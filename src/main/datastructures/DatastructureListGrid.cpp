/*
 * DatastructureListGrid.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */
#include <datastructures/DatastructureListGrid.hpp>
DatastructureListGrid::DatastructureListGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer), DatastructureGrid (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name = "DatastructureListGrid";
}
DatastructureListGrid::~DatastructureListGrid () {
}
void DatastructureListGrid::grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell) {
    if (m_iterations_until_rearange_particles < 1) {
        DatastructureListBenjamin::list_rebuild (p_cell, m_idx_a, m_options);
    }
    DatastructureListBenjamin::list_step_2_calculate (p_cell, m_algorithm, m_idx_a, m_idx_b);
}
