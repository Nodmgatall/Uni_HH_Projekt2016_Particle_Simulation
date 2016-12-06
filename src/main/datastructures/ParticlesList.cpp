#include "../vec3.hpp"
#include <iostream>
#include <vector>

#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include "../tools/Debug.hpp"
#include "ParticlesList.hpp"

ParticlesList::ParticlesList (s_simulator_options *p_options, vec3f *p_bounds)
: ParticlesBase (p_options, p_bounds), m_average_list_length (0.16), m_next_list_size_multiplier (1.1) {
    m_stucture_name                  = "List";
    m_cutoff_radius                  = 0;
    m_last_id                        = 0;
    m_duration_list                  = 0;
    m_cnt_iterations_without_rebuild = 0;
    macro_debug_1 ("constructor of ParticleList called")
}
ParticlesList::~ParticlesList () {
}

void ParticlesList::add_particle (vec3f p_position) {
    if (!m_unused_ids.empty ()) {
        m_unused_ids.erase (m_unused_ids.begin ());
        std::cout << "Not implemented: program will exit" << std::endl;
        exit (EXIT_SUCCESS);
    } else {
        m_particle_ids.push_back (m_last_id++);
        m_velocities_x.push_back (0);
        m_velocities_y.push_back (0);
        m_velocities_z.push_back (0);

        m_positions_x.push_back (p_position.x);
        m_positions_y.push_back (p_position.y);
        m_positions_z.push_back (p_position.z);

        m_accelerations_x.push_back (0);
        m_accelerations_y.push_back (0);
        m_accelerations_z.push_back (0);
    }
}
void ParticlesList::add_particle (vec3f p_position, vec3f p_velocity) {
    add_particle (p_position); // TODO
}

void ParticlesList::run_simulation_iteration (unsigned long p_iteration_number) {
    macro_debug_1 ("running iteration") setup_iteration ();
    unsigned long particle_count = m_positions_x.size ();
    unsigned long last_particle  = particle_count - 1;
    //    unsigned long neighbour_cnt;
    unsigned long size_distances_vector = ((particle_count * particle_count) - particle_count) / 2;
    std::vector<float> distances_x (size_distances_vector);
    std::vector<float> distances_y (size_distances_vector);
    std::vector<float> distances_z (size_distances_vector);
    std::vector<float> distances_squared (size_distances_vector);
    // for each particle go over list
    if (p_iteration_number % m_cnt_iterations_without_rebuild == 0) {
        /* clang-format off */
        build_lists_smarter (&distances_x[0],
                             &distances_y[0],
                             &distances_z[0],
                             &distances_squared[0], size_distances_vector);
        /* clang-format on */
    } else {
        unsigned long start_pos_distance_vector = 0;
        for (unsigned long particle_idx = 0; particle_idx < last_particle; particle_idx++) {
            calculate_distance_vectors (particle_idx,
                                        &distances_x[start_pos_distance_vector],
                                        &distances_y[start_pos_distance_vector],
                                        &distances_z[start_pos_distance_vector],
                                        &m_positions_x[particle_idx + 1],
                                        &m_positions_y[particle_idx + 1],
                                        &m_positions_z[particle_idx + 1],
                                        particle_idx + 1,
                                        particle_count);
            start_pos_distance_vector += (particle_count - particle_idx - 1);
        }

        // calculating distance skalar from the distance vectors
        for (unsigned long distances_idx = 0; distances_idx < size_distances_vector; distances_idx++) {
            /* clang-format off */
            calculate_distances_squared (&distances_squared[0],
                                         &distances_x[0],
                                         &distances_y[0],
                                         &distances_z[0],
                                         size_distances_vector);
            /* clang-format on */
        }
    }

    //    for (unsigned long neighbour_idx = 0; neighbour_idx < neighbour_cnt; neighbour_idx++) {
    // calculate force
    //
    //  }
    // summ
    macro_debug_1 ("iteration done")
}

