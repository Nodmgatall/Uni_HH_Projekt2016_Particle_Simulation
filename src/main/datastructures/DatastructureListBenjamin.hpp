/*
 * DatastructureListBenjamin.hpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */

#ifndef SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTBENJAMIN_HPP_
#define SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTBENJAMIN_HPP_

#include "DatastructureBase.hpp"
#include "Definitions.hpp"
#include "Vec3.hpp"
#include "helper/ParticleGroup.hpp"

class DatastructureListBenjamin : public DatastructureBase {
  protected:
    /**
     * list of neighbors to calculate the interaction with
     */
    std::vector<std::vector<unsigned long>> list_neighbors;
    /**
         * first step in each iteration. Calculates the new particle position based on
         * its own speed
         * @param p_cell the cell contains the particles which are calculated
         */
    void list_step_1_prepare (ParticleGroup& p_cell);
    /**
     * calculates the movement of particles based on the forces between every
     * particle-pair in the given
     * cell
     * @param p_cell the cell which contains the particles
     */
    void list_step_2_calculate (ParticleGroup& p_cell);

  public:
    /**
     * constructor
     */
    DatastructureListBenjamin (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    /**
     * destructor
     */
    ~DatastructureListBenjamin ();
    bool run_simulation_iteration (unsigned long p_iteration_number = 0);
    void add_particle (Vec3f p_position);
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id = -1);
    unsigned long get_particle_count ();
};

#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTBENJAMIN_HPP_ */
