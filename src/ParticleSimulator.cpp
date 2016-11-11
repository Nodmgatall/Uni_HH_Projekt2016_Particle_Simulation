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
#include "tools/Usage.hpp"

#include "IO/OptionsGenerator.hpp"
#include "IO/OptionsSimulation.hpp"
#include <memory>
#include <unistd.h>

#include "generators/ParticleGeneratorFactoryFactory.hpp"

/*clang-format off */
ParticleSimulator::ParticleSimulator (s_simulator_options *p_sim_options, s_generator_options *p_gen_options)
: m_algorithm (dummy_algo), m_bounds (glm::vec3 (1, 1, 1)), m_delta_t (0),
  m_options (p_sim_options), m_particle_file_writer (new ParticleFileWriter ()),
  m_particle_generator (ParticleGeneratorFactory::build (p_gen_options)),
  m_particles (std::make_shared<ParticlesGrid> ()), m_save_config (false) {

    m_particle_file_writer->set_file_name_base (std::string (log_folder) + "/data");
    m_delta_t     = 1;     // TODO remove
    m_save_config = false; // TODO remvove
}
/*clang-format on */

void ParticleSimulator::simulate () {
    DEBUG_BEGIN << "Starting simulation" << DEBUG_END;
    bool iteration_successfull = true;
    // TODO: set up simulation parameters according to later function parameters
    while (false && iteration_successfull == true) // TODO: fix while to end
                                                   // when simulation ended;
    {
        m_particles->run_simulation_iteration ();
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
        m_particle_generator->generate (m_particles, m_bounds, m_options->m_particle_count);
    }
}

void ParticleSimulator::find_simulation_algorithm () {
    DEBUG_BEGIN << "Setting simulation algorithm" << DEBUG_END;
    m_algorithm = dummy_algo;
    m_particles->set_algorithm (m_algorithm);
}
