/*
 * DatastructureListGrid.hpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */
#ifndef SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTGRID_HPP_
#define SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTGRID_HPP_
#include <datastructures/DatastructureGrid.hpp>
#include <datastructures/DatastructureListBenjamin.hpp>
class DatastructureListGrid : virtual public DatastructureGrid {
  protected:
    void grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell) override;
  public:
    /**
         * constructor
         */
    DatastructureListGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    /**
     * destructor
     */
    ~DatastructureListGrid ();
};
#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTGRID_HPP_ */
