#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/OptionHandler.hpp"
#include "IO/ParticleWriterCSV.hpp"
#include "algorithms/AlgorithmLennardJones.hpp"
#include "borders/BorderWrapparound.hpp"
#include "datastructures/DatastructureBase.hpp"
#include "generators/GeneratorFactory.hpp"
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

class ParticleSimulator {
  private:
    s_options&          m_options;
    GeneratorBase*      m_generator;
    ParticleWriterBase* m_writer;
    BorderBase*         m_border;
    AlgorithmBase*      m_algorithm;
    DatastructureBase*  m_datastructure;

  public:
    ParticleSimulator (s_options& p_options);
    ~ParticleSimulator ();
    void simulate ();
};

#endif