unsigned long ParticlesList::get_particle_count () {
    return m_positions_x.size ();
}

void ParticlesList::build_lists_smarter (float *       p_distances_x,
                                         float *       p_distances_y,
                                         float *       p_distances_z,
                                         float *       p_distances_squared,
                                         unsigned long p_size_distance_vectors) {
    unsigned long particle_count        = m_positions_x.size ();
    unsigned long size_distances_vector = ((particle_count * particle_count) - particle_count) / 2;
    unsigned long start_pos_distance_vector = 0;
    float         cutoff_radius_squared     = 0.8;
    std::vector<float> distances (size_distances_vector);
    unsigned long      listed_size = particle_count * (particle_count * (0.25));
    std::cout << "listed size: " << listed_size << std::endl;
    m_listed_positions_x.reserve (listed_size);
    m_listed_positions_y.reserve (listed_size);
    m_listed_positions_z.reserve (listed_size);

    m_listed_velocities_x.reserve (listed_size);
    m_listed_velocities_y.reserve (listed_size);
    m_listed_velocities_z.reserve (listed_size);

    std::vector<float> distances_squared (p_size_distance_vectors);

    // calculating distance vectors for (n^2 -n)/2 pairs
    for (unsigned long particle_idx = 0; particle_idx < particle_count - 1; particle_idx++) {
        calculate_distance_vectors (particle_idx,
                                    &p_distances_x[start_pos_distance_vector],
                                    &p_distances_y[start_pos_distance_vector],
                                    &p_distances_z[start_pos_distance_vector],
                                    &m_positions_x[particle_idx + 1],
                                    &m_positions_y[particle_idx + 1],
                                    &m_positions_z[particle_idx + 1],
                                    particle_idx + 1,
                                    particle_count);
        start_pos_distance_vector += (particle_count - particle_idx - 1);
    }

    // calculating distance skalar from the distance vectors
    for (unsigned long distances_idx = 0; distances_idx < size_distances_vector; distances_idx++) {
        calculate_distances_squared (&p_distances_squared[0],
                                     &p_distances_x[0],
                                     &p_distances_y[0],
                                     &p_distances_z[0],
                                     size_distances_vector);
    }

    // building list
    for (unsigned long distance_section_start = 0, range = particle_count - 1;
         distance_section_start < size_distances_vector;
         distance_section_start += range, range--) {
        unsigned long current_idx = particle_count - 1 - range;
        for (unsigned long dist_vector_part_idx = 0; dist_vector_part_idx < range; dist_vector_part_idx++) {
            if (p_distances_squared[distance_section_start + dist_vector_part_idx] < cutoff_radius_squared) {
                /* clang-format off */
                m_mat_positions_x[current_idx].push_back(m_positions_x[dist_vector_part_idx + current_idx + 1]);
                m_mat_positions_y[current_idx].push_back(m_positions_y[dist_vector_part_idx + current_idx + 1]);
                m_mat_positions_z[current_idx].push_back(m_positions_z[dist_vector_part_idx + current_idx + 1]);

                m_mat_velocities_x[current_idx].push_back(m_velocities_x[dist_vector_part_idx + current_idx + 1]);
                m_mat_velocities_y[current_idx].push_back(m_velocities_y[dist_vector_part_idx + current_idx + 1]);
                m_mat_velocities_z[current_idx].push_back(m_velocities_z[dist_vector_part_idx + current_idx + 1]);

                m_mat_positions_x[dist_vector_part_idx + current_idx + 1].push_back(m_positions_x[current_idx]);
                m_mat_positions_y[dist_vector_part_idx + current_idx + 1].push_back(m_positions_y[current_idx]);
                m_mat_positions_z[dist_vector_part_idx + current_idx + 1].push_back(m_positions_z[current_idx]);

                m_mat_velocities_x[dist_vector_part_idx + current_idx + 1].push_back(m_velocities_x[current_idx]);
                m_mat_velocities_y[dist_vector_part_idx + current_idx + 1].push_back(m_velocities_y[current_idx]);
                m_mat_velocities_z[dist_vector_part_idx + current_idx + 1].push_back(m_velocities_z[current_idx]);
                /* clang-format on */
            }
            if (m_mat_positions_x.size () == listed_size) {
                listed_size = listed_size * (listed_size * 0.16);
                m_listed_positions_x.reserve (listed_size);
                m_listed_positions_y.reserve (listed_size);
                m_listed_positions_z.reserve (listed_size);

                m_listed_velocities_x.reserve (listed_size);
                m_listed_velocities_y.reserve (listed_size);
                m_listed_velocities_z.reserve (listed_size);
            }
        }
    }
    m_listed_positions_x.shrink_to_fit ();
    m_listed_positions_y.shrink_to_fit ();
    m_listed_positions_z.shrink_to_fit ();

    m_listed_velocities_x.shrink_to_fit ();
    m_listed_velocities_y.shrink_to_fit ();
    m_listed_velocities_z.shrink_to_fit ();
}

