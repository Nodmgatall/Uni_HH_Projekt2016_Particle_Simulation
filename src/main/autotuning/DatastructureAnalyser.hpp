/*
 * DatastructureAnalyser.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_AUTOTUNING_DATASTRUCTUREANALYSER_HPP_
#define SRC_MAIN_AUTOTUNING_DATASTRUCTUREANALYSER_HPP_
#include "borders/BorderWrapparound.hpp"
#include <algorithms/AlgorithmStoermerVerletLennardJones.hpp>
#include <cstring>
#include <datastructures/DatastructureBase.hpp>
#include <io/output/file/FileOutputCSV.hpp>
class DatastructureAnalyser : public DatastructureBase {
  public:
    /**
     * constructor
     */
    DatastructureAnalyser (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, OutputBase& p_writer);
    /**
     * destructor
     */
    virtual ~DatastructureAnalyser ();
    /**
     * transfers the internally stored particles to another datastructure.
     */
    void transfer_particles_to (DatastructureBase& p_datastructure);
    /**
     * analyses the already given particles and returns which datastructure would be the fastest.
     * this function modifies p_options.m_initial_speed and p_options.m_input_type
     */
    void analyse ();
    void add_particle (Vec3f p_position) override;
    void add_particle (Vec3f p_position, Vec3f p_velocity, int p_id = -1) override;
};
#endif /* SRC_MAIN_AUTOTUNING_DATASTRUCTUREANALYSER_HPP_ */