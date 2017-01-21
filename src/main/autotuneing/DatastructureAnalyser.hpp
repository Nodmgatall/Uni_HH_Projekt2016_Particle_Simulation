/*
 * DatastructureAnalyser.hpp
 *
 *  Created on: 21.01.2017
 *      Author: benjamin
 */

#ifndef SRC_MAIN_AUTOTUNEING_DATASTRUCTUREANALYSER_HPP_
#define SRC_MAIN_AUTOTUNEING_DATASTRUCTUREANALYSER_HPP_

#include "algorithms/AlgorithmLennardJones.hpp"
#include "borders/BorderWrapparound.hpp"
#include "io/output/file/FileWriterCSV.hpp"
#include <datastructures/DatastructureBase.hpp>

class DatastructureAnalyser : public DatastructureBase {
  public:
    DatastructureAnalyser (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_writer);
    virtual ~DatastructureAnalyser ();
    void transfer_particles_to (DatastructureBase& p_datastructure);
    e_datastructure_type analyse ();
    void add_particle (Vec3f p_position);
    void add_particle (Vec3f p_position, Vec3f p_velocity, int p_id = -1);
};

#endif /* SRC_MAIN_AUTOTUNEING_DATASTRUCTUREANALYSER_HPP_ */