void ParticlesList::build_lists () {
    macro_debug_1 ("starting building neighbour lists");
    unsigned long particle_cnt          = get_particle_count ();
    float         cutoff_radius_squared = 0.8;
    unsigned long current_list_idx      = 0;
    unsigned long next_free_list_entry  = 0;

    // TODO: Idea: dont let them be initialized each time we need to build the lists
    // instead make them a member; pro: minmal performance improvement, con: memory need * (4/3)
    unsigned long listed_size = particle_cnt * (particle_cnt * (0.25));
    std::cout << "listed size: " << listed_size << std::endl;
    m_listed_positions_x.resize (listed_size);
    m_listed_positions_y.resize (listed_size);
    m_listed_positions_z.resize (listed_size);

    m_listed_velocities_x.resize (listed_size);
    m_listed_velocities_y.resize (listed_size);
    m_listed_velocities_z.resize (listed_size);

    std::vector<float> distances_x (particle_cnt);
    std::vector<float> distances_y (particle_cnt);
    std::vector<float> distances_z (particle_cnt);

    unsigned long current_entries = 0;
    m_particle_list_ranges        = std::vector<unsigned long> (listed_size * 2);
    std::vector<float> distances_squared (particle_cnt - 1);
    for (unsigned long cur_idx = 0; cur_idx < particle_cnt; cur_idx++) {
        // in front of idx;
        calculate_distance_vectors (cur_idx,
                                    &distances_x[0],
                                    &distances_y[0],
                                    &distances_z[0],
                                    &m_positions_x[0],
                                    &m_positions_y[0],
                                    &m_positions_z[0],
                                    0,
                                    cur_idx);
        // after idx
        calculate_distance_vectors (cur_idx,
                                    &distances_x[cur_idx + 1],
                                    &distances_y[cur_idx + 1],
                                    &distances_z[cur_idx + 1],
                                    &m_positions_x[cur_idx + 1],
                                    &m_positions_y[cur_idx + 1],
                                    &m_positions_z[cur_idx + 1],
                                    cur_idx + 1,
                                    particle_cnt);

        calculate_distances_squared (
            &distances_squared[0], &distances_x[0], &distances_y[0], &distances_z[0], particle_cnt - 1);
        m_particle_list_ranges[current_list_idx] = next_free_list_entry;
        current_list_idx++;

        int cnt_neighbours = 0;
        for (unsigned long other_idx = 0; other_idx < particle_cnt - 1; other_idx++) {

            if (distances_squared[other_idx] < cutoff_radius_squared) {
                m_listed_positions_x[next_free_list_entry]  = m_positions_x[other_idx];
                m_listed_positions_y[next_free_list_entry]  = m_positions_y[other_idx];
                m_listed_positions_z[next_free_list_entry]  = m_positions_z[other_idx];
                m_listed_velocities_x[next_free_list_entry] = m_velocities_x[other_idx];
                m_listed_velocities_y[next_free_list_entry] = m_velocities_y[other_idx];
                m_listed_velocities_z[next_free_list_entry] = m_velocities_z[other_idx];
                next_free_list_entry++;
                current_entries++;
                cnt_neighbours++;
            }

            if (current_entries == m_listed_positions_x.size ()) {

                listed_size = listed_size * m_next_list_size_multiplier;
                macro_debug ("resizing lists to: ", listed_size)

                        std::cout
                    << "lol " << current_entries << " " << listed_size << std::endl;

                m_particle_list_ranges.resize (listed_size * 2);
                m_listed_positions_x.resize (listed_size);
                m_listed_positions_y.resize (listed_size);
                m_listed_positions_z.resize (listed_size);
                m_listed_velocities_x.resize (listed_size);
                m_listed_velocities_y.resize (listed_size);
                m_listed_velocities_z.resize (listed_size);
            }
        }
        macro_debug ("found neigbours cnt:", cnt_neighbours)
            m_particle_list_ranges[current_list_idx++] = next_free_list_entry;
    }
    m_particle_list_ranges.shrink_to_fit ();
    m_listed_positions_x.shrink_to_fit ();
    m_listed_positions_y.shrink_to_fit ();
    m_listed_positions_z.shrink_to_fit ();
    m_listed_velocities_x.shrink_to_fit ();
    m_listed_velocities_y.shrink_to_fit ();
    m_listed_velocities_z.shrink_to_fit ();
    macro_debug ("shrunk list ranges to: ", m_particle_list_ranges.size ())
        macro_debug ("shrunk lists to: ", m_positions_x.size ())
            macro_debug_1 ("finished building neighbour lists")
}

