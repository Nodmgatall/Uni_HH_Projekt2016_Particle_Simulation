#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"

#include "datastructures/DatastructureBase.hpp"
#include "options/Options.hpp"

class ParticleSimulator {
  private:
    s_options          m_options;
    DatastructureBase* m_datastructure;

  public:
    ParticleSimulator (s_options& p_options, DatastructureBase* p_datastructure);
    ~ParticleSimulator ();
    /**
     * runs the complete simulation with all iteration steps
     */
    void simulate ();
};

#endif
