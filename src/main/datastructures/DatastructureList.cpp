#include <cmath>
#include <iostream>
#include <vector>

#include "DatastructureList.hpp"
#include "Vec3.hpp"
#include "tools/Debug.hpp"

DatastructureList::DatastructureList (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer),
  m_average_list_length (0.16), m_next_list_size_multiplier (1.1) {
    m_stucture_name                  = "DatastructureList";
    m_cutoff_radius                  = 0;
    m_last_id                        = 0;
    m_duration_list                  = 0;
    m_cnt_iterations_without_rebuild = 1;
    macro_debug_1 ("constructor of ParticleList called")
}
DatastructureList::~DatastructureList () {
}

void DatastructureList::add_particle (Vec3f p_position) {
    if (!m_unused_ids.empty ()) {
        m_unused_ids.erase (m_unused_ids.begin ());
        m_standard_stream << "Not implemented: program will exit" << std::endl;
        exit (EXIT_SUCCESS);
    } else {
        m_particle_ids.push_back (m_last_id++);
        /*
            m_velocities_x_now.push_back (0);
            m_velocities_y_now.push_back (0);
            m_velocities_z_now.push_back (0);
        */
        m_positions_x_now.push_back (p_position.x);
        m_positions_y_now.push_back (p_position.y);
        m_positions_z_now.push_back (p_position.z);

        m_positions_x_old.push_back (p_position.x);
        m_positions_y_old.push_back (p_position.y);
        m_positions_z_old.push_back (p_position.z);
        /*
            m_accelerations_x_now.push_back (0);
            m_accelerations_y_now.push_back (0);
            m_accelerations_z_now.push_back (0);
        */
    }
}

void DatastructureList::add_particle (Vec3f p_position, Vec3f p_velocity, int p_id) {
    (void) p_velocity;
    add_particle (p_position);
    (void) p_id;
    //    add_particle (p_position); // TODO
}

void DatastructureList::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
    unsigned long particle_count = m_positions_x_now.size ();
    for (unsigned long particle_idx = 0; particle_idx < particle_count - 1; particle_idx++) {
        if (p_iteration_number % 20 == 0) {
            build_lists ();
        }
        m_algorithm.step_1 (m_positions_x_old[particle_idx],
                            m_positions_y_old[particle_idx],
                            m_positions_z_old[particle_idx],
                            m_positions_x_now[particle_idx],
                            m_positions_y_now[particle_idx],
                            m_positions_z_now[particle_idx]);

        for (unsigned long list_idx = m_neighbour_idxs_list[particle_idx];
             list_idx < m_neighbour_idxs_list[particle_idx + 1];
             list_idx++) {
            m_algorithm.step_2 (m_positions_x_old[particle_idx],
                    m_positions_y_old[particle_idx],
                    m_positions_z_old[particle_idx],
                    m_positions_x_now[particle_idx],
                    m_positions_y_now[particle_idx],
                    m_positions_z_now[particle_idx],
                    &m_positions_x_old[list_idx],
                    &m_positions_y_old[list_idx],
                    &m_positions_z_old[list_idx],
                    &m_positions_x_now[list_idx],
                    &m_positions_y_now[list_idx],
                    &m_positions_z_now[list_idx],
                    0,
                    1);
        }
    }
}

void DatastructureList::build_lists () {
    unsigned long particle_count          = m_positions_x_now.size ();
    unsigned long neighbour_count         = 0;
    unsigned long neighbour_idx_list_size = particle_count * (particle_count * 0.16);
    // TODO: shell thickness done right
    m_shell_thickness              = 0.0;
    data_type              cut_off = m_options.m_cut_off_radius + m_shell_thickness;
    std::vector<data_type> distances;

    m_neighbour_idxs_list.reserve (neighbour_idx_list_size);
    m_neighbour_section_idxs.push_back (0);
    // for each particle
    for (unsigned long particle_idx = 0; particle_idx < particle_count - 1; particle_idx++) {
        unsigned long range = particle_count - particle_idx;
        distances.resize (range);
        calculate_distances_squared (particle_idx, &distances[0]);

        for (unsigned long dist_idx = 0; dist_idx < range; dist_idx++) {
            if (distances[dist_idx] < cut_off) {
                m_neighbour_idxs_list.push_back (particle_idx + 1 + dist_idx);
                neighbour_count++;
            }
        }
        m_neighbour_section_idxs.push_back (neighbour_count);
    }
}

/**
 *  this functions takes a range of positions and a index of a particle of wich
 * we want to
 *  know the distances to each particle in the range.
 */

void DatastructureList::calculate_distances_squared (unsigned long particle_idx, data_type* p_distances_squared) {
    Benchmark::begin ("Calculating Distances", false);

    unsigned long cur_part_idx;

    // square every entry in vector:
    // x
    data_type     x              = m_positions_x_now[particle_idx];
    data_type     y              = m_positions_y_now[particle_idx];
    data_type     z              = m_positions_z_now[particle_idx];
    unsigned long particle_count = m_positions_x_now.size ();
    unsigned long start          = particle_idx + 1;
    for (cur_part_idx = 0; cur_part_idx < particle_count; cur_part_idx++) {
        p_distances_squared[cur_part_idx] = std::pow (x - m_positions_x_now[cur_part_idx + start], 2) +
                                            std::pow (y - m_positions_y_now[cur_part_idx + start], 2) +
                                            std::pow (z - m_positions_z_now[cur_part_idx + start], 2);
    }
}

void DatastructureList::serialize () {
    Benchmark::begin ("saving the data", false);
    m_writer.start ();
    m_writer.saveData (m_positions_x_now, m_positions_y_now, m_positions_z_now, m_particle_ids);
    m_writer.end ();
    Benchmark::end ();
}
/* most likely not used
 void ParticlesList::update_original_vectors (unsigned long p_start_idx,
 unsigned long
 p_segment_length) {

 get_current_status (p_start_idx,
 p_segment_length,
 &m_positions_x,
 &m_positions_y,
 &m_positions_z,
 &m_velocities_x,
 &m_velocities_y,
 &m_velocities_z,
 &m_accelerations_x,
 &m_accelerations_y,
 &m_accelerations_z);
 }
 */

data_type DatastructureList::calculate_cnt_average_neighbours () {
    data_type accum_neighbours = 0;
    for (unsigned long i = 1; i < m_neighbour_idxs_list.size () - 1; i++) {
        accum_neighbours = m_neighbour_idxs_list[i + 1] - m_neighbour_idxs_list[i];
    }
    accum_neighbours /= get_particle_count ();
    return accum_neighbours;
}

data_type DatastructureList::get_cnt_average_neighbours () {
    return m_average_list_length;
}

unsigned long DatastructureList::get_particle_count () {
    return m_positions_x_now.size ();
}
