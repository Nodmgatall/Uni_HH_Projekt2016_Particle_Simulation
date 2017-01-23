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
    for (i = 0; i < p_cell.m_neighbors[13].size (); i++) {
        for (j = 0; j < p_cell.m_neighbors[13][i].size (); j++) {
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
                                p_cell.m_neighbors[13][i][j],
                                p_cell.m_neighbors[13][i][j] + 1);
        }
    }
}
void DatastructureListBenjamin::list_step_2_calculate (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, AlgorithmBase& p_algorithm, unsigned int p_idx_a, unsigned int p_idx_b) {
    unsigned long i, j;
    unsigned int  neighbor_index = get_neighbor_index_for_cells (p_cell_i.m_idx, p_cell_j.m_idx);
    for (i = 0; i < p_cell_i.m_neighbors[neighbor_index].size (); i++) {
        for (j = 0; j < p_cell_i.m_neighbors[neighbor_index][i].size (); j++) {
            p_algorithm.step_2 (p_cell_i.m_positions_x[p_idx_a][i],
                                p_cell_i.m_positions_y[p_idx_a][i],
                                p_cell_i.m_positions_z[p_idx_a][i],
                                p_cell_i.m_positions_x[p_idx_b][i],
                                p_cell_i.m_positions_y[p_idx_b][i],
                                p_cell_i.m_positions_z[p_idx_b][i],
                                p_cell_j.m_positions_x[p_idx_a].data (),
                                p_cell_j.m_positions_y[p_idx_a].data (),
                                p_cell_j.m_positions_z[p_idx_a].data (),
                                p_cell_j.m_positions_x[p_idx_b].data (),
                                p_cell_j.m_positions_y[p_idx_b].data (),
                                p_cell_j.m_positions_z[p_idx_b].data (),
                                p_cell_i.m_neighbors[neighbor_index][i][j],
                                p_cell_i.m_neighbors[neighbor_index][i][j] + 1);
        }
    }
}
void DatastructureListBenjamin::list_step_2_calculate (ParticleGroup& p_cell_i,
                                                       ParticleGroup& p_cell_j,
                                                       AlgorithmBase& p_algorithm,
                                                       unsigned int   p_idx_a,
                                                       unsigned int   p_idx_b,
                                                       data_type      p_offset_x,
                                                       data_type      p_offset_y,
                                                       data_type      p_offset_z) {
    unsigned long i, j;
    Vec3l         b = Vec3l (p_cell_i.m_idx);
    if (p_offset_x > 0) {
        b.x = p_cell_i.m_idx.x - 1;
    } else if (p_offset_x < 0) {
        b.x = p_cell_i.m_idx.x + 1;
    }
    if (p_offset_y > 0) {
        b.y = p_cell_i.m_idx.y - 1;
    } else if (p_offset_y < 0) {
        b.y = p_cell_i.m_idx.y + 1;
    }
    if (p_offset_z > 0) {
        b.z = p_cell_i.m_idx.z - 1;
    } else if (p_offset_z < 0) {
        b.z = p_cell_i.m_idx.z + 1;
    }
    unsigned int neighbor_index = get_neighbor_index_for_cells (p_cell_i.m_idx, b);
    for (i = 0; i < p_cell_i.m_neighbors[neighbor_index].size (); i++) {
        for (j = 0; j < p_cell_i.m_neighbors[neighbor_index][i].size (); j++) {
            p_algorithm.step_2_offset (p_offset_x,
                                       p_offset_y,
                                       p_offset_z,
                                       p_cell_i.m_positions_x[p_idx_a][i],
                                       p_cell_i.m_positions_y[p_idx_a][i],
                                       p_cell_i.m_positions_z[p_idx_a][i],
                                       p_cell_i.m_positions_x[p_idx_b][i],
                                       p_cell_i.m_positions_y[p_idx_b][i],
                                       p_cell_i.m_positions_z[p_idx_b][i],
                                       p_cell_j.m_positions_x[p_idx_a].data (),
                                       p_cell_j.m_positions_y[p_idx_a].data (),
                                       p_cell_j.m_positions_z[p_idx_a].data (),
                                       p_cell_j.m_positions_x[p_idx_b].data (),
                                       p_cell_j.m_positions_y[p_idx_b].data (),
                                       p_cell_j.m_positions_z[p_idx_b].data (),
                                       p_cell_i.m_neighbors[neighbor_index][i][j],
                                       p_cell_i.m_neighbors[neighbor_index][i][j] + 1);
        }
    }
}
bool DatastructureListBenjamin::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
    m_iterations_until_rearange_particles--;
    const data_type ox = m_options.m_bounds.x;
    const data_type oy = m_options.m_bounds.y;
    const data_type oz = m_options.m_bounds.z;
    if (m_iterations_until_rearange_particles < 1) {
        m_iterations_until_rearange_particles = m_options.m_max_iterations_between_datastructure_rebuild;
        list_rebuild (m_particle_groups[0], m_idx_a, m_options);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, oy, oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, oy, 0);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, oy, -oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, 0, oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, 0, 0);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, 0, -oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, -oy, oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, -oy, 0);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, ox, -oy, -oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, 0, oy, oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, 0, oy, 0);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, 0, oy, -oz);
        list_rebuild (m_particle_groups[0], m_particle_groups[0], m_idx_a, m_options, 0, 0, oz);
    }
    step_1_prepare_cell (m_particle_groups[0]);
    list_step_2_calculate (m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, oy, oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, oy, 0);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, oy, -oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, 0, oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, 0, 0);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, 0, -oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, -oy, oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, -oy, 0);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, ox, -oy, -oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, 0, oy, oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, 0, oy, 0);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, 0, oy, -oz);
    list_step_2_calculate (m_particle_groups[0], m_particle_groups[0], m_algorithm, m_idx_a, m_idx_b, 0, 0, oz);
    step_3_fit_into_borders (m_particle_groups[0]);
    m_idx_b = !(m_idx_a = m_idx_b);
