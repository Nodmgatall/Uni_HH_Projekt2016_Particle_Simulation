
#include "ParticleSimulator.hpp"

ParticleSimulator::ParticleSimulator (s_options& p_options)
: m_options (p_options),                                                                         //
  m_writer (new FileWriterCSV (p_options, std::string (log_folder) + "/data")),                  //
  m_border (new BorderWrapparound (m_options.m_bounds)),                                         //
  m_algorithm (AlgorithmFactory::build (m_options)),                                             //
  m_datastructure (DatastructureFactory::build (m_options, *m_border, *m_algorithm, *m_writer)), //
  m_input (InputFactory::build (m_options, *m_datastructure)) {
    m_input->initialize_datastructure ();
}
ParticleSimulator::~ParticleSimulator () {
    delete (m_algorithm);
    delete (m_border);
    delete (m_writer);
    delete (m_datastructure);
    delete (m_input);
}
void ParticleSimulator::simulate () {
    Benchmark::begin ("Simulation");
    int           timesteps_until_next_write = m_options.m_write_fequency;
    unsigned long iteration_number           = 0;
    m_datastructure->serialize ();
    while (iteration_number < m_options.m_max_iterations) {
        Benchmark::begin ("Simulating the time-step");
        bool error_happened = m_datastructure->run_simulation_iteration (iteration_number);
        timesteps_until_next_write--;
        if (!timesteps_until_next_write) {
            m_datastructure->serialize ();
            timesteps_until_next_write = m_options.m_write_fequency;
        }
        iteration_number++;
        Benchmark::end ();
        if (error_happened)
            break;
    }
    m_writer->finalize ();
    Benchmark::end ();
}
