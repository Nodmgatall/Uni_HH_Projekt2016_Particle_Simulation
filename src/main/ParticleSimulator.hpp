#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"

#include "options/OptionHandler.hpp"

#include "borders/BorderWrapparound.hpp"
#include "io/output/ParticleWriterCSV.hpp"

#include "algorithms/AlgorithmFactory.hpp"
#include "datastructures/DatastructureFactory.hpp"
#include "io/input/generators/GeneratorFactory.hpp"

#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

class ParticleSimulator {
  private:
    s_options          m_options;
    ParticleWriterBase m_writer;
    BorderBase         m_border;
    AlgorithmBase      m_algorithm;
    DatastructureBase  m_datastructure;
    GeneratorBase      m_generator;

  public:
    ParticleSimulator (s_options& p_options);
    ~ParticleSimulator ();
    void simulate ();
};

#endif
