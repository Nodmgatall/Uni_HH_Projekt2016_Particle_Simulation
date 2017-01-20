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

class DatastructureListGrid : virtual public DatastructureGrid, virtual public DatastructureListBenjamin {
  protected:
    void grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell);

  public:
    /**
         * constructor
         */
    DatastructureListGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    /**
     * destructor
     */
    ~DatastructureListGrid ();
    bool run_simulation_iteration (unsigned long p_iteration_number = 0);
    void add_particle (Vec3f p_position);
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id = -1);
};

#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTGRID_HPP_ */
