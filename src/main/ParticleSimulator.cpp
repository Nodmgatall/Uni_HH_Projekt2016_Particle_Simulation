
#include "ParticleSimulator.hpp"

ParticleSimulator::ParticleSimulator (s_options& p_options)
: m_options (p_options),                                                                      //
  m_writer (FileWriterCSV (p_options.m_write_modes, std::string (log_folder) + "/data")),     //
  m_border (BorderWrapparound (m_options.m_bounds)),                                          //
  m_algorithm (AlgorithmFactory::build (m_options)),                                          //
  m_datastructure (DatastructureFactory::build (m_options, m_border, m_algorithm, m_writer)), //
  m_input (InputFactory::build (m_options, m_datastructure)) {
    m_input.initialize_datastructure ();
}
ParticleSimulator::~ParticleSimulator () {
}
void ParticleSimulator::simulate () {
    Benchmark::begin ("Simulation");
    unsigned long max_timesteps              = 0;
    int           timesteps_until_next_write = m_options.m_write_fequency;
    unsigned long iteration_number           = 0;
    if (m_options.m_max_iterations > 0) {
        max_timesteps = m_options.m_max_iterations;
    } else {
        max_timesteps = m_options.m_run_time_limit / m_options.m_timestep;
    }
    m_datastructure.serialize ();
    while (iteration_number < max_timesteps) {
        Benchmark::begin ("Simulating the time-step");
        m_datastructure.run_simulation_iteration (iteration_number);
        timesteps_until_next_write--;
        if (!timesteps_until_next_write) {
            m_datastructure.serialize ();
            timesteps_until_next_write = m_options.m_write_fequency;
        }
        iteration_number++;
        Benchmark::end ();
    }
    Benchmark::end ();
}
