#include <memory>

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "datastructures/DatastructureList.hpp"
#include "tools/Usage.hpp"

#include "IO/Options.hpp"
#include <memory>
#include <unistd.h>

#include "datastructures/DatastructureBase.hpp"
#include "datastructures/DatastructureGrid.hpp"
#include "generators/ParticleGeneratorFactory.hpp"

ParticleSimulator::ParticleSimulator (s_options& p_options)
: m_options (p_options), m_generator (ParticleGeneratorFactory::build (p_options)),
  m_writer (new ParticleWriterCSV (p_options.m_write_modes, std::string (log_folder) + "/data")),
  m_save_config (false), m_border (new BorderWrapparound (p_options.m_bounds)),
  m_algorithm (new AlgorithmLennardJones (p_options)), m_datastructure (0) {
    Benchmark::begin ("ParticleSimulator");
    switch (m_options.m_data_structure) {
        case GRID:
            m_datastructure = new DatastructureGrid (m_options, *m_border, *m_algorithm, *m_writer);
            break;
        case LIST:
            m_datastructure = new DatastructureList (m_options, *m_border, *m_algorithm, *m_writer);
            break;
        case LISTEDGIRD:
            std::cout << "Mixture of list and grind not implemented" << std::endl;
            exit (EXIT_SUCCESS);
    }
    if (m_options.m_in_file_name.length () > 0) {
        DEBUG_BEGIN << "loading from file: " << m_options.m_in_file_name << DEBUG_END;
    } else {
        m_generator->generate (m_datastructure);
    }
    Benchmark::end ();
}
ParticleSimulator::~ParticleSimulator () {
    delete (m_generator);
    delete (m_writer);
    delete (m_border);
    delete (m_algorithm);
    delete (m_datastructure);
}
void ParticleSimulator::simulate () {
    Benchmark::begin ("Simulation");
    m_datastructure->serialize ();
    data_type     current_time = 0.0;
    data_type     max_run_time;
    int           timesteps_until_next_write = m_options.m_write_fequency;
    unsigned long iteration_number           = 0;
    if (m_options.m_max_iterations > 0) {
        max_run_time = m_options.m_max_iterations * m_options.m_timestep;
    } else {
        max_run_time = m_options.m_run_time_limit;
    }
    while (current_time < max_run_time && current_time < m_options.m_run_time_limit) {
        Benchmark::begin ("Simulating the time-step");
        DEBUG_BEGIN << DEBUG_VAR (current_time) << DEBUG_END;
        m_datastructure->run_simulation_iteration (iteration_number);
        current_time += m_options.m_timestep;
        timesteps_until_next_write--;
        if (!timesteps_until_next_write) {
            m_datastructure->serialize ();
            timesteps_until_next_write = m_options.m_write_fequency;
        }
        iteration_number++;
        Benchmark::end ();
    }
    Benchmark::end ();
    std::cout << "Simulated " << iteration_number << " iterations in " << current_time
              << "miliseconds" << std::endl;
}