#ifdef CALCULATE_ENERGY_CONSERVATION
    unsigned int i, j;
    g_sum_energy = 0;
    for (i = 0; i < m_particle_groups.size (); i++) {
        ParticleGroup& group = m_particle_groups[i];
        for (j = 0; j < group.m_ids.size (); j++) {
            data_type m = 1;
            Vec3f     v = Vec3f (group.m_positions_x[m_idx_b][j] - group.m_positions_x[m_idx_a][j],
                             group.m_positions_y[m_idx_b][j] - group.m_positions_y[m_idx_a][j],
                             group.m_positions_z[m_idx_b][j] - group.m_positions_z[m_idx_a][j]);
            g_sum_energy += 0.5 * m * v.length () * v.length ();
        }
    }
    m_verbose_stream << DEBUG_VAR (g_sum_energy) << " Joule" << std::endl;
    g_sum_energy_valid = true;
#endif
    return false; // NO error
}
void DatastructureListBenjamin::list_rebuild (ParticleGroup& p_cell, unsigned int p_idx_a, s_options& p_options) {
    unsigned long i;
    unsigned long j;
    p_cell.m_neighbors[13].resize (p_cell.m_ids.size ());
    // cut_off_radius*1.2 to allow particles to move before reconstruction of
    // lists is needed
    data_type cut_off_radius_squared = p_options.m_cut_off_radius * p_options.m_cut_off_radius * 1.2f;
    for (i = 0; i < p_cell.m_neighbors[13].size (); i++) {
        p_cell.m_neighbors[13][i].clear ();
    }
    for (i = 0; i < p_cell.m_neighbors[13].size (); i++) {
        for (j = 0; j < i; j++) {
            data_type dx = p_cell.m_positions_x[p_idx_a][i] - p_cell.m_positions_x[p_idx_a][j];
            data_type dy = p_cell.m_positions_y[p_idx_a][i] - p_cell.m_positions_y[p_idx_a][j];
            data_type dz = p_cell.m_positions_z[p_idx_a][i] - p_cell.m_positions_z[p_idx_a][j];
            if (cut_off_radius_squared >= (dx * dx + dy * dy + dz * dz)) {
                p_cell.m_neighbors[13][i].push_back (j);
            }
        }
    }
}
void DatastructureListBenjamin::list_rebuild (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, unsigned int p_idx_a, s_options& p_options) {
    unsigned long i;
    unsigned long j;
    unsigned int  neighbor_index = get_neighbor_index_for_cells (p_cell_i.m_idx, p_cell_j.m_idx);
    p_cell_i.m_neighbors[neighbor_index].resize (p_cell_i.m_ids.size ());
    // cut_off_radius*1.2 to allow particles to move before reconstruction of
    // lists is needed
    data_type cut_off_radius_squared = p_options.m_cut_off_radius * p_options.m_cut_off_radius * 1.2f;
    for (i = 0; i < p_cell_i.m_ids.size (); i++) {
        p_cell_i.m_neighbors[neighbor_index][i].clear ();
    }
    for (i = 0; i < p_cell_i.m_ids.size (); i++) {
        for (j = 0; j < p_cell_j.m_ids.size (); j++) {
            data_type dx = p_cell_i.m_positions_x[p_idx_a][i] - p_cell_j.m_positions_x[p_idx_a][j];
            data_type dy = p_cell_i.m_positions_y[p_idx_a][i] - p_cell_j.m_positions_y[p_idx_a][j];
            data_type dz = p_cell_i.m_positions_z[p_idx_a][i] - p_cell_j.m_positions_z[p_idx_a][j];
            if (cut_off_radius_squared >= (dx * dx + dy * dy + dz * dz)) {
                p_cell_i.m_neighbors[neighbor_index][i].push_back (j);
            }
        }
    }
}
void DatastructureListBenjamin::list_rebuild (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, unsigned int p_idx_a, s_options& p_options, data_type p_offset_x, data_type p_offset_y, data_type p_offset_z) {
    unsigned long i;
    unsigned long j;
    Vec3l         b = Vec3l (p_cell_i.m_idx);
    if (p_offset_x > 0) {
        b.x = p_cell_i.m_idx.x - 1;
    } else if (p_offset_x < 0) {
        b.x = p_cell_i.m_idx.x + 1;
    }
    if (p_offset_y > 0) {
        b.y = p_cell_i.m_idx.y - 1;
    } else if (p_offset_y < 0) {
        b.y = p_cell_i.m_idx.y + 1;
    }
    if (p_offset_z > 0) {
        b.z = p_cell_i.m_idx.z - 1;
    } else if (p_offset_z < 0) {
        b.z = p_cell_i.m_idx.z + 1;
    }
    unsigned int neighbor_index = get_neighbor_index_for_cells (p_cell_i.m_idx, b);
    p_cell_i.m_neighbors[neighbor_index].resize (p_cell_i.m_ids.size ());
    // cut_off_radius*1.2 to allow particles to move before reconstruction of
    // lists is needed
    data_type cut_off_radius_squared = p_options.m_cut_off_radius * p_options.m_cut_off_radius * 1.2f;
    for (i = 0; i < p_cell_i.m_ids.size (); i++) {
        p_cell_i.m_neighbors[neighbor_index][i].clear ();
    }
    for (i = 0; i < p_cell_i.m_ids.size (); i++) {
        for (j = 0; j < p_cell_j.m_ids.size (); j++) {
            data_type dx = p_cell_i.m_positions_x[p_idx_a][i] + p_offset_x - p_cell_j.m_positions_x[p_idx_a][j];
            data_type dy = p_cell_i.m_positions_y[p_idx_a][i] + p_offset_y - p_cell_j.m_positions_y[p_idx_a][j];
            data_type dz = p_cell_i.m_positions_z[p_idx_a][i] + p_offset_z - p_cell_j.m_positions_z[p_idx_a][j];
            if (cut_off_radius_squared >= (dx * dx + dy * dy + dz * dz)) {
                p_cell_i.m_neighbors[neighbor_index][i].push_back (j);
            }
        }
    }
}
int DatastructureListBenjamin::get_neighbor_index_for_cells (Vec3l& p_idx_i, Vec3l& p_idx_j) {
    return (p_idx_j.x - p_idx_i.x + 1) * 9 + (p_idx_j.y - p_idx_i.y + 1) * 3 + (p_idx_j.z - p_idx_i.z + 1);
}
