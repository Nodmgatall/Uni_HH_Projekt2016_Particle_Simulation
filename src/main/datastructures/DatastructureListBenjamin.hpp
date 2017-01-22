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

class DatastructureListBenjamin : virtual public DatastructureBase {
  protected:
  public:
    /**
     * constructor
     */
    DatastructureListBenjamin (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    /**
     * destructor
     */
    ~DatastructureListBenjamin ();
    bool run_simulation_iteration (unsigned long p_iteration_number = 0) override;
    /**
     * calculates the movement of particles based on the forces between every
     * particle-pair in the given
     * cell
     * @param p_cell the cell which contains the particles
     */
    static void list_step_2_calculate (ParticleGroup& p_cell,
                                       AlgorithmBase& p_algorithm,
                                       unsigned int   p_idx_a,
                                       unsigned int   p_idx_b);
    /**
     * rebuilds the neighborlist in the given cell. if there are other cells in the neighborhood,
     * these would be ignored.
     */
    static void list_rebuild (ParticleGroup& p_cell, unsigned int p_idx_a, s_options& p_options);
};

#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELISTBENJAMIN_HPP_ */