void ParticlesList::setup_iteration () {
    macro_debug_1 ("starting setting up iteration") int size = m_positions_x.size ();
    m_listed_accelerations_x                                 = std::vector<float> (size);
    m_listed_accelerations_y                                 = std::vector<float> (size);
    m_listed_accelerations_z                                 = std::vector<float> (size);

    if (true) {
        build_lists ();
    }
    macro_debug_1 ("finished setting up iteration")
}
/**
 *  this functions takes a range of positions and a index of a particle of wich we want to
 *  know the distances to each particle in the range.
 */

void ParticlesList::calculate_distance_vectors (unsigned long p_particle_idx,

                                                float *       p_distances_x,
                                                float *       p_distances_y,
                                                float *       p_distances_z,
                                                float *       p_positions_x,
                                                float *       p_positions_y,
                                                float *       p_positions_z,
                                                unsigned long start_idx,
                                                unsigned long end_idx) {
    unsigned long cur_dist_idx;
    unsigned long other_part_idx;
    float         x = m_positions_x[p_particle_idx];
    float         y = m_positions_y[p_particle_idx];
    float         z = m_positions_z[p_particle_idx];

    for (cur_dist_idx = 0, other_part_idx = start_idx; other_part_idx < end_idx; cur_dist_idx++, other_part_idx++) {
        p_distances_x[cur_dist_idx] = x - p_positions_x[other_part_idx];
    }

    for (cur_dist_idx = 0, other_part_idx = start_idx; other_part_idx < end_idx; cur_dist_idx++, other_part_idx++) {
        p_distances_y[cur_dist_idx] = y - p_positions_y[other_part_idx];
    }

    for (cur_dist_idx = 0, other_part_idx = start_idx; other_part_idx < end_idx; cur_dist_idx++, other_part_idx++) {
        p_distances_z[cur_dist_idx] = z - p_positions_z[other_part_idx];
    }
}
void ParticlesList::calculate_distances_squared (float *       p_distances_squared,
                                                 float *       p_distances_x,
                                                 float *       p_distances_y,
                                                 float *       p_distances_z,
                                                 unsigned long size) {
    Benchmark::begin ("Calculating Distances", false);

    unsigned long cur_part_idx;
    float         cur_pos_part;

    // square every entry in vector:
    // x
    for (cur_part_idx = 0; cur_part_idx < size; cur_part_idx++) {
        cur_pos_part                = p_distances_x[cur_part_idx];
        p_distances_x[cur_part_idx] = cur_pos_part * cur_pos_part;
    }
    // y
    for (cur_part_idx = 0; cur_part_idx < size; cur_part_idx++) {
        cur_pos_part                = p_distances_y[cur_part_idx];
        p_distances_y[cur_part_idx] = cur_pos_part * cur_pos_part;
    }

    // z
    for (cur_part_idx = 0; cur_part_idx < size; cur_part_idx++) {
        cur_pos_part                = p_distances_z[cur_part_idx];
        p_distances_z[cur_part_idx] = cur_pos_part * cur_pos_part;
    }
    // summing up the squared distances
    // frist x + y
    for (cur_part_idx = 0; cur_part_idx < size; cur_part_idx++) {
        p_distances_squared[cur_part_idx] = p_distances_x[cur_part_idx] + p_distances_y[cur_part_idx];
    }
    // then the result + z
    for (cur_part_idx = 0; cur_part_idx < size; cur_part_idx++) {
        p_distances_squared[cur_part_idx] += p_distances_z[cur_part_idx];
        macro_debug ("distance: ", p_distances_squared[cur_part_idx])
    }
    Benchmark::end ();
}

