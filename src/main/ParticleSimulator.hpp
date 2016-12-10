#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/OptionHandler.hpp"
#include "IO/ParticleFileWriter.hpp"
#include "algorithms/AlgorithmLennardJones.hpp"
#include "borders/ParticleBoundsCorrectionWraparound.hpp"
#include "datastructures/ParticlesBase.hpp"
#include "generators/ParticleGeneratorFactory.hpp"
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

class ParticleSimulator {
  private:
    s_options&                             m_options;
    std::unique_ptr<ParticleGeneratorBase> m_particle_generator;
    std::shared_ptr<ParticlesBase>         m_particles;
    ParticleFileWriter                     m_particle_file_writer;
    bool                                   m_save_config;
    ParticleBoundsCorrectionWraparound     m_particle_bounds_correction;
    AlgorithmLennardJones                  m_algorithm;

  public:
    ParticleSimulator (s_options& p_options);
    void simulate ();
    void init_particle_data ();
};

#endif
