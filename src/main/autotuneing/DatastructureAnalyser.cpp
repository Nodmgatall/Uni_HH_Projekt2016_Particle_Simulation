/*
 * DatastructureAnalyser.cpp
 *
 *  Created on: 21.01.2017
 *      Author: benjamin
 */

#include <autotuneing/DatastructureAnalyser.hpp>

/*m_idx_a -> position*/
/*m_idx_a -> velocity*/
DatastructureAnalyser::DatastructureAnalyser (s_options&     p_options,
                                              BorderBase&    p_border,
                                              AlgorithmBase& p_algorithm,
                                              WriterBase&    p_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_writer) {
    m_stucture_name = "DatastructureAnalyser";
    m_particle_groups.push_back (ParticleGroup (Vec3l (), m_options.m_bounds));
}

DatastructureAnalyser::~DatastructureAnalyser () {
}

void DatastructureAnalyser::transfer_particles_to (DatastructureBase& p_datastructure) {
    unsigned long i;
    for (i = 0; i < get_particle_count (); i++) {
        p_datastructure.add_particle (Vec3f (m_particle_groups[0].m_positions_x[m_idx_a][i],
                                             m_particle_groups[0].m_positions_y[m_idx_a][i],
                                             m_particle_groups[0].m_positions_z[m_idx_a][i]),
                                      Vec3f (m_particle_groups[0].m_positions_x[m_idx_b][i],
                                             m_particle_groups[0].m_positions_y[m_idx_b][i],
                                             m_particle_groups[0].m_positions_z[m_idx_b][i]),
                                      m_particle_groups[0].m_ids[i]);
    }
}
e_datastructure_type DatastructureAnalyser::analyse () {
    if (m_particle_groups[0].m_ids.size () > 0) {
        // variables for statistics -->>
        std::vector<unsigned long> interaction_count; // each interaction-pair count just once
        unsigned long              sum_interaction_count = 0;
        unsigned long              avg_interaction_count_by_data;
        float                      avg_place_per_particle;
        float                      avg_interaction_count_by_cut_off;
        float                      volume_included_in_cut_off;
        float total_volume = m_options.m_bounds.x * m_options.m_bounds.y * m_options.m_bounds.z;
        float total_volume_by_data;
        float cut_off_3 = m_options.m_cut_off_radius * m_options.m_cut_off_radius * m_options.m_cut_off_radius;
        data_type xl = m_particle_groups[0].m_positions_x[m_idx_a][0];
        data_type yl = m_particle_groups[0].m_positions_x[m_idx_a][0];
        data_type zl = m_particle_groups[0].m_positions_x[m_idx_a][0];
        data_type xr = xl;
        data_type yr = yl;
        data_type zr = zl;
        // variables for statistics <<--
        unsigned long i;
        unsigned long j;
        data_type cut_off_radius_squared = m_options.m_cut_off_radius * m_options.m_cut_off_radius;
        interaction_count.resize (m_particle_groups[0].m_ids.size ());
        for (i = 0; i < m_particle_groups[0].m_ids.size (); i++) {
            interaction_count[i] = 0;
            if (xl > m_particle_groups[0].m_positions_x[m_idx_a][i])
                xl = m_particle_groups[0].m_positions_x[m_idx_a][i];
            if (xr < m_particle_groups[0].m_positions_x[m_idx_a][i])
                xr = m_particle_groups[0].m_positions_x[m_idx_a][i];
            if (yl > m_particle_groups[0].m_positions_y[m_idx_a][i])
                yl = m_particle_groups[0].m_positions_y[m_idx_a][i];
            if (yr < m_particle_groups[0].m_positions_y[m_idx_a][i])
                yr = m_particle_groups[0].m_positions_y[m_idx_a][i];
            if (zl > m_particle_groups[0].m_positions_z[m_idx_a][i])
                zl = m_particle_groups[0].m_positions_z[m_idx_a][i];
            if (zr < m_particle_groups[0].m_positions_z[m_idx_a][i])
                zr = m_particle_groups[0].m_positions_z[m_idx_a][i];
            for (j = 0; j < i; j++) {
                data_type dx = m_particle_groups[0].m_positions_x[m_idx_a][i] -
                               m_particle_groups[0].m_positions_x[m_idx_a][j];
                data_type dy = m_particle_groups[0].m_positions_y[m_idx_a][i] -
                               m_particle_groups[0].m_positions_y[m_idx_a][j];
                data_type dz = m_particle_groups[0].m_positions_z[m_idx_a][i] -
                               m_particle_groups[0].m_positions_z[m_idx_a][j];
                if (cut_off_radius_squared >= (dx * dx + dy * dy + dz * dz)) {
                    interaction_count[i]++;
                    sum_interaction_count++;
                }
            }
        }
        total_volume_by_data          = (xr - xl) * (yr - yl) * (zr - zl);
        avg_interaction_count_by_data = sum_interaction_count / m_particle_groups[0].m_ids.size ();
        avg_place_per_particle        = (total_volume_by_data) / m_particle_groups[0].m_ids.size ();
        volume_included_in_cut_off    = 4 / 3 * M_PI * cut_off_3;
        avg_interaction_count_by_cut_off = volume_included_in_cut_off / avg_place_per_particle;
        if (total_volume_by_data < total_volume / 20.0) {
            // only a small piece of the volume is used by the particles
            return e_datastructure_type::LIST_BENJAMIN;
        }
        if (avg_place_per_particle > volume_included_in_cut_off / 8.0) {
            // in the average there are less than 8 particles in a cell
            return e_datastructure_type::GRID;
        }
        if (avg_interaction_count_by_data < avg_interaction_count_by_cut_off / 2.0) {
            // real interactions are much smaller then that what is expected by grid usage
            return e_datastructure_type::LISTEDGIRD;
        }
    } else {
        // error cannot analyse not existing data
    }
    return e_datastructure_type::GRID;
}
void DatastructureAnalyser::add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id) {
    long id = 0;
    if (p_id >= 0) {
        id       = p_id;
        m_max_id = MAX (m_max_id, p_id + 1);
    } else {
        id = m_max_id++;
    }
    m_particle_groups[0].add_particle (p_current_position, p_current_velocity, m_idx_a, id);
}
void DatastructureAnalyser::add_particle (Vec3f p_position) {
    add_particle (p_position, Vec3f (0));
}
