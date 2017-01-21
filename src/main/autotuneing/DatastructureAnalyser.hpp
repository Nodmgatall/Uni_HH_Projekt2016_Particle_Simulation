/*
 * DatastructureAnalyser.hpp
 *
 *  Created on: 21.01.2017
 *      Author: benjamin
 */

#ifndef SRC_MAIN_AUTOTUNEING_DATASTRUCTUREANALYSER_HPP_
#define SRC_MAIN_AUTOTUNEING_DATASTRUCTUREANALYSER_HPP_

#include <datastructures/DatastructureBase.hpp>

class DatastructureAnalyser : public DatastructureBase {
  public:
    DatastructureAnalyser (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    virtual ~DatastructureAnalyser ();

    void transfer_particles_to (DatastructureBase& p_datastructure);
    void analyse ();
};

#endif /* SRC_MAIN_AUTOTUNEING_DATASTRUCTUREANALYSER_HPP_ */