void ParticlesList::serialize (std::shared_ptr<ParticleFileWriter> p_writer) {

    Benchmark::begin ("saving the data", false);
    p_writer->saveData (&m_positions_x, &m_positions_y, &m_positions_z, &m_particle_ids);
    Benchmark::end ();
}
/* most likely not used
 void ParticlesList::update_original_vectors (unsigned long p_start_idx, unsigned long
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
void ParticlesList::get_current_status (unsigned long p_idx_first,
                                        unsigned long p_segment_length,

                                        std::vector<unsigned long> *p_ids,
                                        std::vector<float> *        p_positions_x,
                                        std::vector<float> *        p_positions_y,
                                        std::vector<float> *        p_positions_z,
                                        std::vector<float> *        p_velocities_x,
                                        std::vector<float> *        p_velocities_y,
                                        std::vector<float> *        p_velocities_z,
                                        std::vector<float> *        p_accelerations_x,
                                        std::vector<float> *        p_accelerations_y,
                                        std::vector<float> *        p_accelerations_z) {
    unsigned long end = p_segment_length + p_idx_first;
    int           current_list_idx;
    for (unsigned long range_idx = p_idx_first; range_idx < end; range_idx++) {
        current_list_idx                = m_particle_list_ranges[range_idx * 2];
        (*p_ids)[range_idx]             = m_particle_ids[current_list_idx];
        (*p_positions_x)[range_idx]     = m_listed_positions_x[current_list_idx];
        (*p_positions_y)[range_idx]     = m_listed_positions_x[current_list_idx];
        (*p_positions_z)[range_idx]     = m_listed_positions_x[current_list_idx];
        (*p_velocities_x)[range_idx]    = m_listed_velocities_x[current_list_idx];
        (*p_velocities_y)[range_idx]    = m_listed_velocities_y[current_list_idx];
        (*p_velocities_z)[range_idx]    = m_listed_velocities_z[current_list_idx];
        (*p_accelerations_x)[range_idx] = m_listed_accelerations_x[current_list_idx];
        (*p_accelerations_y)[range_idx] = m_listed_accelerations_y[current_list_idx];
        (*p_accelerations_z)[range_idx] = m_listed_accelerations_z[current_list_idx];
    }
}

float ParticlesList::calculate_cnt_average_neighbours () {
    float accum_neighbours = 0;
    for (unsigned long i = 1; i < m_particle_list_ranges.size (); i += 2) {
        accum_neighbours += m_particle_list_ranges[i];
    }
    accum_neighbours /= get_particle_count ();
    return accum_neighbours;
}

float ParticlesList::get_cnt_average_neighbours () {
    return m_average_list_length;
}
