
#include "ParticleSimulator.hpp"

ParticleSimulator::ParticleSimulator (s_options& p_options) //
    : m_options (p_options),                                //
      m_writer (ParticleWriterCSV (p_options.m_write_modes,
                                   std::string (log_folder) + "/data")), //
      m_border (BorderWrapparound (m_options.m_bounds)),                 //
      m_algorithm (AlgorithmFactory::build (m_options)),                 //
      m_datastructure (DatastructureFactory::build (m_options,
                                                    m_border,
                                                    m_algorithm,
                                                    m_writer)), //
      m_input (InputFactory::build (m_options, m_datastructure)) {
    Benchmark::begin ("ParticleSimulator");
    if (m_options.m_in_file_name.length () > 0) {
        DEBUG_BEGIN << "loading from file: " << m_options.m_in_file_name << DEBUG_END;
    } else {
        m_input.initialize ();
    }
    Benchmark::end ();
}
ParticleSimulator::~ParticleSimulator () {
}
void ParticleSimulator::simulate () {
    Benchmark::begin ("Simulation");
    m_datastructure.serialize ();
    data_type     current_time = 0.0;
    data_type     max_run_time;
    int           timesteps_until_next_write = m_options.m_write_fequency;
    unsigned long iteration_number           = 0;
    if (m_options.m_max_iterations > 0) {
        max_run_time = m_options.m_max_iterations * m_options.m_timestep;
    } else {
        max_run_time = m_options.m_run_time_limit;
    }
    max_run_time = MIN (max_run_time, m_options.m_run_time_limit);
    while (current_time < max_run_time) {
        Benchmark::begin ("Simulating the time-step");
        DEBUG_BEGIN << DEBUG_VAR (current_time) << DEBUG_END;
        m_datastructure.run_simulation_iteration (iteration_number);
        current_time += m_options.m_timestep;
        timesteps_until_next_write--;
        if (!timesteps_until_next_write) {
            m_datastructure.serialize ();
            timesteps_until_next_write = m_options.m_write_fequency;
        }
        iteration_number++;
        Benchmark::end ();
    }
    Benchmark::end ();
    std::cout << "Simulated " << iteration_number << " iterations " << std::endl;
}
