#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"

#include "options/OptionHandler.hpp"

#include "borders/BorderWrapparound.hpp"
#include "io/output/file/FileWriterCSV.hpp"

#include "algorithms/AlgorithmFactory.hpp"
#include "datastructures/DatastructureFactory.hpp"
#include "io/input/InputFactory.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <memory>

class ParticleSimulator {
  private:
    s_options          m_options;
    WriterBase*        m_writer;
    BorderBase*        m_border;
    AlgorithmBase*     m_algorithm;
    DatastructureBase* m_datastructure;
    InputBase*         m_input;

  public:
    ParticleSimulator (s_options& p_options);
    ~ParticleSimulator ();
    /**
     * runs the complete simulation with all iteration steps
     */
    void simulate ();
};

#endif
