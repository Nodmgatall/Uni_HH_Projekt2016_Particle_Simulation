#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP
#include "Definitions.hpp"
#include "datastructures/DatastructureBase.hpp"
#include "options/Options.hpp"
class ParticleSimulator {
  private:
    /**
     * the given options from the program-start
     */
    s_options m_options;
    /**
     * the datastructure which holds all the data
     */
    DatastructureBase* m_datastructure;

  public:
    /**
     * constructor
     */
    ParticleSimulator (s_options& p_options, DatastructureBase* p_datastructure);
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
