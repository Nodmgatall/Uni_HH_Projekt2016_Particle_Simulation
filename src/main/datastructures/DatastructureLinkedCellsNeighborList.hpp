/*
 * DatastructureLinkedCellsNeighborList.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELINKEDCELLSNEIGHBORLIST_HPP_
#define SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELINKEDCELLSNEIGHBORLIST_HPP_
#include <datastructures/DatastructureLinkedCells.hpp>
#include <datastructures/DatastructureNeighborList.hpp>
class DatastructureLinkedCellsNeighborList : public DatastructureLinkedCells {
  protected:
    void grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell) override;
    void grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j) override;
    void grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, data_type p_offset_x, data_type p_offset_y, data_type p_offset_z) override;

  public:
    /**
     * constructor
     */
    DatastructureLinkedCellsNeighborList (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, OutputBase& p_particle_writer);
    /**
     * destructor
     */
    virtual ~DatastructureLinkedCellsNeighborList ();
};
#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTURELINKEDCELLSNEIGHBORLIST_HPP_ */
