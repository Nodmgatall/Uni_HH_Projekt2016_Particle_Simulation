
#include "ParticleSimulator.hpp"

ParticleSimulator::ParticleSimulator (s_options& p_options, DatastructureBase* p_datastructure)
: m_options (p_options),            //
  m_datastructure (p_datastructure) //
{
}
ParticleSimulator::~ParticleSimulator () {
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
    Benchmark::end ();
}
