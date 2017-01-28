/*
 * DatastructureListGrid.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */
#include <datastructures/DatastructureListGrid.hpp>
DatastructureListGrid::DatastructureListGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer), DatastructureGrid (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name                       = "DatastructureListGrid";
    m_iterations_until_rearange_particles = 0;
}
DatastructureListGrid::~DatastructureListGrid () {
}
void DatastructureListGrid::grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell) {
    if (m_datastructure_rebuild_last_iteration_flag) {
        DatastructureListBenjamin::list_rebuild (p_cell, m_idx_a, m_options);
    }
    DatastructureListBenjamin::list_step_2_calculate (p_cell, m_algorithm, m_idx_a, m_idx_b);
}

void DatastructureListGrid::grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j) {
    if (m_datastructure_rebuild_last_iteration_flag) {
        DatastructureListBenjamin::list_rebuild (p_cell_i, p_cell_j, m_idx_a, m_options);
    }
    DatastructureListBenjamin::list_step_2_calculate (p_cell_i, p_cell_j, m_algorithm, m_idx_a, m_idx_b);
}
void DatastructureListGrid::grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, data_type p_offset_x, data_type p_offset_y, data_type p_offset_z) {
    if (m_datastructure_rebuild_last_iteration_flag) {
        DatastructureListBenjamin::list_rebuild (p_cell_i, p_cell_j, m_idx_a, m_options, p_offset_x, p_offset_y, p_offset_z);
    }
    DatastructureListBenjamin::list_step_2_calculate (p_cell_i, p_cell_j, m_algorithm, m_idx_a, m_idx_b, p_offset_x, p_offset_y, p_offset_z);
}
