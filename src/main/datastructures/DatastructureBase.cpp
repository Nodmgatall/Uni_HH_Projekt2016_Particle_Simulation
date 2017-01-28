/*
 * DatastructureBase.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */
#include "DatastructureListBenjamin.hpp"
void DatastructureBase::step_1_prepare_cell (ParticleGroup& p_cell) {
    unsigned int       i;
    const unsigned int max = p_cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        m_algorithm.step_1 (p_cell.m_positions_x[m_idx_a][i],
                            p_cell.m_positions_y[m_idx_a][i],
                            p_cell.m_positions_z[m_idx_a][i],
                            p_cell.m_positions_x[m_idx_b][i],
                            p_cell.m_positions_y[m_idx_b][i],
                            p_cell.m_positions_z[m_idx_b][i]);
    }
}
void DatastructureBase::step_3_fit_into_borders (ParticleGroup& p_cell) {
    m_border.updatePosition (p_cell, m_idx_a, m_error_happened);
}
void DatastructureBase::serialize () {
    Benchmark::begin ("saving the data", false);
    m_writer.start ();
    for (ParticleGroup cell : m_particle_groups) {
        if (!(cell.m_ids.empty ())) {
            m_writer.saveData (cell.m_positions_x[m_idx_a], cell.m_positions_y[m_idx_a], cell.m_positions_z[m_idx_a], cell.m_ids);
        }
    }
    m_writer.end ();
    Benchmark::end ();
}
bool DatastructureBase::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
    return true; // this should never be called !!!!! -> return error
}
void DatastructureBase::add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id) {
    long id = 0;
    if (p_id >= 0) {
        id       = p_id;
        m_max_id = MAX (m_max_id, p_id + 1);
    } else {
        id = m_max_id++;
    }
    Vec3f old_position = p_current_position - p_current_velocity * m_options.m_timestep;
    m_border.updatePosition (p_current_position.x, p_current_position.y, p_current_position.z, old_position.x, old_position.y, old_position.z);
    m_particle_groups[0].add_particle (p_current_position, old_position, m_idx_a, id);
}
void DatastructureBase::add_particle (Vec3f p_position) {
    add_particle (p_position, Vec3f (0));
}
unsigned long DatastructureBase::get_particle_count () {
    unsigned long particle_count = 0;
    for (ParticleGroup cell : m_particle_groups) {
        particle_count += cell.m_ids.size ();
    }
    return particle_count;
}
void DatastructureBase::calculate_next_datastructure_rebuild () { // calculate, when the datastructure should be rebuild
    unsigned int i, j;
    data_type    v_max = 0.00001; // do not devide through 0
    for (i = 0; i < m_particle_groups.size (); i++) {
        ParticleGroup& group = m_particle_groups[i];
        for (j = 0; j < group.m_ids.size (); j++) {
            v_max = MAX (v_max, fabs (group.m_positions_x[m_idx_b][j] - group.m_positions_x[m_idx_a][j]));
            v_max = MAX (v_max, fabs (group.m_positions_y[m_idx_b][j] - group.m_positions_y[m_idx_a][j]));
            v_max = MAX (v_max, fabs (group.m_positions_z[m_idx_b][j] - group.m_positions_z[m_idx_a][j]));
        }
    }
    // always decreasing value
    m_iterations_until_rearange_particles =
        MAX (MIN (m_iterations_since_rearange_particles, MIN (m_options.m_max_iterations_between_datastructure_rebuild, log (m_speed_factor / v_max))), 1); // 1 == immediately
    m_verbose_stream << "m_iterations_until_rearange_particles " << (m_iterations_until_rearange_particles) << " - "                                        //
                     << (m_speed_factor) << " - "                                                                                                           //
                     << (v_max) << " - "                                                                                                                    //
                     << (m_speed_factor / v_max) << " - "                                                                                                   //
                     << (log (m_speed_factor / v_max)) << std::endl;
    m_iterations_since_rearange_particles = m_iterations_until_rearange_particles;
}
