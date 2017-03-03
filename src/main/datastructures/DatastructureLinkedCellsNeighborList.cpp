/*
 * DatastructureLinkedCellsNeighborList.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include <datastructures/DatastructureLinkedCellsNeighborList.hpp>
DatastructureLinkedCellsNeighborList::DatastructureLinkedCellsNeighborList (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, OutputBase& p_particle_writer)
: DatastructureLinkedCells (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name = "DatastructureLinkedCellsNeighborList";
}
DatastructureLinkedCellsNeighborList::~DatastructureLinkedCellsNeighborList () {
}
void DatastructureLinkedCellsNeighborList::grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell) {
    if (m_datastructure_rebuild_last_iteration_flag) {
        DatastructureNeighborList::list_rebuild (p_cell, m_idx_a, m_options);
    }
    DatastructureNeighborList::list_step_2_calculate (p_cell, m_algorithm, m_idx_a, m_idx_b);
}

void DatastructureLinkedCellsNeighborList::grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j) {
    if (m_datastructure_rebuild_last_iteration_flag) {
        DatastructureNeighborList::list_rebuild (p_cell_i, p_cell_j, m_idx_a, m_options);
    }
    DatastructureNeighborList::list_step_2_calculate (p_cell_i, p_cell_j, m_algorithm, m_idx_a, m_idx_b);
}
void DatastructureLinkedCellsNeighborList::grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, data_type p_offset_x, data_type p_offset_y, data_type p_offset_z) {
    if (m_datastructure_rebuild_last_iteration_flag) {
        DatastructureNeighborList::list_rebuild (p_cell_i, p_cell_j, m_idx_a, m_options, p_offset_x, p_offset_y, p_offset_z);
    }
    DatastructureNeighborList::list_step_2_calculate (p_cell_i, p_cell_j, m_algorithm, m_idx_a, m_idx_b, p_offset_x, p_offset_y, p_offset_z);
}
e_datastructure_type DatastructureLinkedCellsNeighborList::get_structure_type () {
    return e_datastructure_type::LINKED_CELLS_NEIGHBOR_LIST;
}
