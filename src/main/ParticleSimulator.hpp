/*
 * ParticleSimulator.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_PARTICLESIMULATOR_HPP_
#define SRC_MAIN_PARTICLESIMULATOR_HPP_
#include "Definitions.hpp"
#include "datastructures/DatastructureBase.hpp"
#include "options/Options.hpp"
#include <autotuning/Autotuning.hpp>
class ParticleSimulator {
  private:
    /**
     * the given options from the program-start
     */
    s_options m_options;

    OutputBase*    m_output;
    BorderBase*    m_border;
    AlgorithmBase* m_algorithm;
    /**
     * the datastructure which holds all the data
     */
    DatastructureBase* m_datastructure;

  public:
    /**
     * constructor
     */
    ParticleSimulator (s_options& p_options, OutputBase* p_output, BorderBase* p_border, AlgorithmBase* p_algorithm, DatastructureBase* p_datastructure);
    /**
     * destructor
     */
    ~ParticleSimulator ();
    /**
     * runs the complete simulation with all iteration steps
     */
    void simulate ();
};
#endif
