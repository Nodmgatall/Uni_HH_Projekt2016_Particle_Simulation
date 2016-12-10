#include <memory>

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "datastructures/ParticlesBase.hpp"
#include "datastructures/ParticlesGrid.hpp"
#include "datastructures/ParticlesList.hpp"
#include "tools/Usage.hpp"

#include "IO/Options.hpp"
#include <memory>
#include <unistd.h>

#include "generators/ParticleGeneratorFactory.hpp"

ParticleSimulator::ParticleSimulator (s_options& p_options)
: m_options (p_options), m_particle_generator (ParticleGeneratorFactory::build (p_options)),
  m_particles (0),
  m_particle_file_writer (p_options.m_write_modes, std::string (log_folder) + "/data"),
  m_save_config (false), m_particle_bounds_correction (p_options.m_bounds), m_algorithm (p_options) {
}

void ParticleSimulator::simulate () {
    Benchmark::begin ("Simulation");
    m_particles->serialize ();
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
        m_particles->run_simulation_iteration (iteration_number);
        current_time += m_options.m_timestep;
        timesteps_until_next_write--;
        if (!timesteps_until_next_write) {
            m_particles->serialize ();
            timesteps_until_next_write = m_options.m_write_fequency;
        }
        iteration_number++;
        Benchmark::end ();
    }
    Benchmark::end ();
    std::cout << "Simulated " << iteration_number << " iterations in " << current_time
              << "miliseconds" << std::endl;
}

void ParticleSimulator::init_particle_data () {
    Benchmark::begin ("init_particle_data");
    switch (m_options.m_data_structure) {
        case GRID:
            m_particles =
                std::make_shared<ParticlesGrid> (m_options, m_particle_bounds_correction, m_algorithm, m_particle_file_writer);
            break;
        case LIST:
            m_particles =
                std::make_shared<ParticlesList> (m_options, m_particle_bounds_correction, m_algorithm, m_particle_file_writer);
            break;
        case LISTEDGIRD:
            std::cout << "Mixture of list and grind not implemented" << std::endl;
            exit (EXIT_SUCCESS);
    }
    if (m_options.m_in_file_name.length () > 0) {
        DEBUG_BEGIN << "loading from file: " << m_options.m_in_file_name << DEBUG_END;
    } else {
        m_particle_generator.generate (m_particles);
    }
    Benchmark::end ();
}
