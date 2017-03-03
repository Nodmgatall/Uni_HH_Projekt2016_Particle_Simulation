/*
 * ParticleSimulator.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "ParticleSimulator.hpp"
ParticleSimulator::ParticleSimulator (s_options& p_options, OutputBase* p_output, BorderBase* p_border, AlgorithmBase* p_algorithm, DatastructureBase* p_datastructure)
: m_options (p_options),                                                                                 //
  m_output (p_output), m_border (p_border), m_algorithm (p_algorithm), m_datastructure (p_datastructure) //
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
        if (m_options.m_autotuning) {
            m_options.m_iterations_until_autotuning_scan--;
            if (m_options.m_iterations_until_autotuning_scan < 0) {
                m_options.m_iterations_until_autotuning_scan = m_options.m_iterations_between_autotuning_scan;
                m_datastructure                              = Autotuning::get_best_datastructure (m_options, *m_border, *m_algorithm, *m_output, m_datastructure);
            }
        }
        iteration_number++;
        Benchmark::end ();
        if (error_happened)
            break;
    }
    Benchmark::end ();
}
