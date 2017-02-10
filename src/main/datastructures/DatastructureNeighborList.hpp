/*
 * DatastructureNeighborList.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_DATASTRUCTURES_DATASTRUCTURENEIGHBORLIST_HPP_
#define SRC_MAIN_DATASTRUCTURES_DATASTRUCTURENEIGHBORLIST_HPP_
#include "DatastructureBase.hpp"

class DatastructureNeighborList : public DatastructureBase {
  protected:
  public:
    /**
     * constructor
     */
    DatastructureNeighborList (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, OutputBase& p_particle_writer);
    /**
     * destructor
     */
    virtual ~DatastructureNeighborList ();
    bool run_simulation_iteration (unsigned long p_iteration_number = 0) override;
    /**
     * calculates the movement of particles based on the forces between every
     * particle-pair in the given
     * cell
     * @param p_cell the cell which contains the particles
     */
    static void list_step_2_calculate (ParticleGroup& p_cell, AlgorithmBase& p_algorithm, unsigned int p_idx_a, unsigned int p_idx_b);
    static void list_step_2_calculate (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, AlgorithmBase& p_algorithm, unsigned int p_idx_a, unsigned int p_idx_b);
    static void
        list_step_2_calculate (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, AlgorithmBase& p_algorithm, unsigned int p_idx_a, unsigned int p_idx_b, data_type p_offset_x, data_type p_offset_y, data_type p_offset_z);
    /**
     * rebuilds the neighborlist in the given cell. if there are other cells in the neighborhood,
     * these would be ignored.
     */
    static void list_rebuild (ParticleGroup& p_cell, unsigned int p_idx_a, s_options& p_options);
    static void list_rebuild (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, unsigned int p_idx_a, s_options& p_options);
    static void list_rebuild (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, unsigned int p_idx_a, s_options& p_options, data_type p_offset_x, data_type p_offset_y, data_type p_offset_z);
    /**
     * returns the index in the neighborhoodlist for the first cell
     */
    static int get_neighbor_index_for_cells (Vec3l& p_idx_i, Vec3l& p_idx_j);
};
#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTURENEIGHBORLIST_HPP_ */
