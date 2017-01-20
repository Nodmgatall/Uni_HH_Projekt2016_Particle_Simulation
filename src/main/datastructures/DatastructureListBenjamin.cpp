/*
 * DatastructureListBenjamin.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */

#include <datastructures/DatastructureListBenjamin.hpp>

DatastructureListBenjamin::DatastructureListBenjamin (s_options&     p_options,
                                                      BorderBase&    p_border,
                                                      AlgorithmBase& p_algorithm,
                                                      WriterBase&    p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name = "DatastructureListGrid";
    m_particle_groups.push_back (ParticleGroup (Vec3l (), m_options.m_bounds));
}
DatastructureListBenjamin::~DatastructureListBenjamin () {
}
void DatastructureListBenjamin::list_step_2_calculate (ParticleGroup& p_cell) {
    unsigned long i, j;
    for (i = 0; i < p_cell.m_neighbors.size (); i++) {
        for (j = 0; j < p_cell.m_neighbors[i].size (); j++) {
            m_algorithm.step_2 (p_cell.m_positions_x[m_idx_a][i],
                                p_cell.m_positions_y[m_idx_a][i],
                                p_cell.m_positions_z[m_idx_a][i],
                                p_cell.m_positions_x[m_idx_b][i],
                                p_cell.m_positions_y[m_idx_b][i],
                                p_cell.m_positions_z[m_idx_b][i],
                                p_cell.m_positions_x[m_idx_a].data (),
                                p_cell.m_positions_y[m_idx_a].data (),
                                p_cell.m_positions_z[m_idx_a].data (),
                                p_cell.m_positions_x[m_idx_b].data (),
                                p_cell.m_positions_y[m_idx_b].data (),
                                p_cell.m_positions_z[m_idx_b].data (),
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
        list_rebuild (m_particle_groups[0]);
    }
    step_1_prepare_cell (m_particle_groups[0]);
    list_step_2_calculate (m_particle_groups[0]);
    step_3_fit_into_borders (m_particle_groups[0]);
    m_idx_b = !(m_idx_a = m_idx_b);
    return false; // NO error
}
void DatastructureListBenjamin::list_rebuild (ParticleGroup& p_cell) {
    unsigned long i;
    unsigned long j;
    p_cell.m_neighbors.resize (get_particle_count ());
    // cut_off_radius*1.2 to allow particles to move before reconstruction of
    // lists is needed
    data_type cut_off_radius_squared = m_options.m_cut_off_radius * m_options.m_cut_off_radius * 1.2f;
    for (i = 0; i < p_cell.m_neighbors.size (); i++) {
        p_cell.m_neighbors[i].clear ();
    }
    for (i = 0; i < p_cell.m_neighbors.size (); i++) {
        for (j = 0; j < i; j++) {
            data_type dx = p_cell.m_positions_x[m_idx_a][i] - p_cell.m_positions_x[m_idx_a][j];
            data_type dy = p_cell.m_positions_y[m_idx_a][i] - p_cell.m_positions_y[m_idx_a][j];
            data_type dz = p_cell.m_positions_z[m_idx_a][i] - p_cell.m_positions_z[m_idx_a][j];
            if (cut_off_radius_squared >= (dx * dx + dy * dy + dz * dz)) {
                p_cell.m_neighbors[i].push_back (j);
            }
        }
    }
}
void DatastructureListBenjamin::add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id) {
    long id = 0;
    if (p_id >= 0) {
        id       = p_id;
        m_max_id = MAX (m_max_id, p_id + 1);
    } else {
        id = m_max_id++;
    }
    Vec3f old_position = p_current_position - p_current_velocity * m_options.m_timestep;
    m_border.updatePosition (p_current_position.x,
                             p_current_position.y,
                             p_current_position.z,
                             old_position.x,
                             old_position.y,
                             old_position.z);
    m_particle_groups[0].add_particle (p_current_position, old_position, m_idx_a, id);
}
void DatastructureListBenjamin::add_particle (Vec3f p_position) {
    add_particle (p_position, Vec3f (0));
}
