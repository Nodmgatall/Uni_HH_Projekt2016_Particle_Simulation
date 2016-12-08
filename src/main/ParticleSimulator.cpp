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

#include "IO/OptionsGenerator.hpp"
#include "IO/OptionsSimulation.hpp"
#include <memory>
#include <unistd.h>

#include "generators/ParticleGeneratorFactory.hpp"

/*clang-format off */
ParticleSimulator::ParticleSimulator (s_simulator_options &p_sim_options, s_generator_options *p_gen_options)
: m_bounds (Vec3f (5.0f, 5.0f, 5.0f)), m_options (p_sim_options),
  m_particle_file_writer (std::make_shared<ParticleFileWriter> (p_sim_options.m_write_modes)),
  m_particle_generator (ParticleGeneratorFactory::build (p_gen_options)), m_particles (0),
  m_save_config (false) {
    DEBUG_BEGIN << "ParticleSimulator()" << DEBUG_END;
    m_particle_file_writer->set_file_name_base (std::string (log_folder) + "/data");
    m_save_config = false; // TODO remvove
}
/*clang-format on */

void ParticleSimulator::simulate () {
    Benchmark::begin ("Simulation");
    m_particles->serialize (m_particle_file_writer);
    data_type current_time               = 0.0;
    int       timesteps_until_next_write = m_options.m_write_fequency;
    while (current_time <= m_options.m_run_time_limit) {
        Benchmark::begin ("Simulating the time-step");
        DEBUG_BEGIN << DEBUG_VAR (current_time) << DEBUG_END;
        m_particles->run_simulation_iteration ();
        current_time += m_options.m_timestep;
        timesteps_until_next_write--;
        if (!timesteps_until_next_write) {
            m_particles->serialize (m_particle_file_writer);
            timesteps_until_next_write = m_options.m_write_fequency;
        }
        Benchmark::end ();
    }
    Benchmark::end ();
}

void ParticleSimulator::init_particle_data () {
    Benchmark::begin ("init_particle_data");
    ParticleBoundsCorrectionWraparound particleBoundsCorrectionWraparound =
        ParticleBoundsCorrectionWraparound (m_bounds);
    switch (m_options.m_data_structure) {
        case GRID:
            m_particles = std::make_shared<ParticlesGrid> (m_options, m_bounds, particleBoundsCorrectionWraparound);
            break;
        case LIST:
            m_particles = std::make_shared<ParticlesList> (m_options, m_bounds, particleBoundsCorrectionWraparound);
            break;
        case LISTEDGIRD:
            std::cout << "Mixture of list and grind not implemented" << std::endl;
            exit (EXIT_SUCCESS);
    }
    if (m_options.m_in_file_name.length () > 0) {
        DEBUG_BEGIN << "loading from file: " << m_options.m_in_file_name << DEBUG_END;
    } else {
        m_particle_generator->generate (m_particles, m_bounds, m_options.m_particle_count);
    }
    Benchmark::end ();
}
