/*
 * DatastructureListBenjamin.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */
#include <datastructures/DatastructureListBenjamin.hpp>
DatastructureListBenjamin::DatastructureListBenjamin (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name = "DatastructureListGrid";
    m_particle_groups.push_back (ParticleGroup (Vec3l (), m_options.m_bounds));
}
DatastructureListBenjamin::~DatastructureListBenjamin () {
}
void DatastructureListBenjamin::list_step_2_calculate (ParticleGroup& p_cell, AlgorithmBase& p_algorithm, unsigned int p_idx_a, unsigned int p_idx_b) {
    unsigned long i, j;
    for (i = 0; i < p_cell.m_neighbors.size (); i++) {
        for (j = 0; j < p_cell.m_neighbors[i].size (); j++) {
            p_algorithm.step_2 (p_cell.m_positions_x[p_idx_a][i],
                                p_cell.m_positions_y[p_idx_a][i],
                                p_cell.m_positions_z[p_idx_a][i],
                                p_cell.m_positions_x[p_idx_b][i],
                                p_cell.m_positions_y[p_idx_b][i],
                                p_cell.m_positions_z[p_idx_b][i],
                                p_cell.m_positions_x[p_idx_a].data (),
                                p_cell.m_positions_y[p_idx_a].data (),
                                p_cell.m_positions_z[p_idx_a].data (),
                                p_cell.m_positions_x[p_idx_b].data (),
                                p_cell.m_positions_y[p_idx_b].data (),
                                p_cell.m_positions_z[p_idx_b].data (),
                                p_cell.m_neighbors[i][j],
                                p_cell.m_neighbors[i][j] + 1);
        }
    }
    // TODO border interactions missing!!!
}
bool DatastructureListBenjamin::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
    m_iterations_until_rearange_particles--;
    if (m_iterations_until_rearange_particles < 1) {
        m_iterations_until_rearange_particles = m_options.m_max_iterations_between_datastructure_rebuild;
        list_rebuild (m_particle_groups[0], m_idx_a, m_options);
    }
    step_1_prepare_cell (m_particle_groups[0]);
    list_step_2_calculate (m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b);
    step_3_fit_into_borders (m_particle_groups[0]);
    m_idx_b = !(m_idx_a = m_idx_b);
    return false; // NO error
}
void DatastructureListBenjamin::list_rebuild (ParticleGroup& p_cell, unsigned int p_idx_a, s_options& p_options) {
    unsigned long i;
    unsigned long j;
    p_cell.m_neighbors.resize (p_cell.m_ids.size ());
    // cut_off_radius*1.2 to allow particles to move before reconstruction of
    // lists is needed
    data_type cut_off_radius_squared = p_options.m_cut_off_radius * p_options.m_cut_off_radius * 1.2f;
    for (i = 0; i < p_cell.m_neighbors.size (); i++) {
        p_cell.m_neighbors[i].clear ();
    }
    for (i = 0; i < p_cell.m_neighbors.size (); i++) {
        for (j = 0; j < i; j++) {
            data_type dx = p_cell.m_positions_x[p_idx_a][i] - p_cell.m_positions_x[p_idx_a][j];
            data_type dy = p_cell.m_positions_y[p_idx_a][i] - p_cell.m_positions_y[p_idx_a][j];
            data_type dz = p_cell.m_positions_z[p_idx_a][i] - p_cell.m_positions_z[p_idx_a][j];
            if (cut_off_radius_squared >= (dx * dx + dy * dy + dz * dz)) {
                p_cell.m_neighbors[i].push_back (j);
            }
        }
    }
}
int DatastructureListBenjamin::get_neighbor_index_for_cells(ParticleGroup& p_cell_i,ParticleGroup& p_cell_j){
return p_cell_i.m_idx.x*6+(p_cell_j.m_idx.y-p_cell_i.m_idx.y+1)*3+(p_cell_j.m_idx.z-p_cell_i.m_idx.z+1);
/*
 * (yes this order is intended ...)
 * this order matches the one as used ion the grid-optimisation
 * returned values is one off [6,7,8,9,10,11,12,13,14,0,1,2,3 ]
 *
 */
}
