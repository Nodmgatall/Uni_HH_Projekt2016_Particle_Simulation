#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/OptionHandler.hpp"
#include "IO/ParticleWriterCSV.hpp"
#include "algorithms/AlgorithmLennardJones.hpp"
#include "borders/BorderWrapparound.hpp"
#include "datastructures/DatastructureBase.hpp"
#include "generators/ParticleGeneratorFactory.hpp"
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

class ParticleSimulator {
  private:
    s_options&             m_options;
    ParticleGeneratorBase* m_particle_generator;
    ParticleWriterBase*    m_particle_file_writer;
    bool                   m_save_config;
    BorderBase*            m_border;
    AlgorithmBase*         m_algorithm;
    DatastructureBase*     m_particles;

  public:
    ParticleSimulator (s_options& p_options);
    ~ParticleSimulator ();
    void simulate ();
};

#endif
