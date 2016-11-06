#include <memory>

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "algorithms/DummyAlgorithm.hpp"
#include "datastructures/ParticlesBase.hpp"
#include "datastructures/ParticlesGrid.hpp"
#include "datastructures/ParticlesList.hpp"
#include "generators/ParticleGenerator.hpp"
#include "tools/Usage.hpp"

#include "IO/OptionsGenerator.hpp"
#include "IO/OptionsSimulation.hpp"
#include <memory>
#include <unistd.h>

/*clang-format off */
ParticleSimulator::ParticleSimulator (s_simulator_options *p_sim_options, s_generator_options *p_gen_options)
: m_algorithm (dummy_algo), m_bounds (glm::vec3 (1, 1, 1)), m_delta_t (0),
  m_options (p_sim_options), m_particle_file_writer (new ParticleFileWriter ()),
  m_particle_generator (new ParticleGenerator (p_gen_options)),
  m_particles (std::make_shared<ParticlesGrid> ()), m_save_config (false) {
    time_t     current_time;
    struct tm *time_info;
    char       log_folder[29];
    time (&current_time);
    time_info = localtime (&current_time);
    strftime (log_folder, sizeof (log_folder), "logdata/%Y-%m-%d_%H-%M-%S", time_info);
    mkdir ("logdata", 0700);
    mkdir (log_folder, 0700);
    g_debug_stream.open (std::string (log_folder) + "/log.txt", std::fstream::out);
    unlink ("logdata/latest");
    symlink ((std::string ("../") + log_folder).c_str (), "logdata/latest");
    print_header ();
    m_particle_file_writer->set_file_name_base (std::string (log_folder) + "/data");
}
/*clang-format on */

void ParticleSimulator::print_header () {
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
    DEBUG_BEGIN << "                  Particle Simulation                  " << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
    DEBUG_BEGIN << "            Benjamin Wanke, Oliver Heidmann            " << DEBUG_ENDL;
    DEBUG_BEGIN << "                      Supervisior                      " << DEBUG_END;
    DEBUG_BEGIN << "                    Philipp Neumann                    " << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_ENDL;
}

void ParticleSimulator::simulate () {
    DEBUG_BEGIN << "Starting simulation" << DEBUG_END;
    bool iteration_successfull = true;
    // TODO: set up simulation parameters according to later function parameters
    while (false && iteration_successfull == true) // TODO: fix while to end
                                                   // when simulation ended;
    {
        m_algorithm (m_particles);
    }
    m_particle_file_writer->saveData (m_particles, m_options->m_write_modes);
    DEBUG_BEGIN << "Simulation finished" << DEBUG_END;
}

void ParticleSimulator::init_particle_data () {
    switch (m_options->m_data_structure) {
        case GRID:
            m_particles = std::make_shared<ParticlesGrid> ();
            break;
        case LIST:
            m_particles = std::make_shared<ParticlesList> ();
            break;
        case LISTEDGIRD:
            std::cout << "Mixture of list and grind not implemented" << std::endl;
            exit (EXIT_SUCCESS);
    }
    if (m_options->m_in_file_name.length () > 0) {
        DEBUG_BEGIN << "loading from file: " << m_options->m_in_file_name << DEBUG_END;
    } else {
        m_particle_generator->generate (m_particles, m_bounds, m_particles->get_particle_count ());
    }
}

void ParticleSimulator::find_simulation_algorithm () {
    DEBUG_BEGIN << "Setting simulation algorithm" << DEBUG_END;
    m_algorithm = dummy_algo;
}
