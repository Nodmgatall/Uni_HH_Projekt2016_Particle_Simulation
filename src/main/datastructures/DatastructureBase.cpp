/*
 * DatastructureBase.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include <datastructures/DatastructureNeighborList.hpp>
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
e_datastructure_type DatastructureBase::get_structure_type () {
    exit (1); // Never call this
}
void DatastructureBase::serialize () {
    if (m_options.m_output_type != e_output_type::VOID) {
        Benchmark::begin ("saving the data", false);
        m_writer.start ();
        size_t idx;
        for (idx = 0; idx < m_particle_groups_count; idx++) {
            if (!(m_particle_groups[idx].m_ids.empty ())) {
                m_writer.saveData (m_particle_groups[idx].m_positions_x[m_idx_a],
                                   m_particle_groups[idx].m_positions_y[m_idx_a],
                                   m_particle_groups[idx].m_positions_z[m_idx_a],
                                   m_particle_groups[idx].m_ids);
            }
        }
        m_writer.end ();
        Benchmark::end ();
    }
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
void DatastructureBase::add_particle_internal (Vec3f p_current_position, Vec3f p_last_position, int p_id) {
    long id = 0;
    if (p_id >= 0) {
        id       = p_id;
        m_max_id = MAX (m_max_id, p_id + 1);
    } else {
        id = m_max_id++;
    }
    m_border.updatePosition (p_current_position.x, p_current_position.y, p_current_position.z, p_last_position.x, p_last_position.y, p_last_position.z);
    m_particle_groups[0].add_particle (p_current_position, p_last_position, m_idx_a, id);
}
void DatastructureBase::add_particle (Vec3f p_position) {
    add_particle (p_position, Vec3f (0));
}
unsigned long DatastructureBase::get_particle_count () {
    unsigned long particle_count = 0;
    size_t        idx;
    for (idx = 0; idx < m_particle_groups_count; idx++) {
        particle_count += m_particle_groups[idx].m_ids.size ();
    }
    return particle_count;
}
void DatastructureBase::calculate_next_datastructure_rebuild () { // calculate, when the datastructure should be rebuild
    unsigned int i, j;
    data_type    v_max_x = 0.00001; // do not devide through 0
    data_type    v_max_y = 0.00001; // do not devide through 0
    data_type    v_max_z = 0.00001; // do not devide through 0
    data_type    v_max   = 0.00001; // do not devide through 0
    for (i = 0; i < m_particle_groups_count; i++) {
        ParticleGroup& group = m_particle_groups[i];
        for (j = 0; j < group.m_ids.size (); j++) {
            v_max_x = MAX (v_max_x, fabs (group.m_positions_x[m_idx_b][j] - group.m_positions_x[m_idx_a][j]));
            v_max_y = MAX (v_max_y, fabs (group.m_positions_y[m_idx_b][j] - group.m_positions_y[m_idx_a][j]));
            v_max_z = MAX (v_max_z, fabs (group.m_positions_z[m_idx_b][j] - group.m_positions_z[m_idx_a][j]));
        }
    }
    //*2 -> (*4 inside sqrt) because particles might speed up
    v_max = sqrt (v_max_x * v_max_x * 4 + v_max_y * v_max_y * 4 + v_max_z * v_max_z * 4);
    // always decreasing value (MIN with old value)
    // Maximum with 1 to avoid negative values
    m_iterations_until_rearange_particles = MAX (MIN (m_iterations_since_rearange_particles, MIN (m_options.m_max_iterations_between_datastructure_rebuild, (m_speed_factor / v_max))), 1); //
    m_verbose_stream << "m_iterations_until_rearange_particles " << (m_iterations_until_rearange_particles) << " - " //
                     << (m_speed_factor) << " - "                                                                    //
                     << (v_max) << " - "                                                                             //
                     << (m_speed_factor / v_max) << std::endl;
    m_iterations_since_rearange_particles = m_iterations_until_rearange_particles;
}
void DatastructureBase::analyse () {
    m_options.m_initial_speed = 0;
    m_standard_stream << DEBUG_VAR (m_options.m_initial_speed) << std::endl;
    m_options.m_input_type = e_input_type::AUTOTUNING_ERROR;
    if (m_options.m_particle_count) {
        // variables for statistics -->>
        unsigned long sum_interaction_count = 0;
        unsigned long avg_interaction_count_by_data;
        float         avg_place_per_particle;
        float         avg_interaction_count_by_cut_off;
        float         volume_included_in_cut_off;
        float         total_volume = m_options.m_bounds.x * m_options.m_bounds.y * m_options.m_bounds.z;
        float         total_volume_by_data;
        float         cut_off_3                       = m_options.m_cut_off_radius * m_options.m_cut_off_radius * m_options.m_cut_off_radius;
        unsigned long particle_count                  = m_options.m_particle_count;
        unsigned long cells_with_nearly_none_particle = 0;
        data_type     xl                              = 999999999999;
        data_type     yl                              = 999999999999;
        data_type     zl                              = 999999999999;
        data_type     xr                              = -999999999999;
        data_type     yr                              = -999999999999;
        data_type     zr                              = -999999999999;
        // variables for statistics <<--
        unsigned long i;
        /**
         * particles_in_cell_count simulates a 10x10x10 grid layout and counts, how many particles are in each cell.
         */
        int particles_in_cell_count[1000];
        memset (&particles_in_cell_count[0], 0, 1000 * sizeof (int));
        data_type v_max_x = 0.0;
        data_type v_max_y = 0.0;
        data_type v_max_z = 0.0;
        size_t    idx;
        for (idx = 0; idx < m_particle_groups_count; idx++) {
            for (i = 0; i < m_particle_groups[idx].m_ids.size (); i++) {
                data_type ax = m_particle_groups[idx].m_positions_x[m_idx_a][i];
                data_type ay = m_particle_groups[idx].m_positions_y[m_idx_a][i];
                data_type az = m_particle_groups[idx].m_positions_z[m_idx_a][i];
                data_type bx = m_particle_groups[idx].m_positions_x[m_idx_b][i];
                data_type by = m_particle_groups[idx].m_positions_y[m_idx_b][i];
                data_type bz = m_particle_groups[idx].m_positions_z[m_idx_b][i];
                v_max_x      = MAX (v_max_x, fabs (bx - ax));
                v_max_y      = MAX (v_max_y, fabs (by - ay));
                v_max_z      = MAX (v_max_z, fabs (bz - az));
                particles_in_cell_count[(((int) (fabs (ax) * 10.0 / m_options.m_bounds.x)) % 10) * 100 + //
                                        (((int) (fabs (ay) * 10.0 / m_options.m_bounds.y)) % 10) * 10 +  //
                                        (((int) (fabs (az) * 10.0 / m_options.m_bounds.z)) % 10)]++;
            }
        }
        total_volume_by_data             = (xr - xl) * (yr - yl) * (zr - zl);
        avg_interaction_count_by_data    = sum_interaction_count / particle_count;
        avg_place_per_particle           = (total_volume_by_data) / particle_count;
        volume_included_in_cut_off       = 4 / 3 * M_PI * cut_off_3;
        avg_interaction_count_by_cut_off = volume_included_in_cut_off / avg_place_per_particle;
        for (i = 0; i < 1000; i++) {
            if ((unsigned) particles_in_cell_count[i] < particle_count / 10000) {
                // if a cell has less particles than 1/10 from the average case
                cells_with_nearly_none_particle++;
            }
        }
        if (cells_with_nearly_none_particle > 300) {
            m_options.m_input_type = e_input_type::AUTOTUNING_IRREGULAR_DISTRIBUTION;
        } else {
            m_options.m_input_type = e_input_type::AUTOTUNING_REGULAR_DISTRIBUTION;
        }
        m_options.m_initial_speed = sqrt (v_max_x * v_max_x + v_max_y * v_max_y + v_max_z * v_max_z);
        m_standard_stream << DEBUG_VAR (m_options.m_initial_speed) << std::endl;
        m_verbose_stream << DEBUG_VAR (total_volume_by_data) << std::endl;
        m_verbose_stream << DEBUG_VAR (avg_interaction_count_by_data) << std::endl;
        m_verbose_stream << DEBUG_VAR (avg_place_per_particle) << std::endl;
        m_verbose_stream << DEBUG_VAR (volume_included_in_cut_off) << std::endl;
        m_verbose_stream << DEBUG_VAR (avg_interaction_count_by_cut_off) << std::endl;
        m_verbose_stream << DEBUG_VAR (total_volume) << std::endl;
    }
}
void DatastructureBase::transfer_particles_to (DatastructureBase* p_datastructure) {
    unsigned long i;
    size_t        idx;
    for (idx = 0; idx < m_particle_groups_count; idx++) {
        for (i = 0; i < m_particle_groups[idx].m_ids.size (); i++) {
            p_datastructure->add_particle_internal (
                Vec3f (m_particle_groups[idx].m_positions_x[m_idx_a][i], m_particle_groups[idx].m_positions_y[m_idx_a][i], m_particle_groups[idx].m_positions_z[m_idx_a][i]),
                Vec3f (m_particle_groups[idx].m_positions_x[m_idx_b][i], m_particle_groups[idx].m_positions_y[m_idx_b][i], m_particle_groups[idx].m_positions_z[m_idx_b][i]),
                m_particle_groups[idx].m_ids[i]);
        }
    }
}
