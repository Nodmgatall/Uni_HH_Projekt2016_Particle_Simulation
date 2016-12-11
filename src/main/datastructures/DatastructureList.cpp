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

void DatastructureList::add_particle (Vec3f p_position, Vec3f p_velocity, int p_id) {
    (void) p_velocity;
    add_particle (p_position);
    (void) p_id;
    //    add_particle (p_position); // TODO
}

void DatastructureList::run_simulation_iteration (unsigned long p_iteration_number) {
    macro_debug_1 ("running iteration") unsigned long particle_count = m_positions_x.size ();
    unsigned long                                     last_particle  = particle_count - 1;
    //    unsigned long neighbour_cnt;
    // std::cout << "cnt particles: " << particle_count << std::endl;
    unsigned long size_distance_vectors = ((particle_count * particle_count) - particle_count) / 2;
    std::vector<data_type> distances_x (size_distance_vectors);
    std::vector<data_type> distances_y (size_distance_vectors);
    std::vector<data_type> distances_z (size_distance_vectors);
    std::vector<data_type> distances_squared (size_distance_vectors);
    // for each particle go over list
    //    macro_debug_1 ("Starting iteration (list)");
    if (p_iteration_number % m_cnt_iterations_without_rebuild == 0) {
        //      macro_debug_1 (" rebuilding list");
        /* clang-format off */
        build_lists_smarter (&distances_x[0],
                             &distances_y[0],
                             &distances_z[0],
                             &distances_squared[0], size_distance_vectors);
        /* clang-format on */
    } else {
        //  macro_debug_1 (" using old lists");
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
        for (unsigned long distances_idx = 0; distances_idx < size_distance_vectors; distances_idx++) {
            /* clang-format off */
            calculate_distances_squared (&distances_squared[0],
                                         &distances_x[0],
                                         &distances_y[0],
                                         &distances_z[0],
                                         size_distance_vectors);
            /* clang-format on */
        }
    }

    //    for (unsigned long neighbour_idx = 0; neighbour_idx < neighbour_cnt;
    //    neighbour_idx++) {
    // calculate force
    //
    //  }
    // summ
    macro_debug_1 ("iteration done")
}

unsigned long DatastructureList::get_particle_count () {
    return m_positions_x.size ();
}

void DatastructureList::build_lists_smarter (data_type*    p_distances_x,
                                             data_type*    p_distances_y,
                                             data_type*    p_distances_z,
                                             data_type*    p_distances_squared,
                                             unsigned long p_size_distance_vectors) {
    unsigned long          particle_count            = m_positions_x.size ();
    unsigned long          start_pos_distance_vector = 0;
    data_type              cutoff_radius_squared     = 0.8;
    std::vector<data_type> distances (p_size_distance_vectors);
    unsigned long          listed_size = particle_count * (particle_count * (0.25));
    std::cout << "listed size: " << listed_size << std::endl;
    std::cout << "p_size_distance_vectors = " << p_size_distance_vectors << std::endl;
    m_listed_positions_x.reserve (listed_size);
    m_listed_positions_y.reserve (listed_size);
    m_listed_positions_z.reserve (listed_size);

    m_listed_velocities_x.reserve (listed_size);
    m_listed_velocities_y.reserve (listed_size);
    m_listed_velocities_z.reserve (listed_size);

    std::vector<data_type> distances_squared (p_size_distance_vectors);

    // calculating distance vectors for (n^2 -n)/2 pairs
    for (unsigned long particle_idx = 0, range = particle_count - 1; particle_idx < particle_count - 1;
         particle_idx++, range--) {
        macro_debug ("calculating distances of ", particle_idx);
        macro_debug ("range: ", (particle_count - (particle_idx + 1)));
        calculate_distance_vectors (particle_idx,
                                    &p_distances_x[0],
                                    &p_distances_y[0],
                                    &p_distances_z[0],
                                    &m_positions_x[0],
                                    &m_positions_y[0],
                                    &m_positions_z[0],
                                    start_pos_distance_vector,
                                    range);
        start_pos_distance_vector += (particle_count - particle_idx - 1);
    }

    // calculating distance skalar from the distance vectors
    macro_debug ("cnt_distances", p_size_distance_vectors);
    // macro_debug ("distances_idx", distances_idx);
    // macro_debug ("p_size_distance_vectors", p_size_distance_vectors);
    calculate_distances_squared (&p_distances_squared[0], &p_distances_x[0], &p_distances_y[0], &p_distances_z[0], p_size_distance_vectors);
    macro_debug_1 ("start sorting into lists");

    // building list
    m_mat_positions_x = std::vector<std::vector<float>> (particle_count, std::vector<float> ());
    m_mat_positions_y = std::vector<std::vector<float>> (particle_count, std::vector<float> ());
    m_mat_positions_z = std::vector<std::vector<float>> (particle_count, std::vector<float> ());
    std::cout << particle_count << "<- particle_cnt" << std::endl;
    // for all particles from index 0
    for (unsigned long distance_section_start = 0, range = particle_count - 1;
         distance_section_start < p_size_distance_vectors;
         distance_section_start += range, range--) {
        // std::cout << "start: " << distance_section_start << std::endl;
        //  std::cout << "range: " << range << std::endl;
        unsigned long cur_list_idx = particle_count - 1 - range;
        //  std::cout << "cur_idx " << cur_list_idx << std::endl;
        for (unsigned long dist_vector_part_idx = 0; dist_vector_part_idx < range; dist_vector_part_idx++) {
            //   std::cout << "dvpi: " << dist_vector_part_idx << std::endl;
            if (p_distances_squared[distance_section_start + dist_vector_part_idx] < cutoff_radius_squared) {
                /* clang-format off */
             //   std::cout << dist_vector_part_idx << " " << distance_section_start << std::endl;
             //   std::cout << dist_vector_part_idx + cur_list_idx + 1 << std::endl;
                m_mat_positions_x[cur_list_idx].push_back(m_positions_x[dist_vector_part_idx + cur_list_idx + 1]);
                m_mat_positions_y[cur_list_idx].push_back(m_positions_y[dist_vector_part_idx + cur_list_idx + 1]);
                m_mat_positions_z[cur_list_idx].push_back(m_positions_z[dist_vector_part_idx + cur_list_idx + 1]);
/*
                m_mat_velocities_x[cur_list_idx].push_back(m_velocities_x[dist_vector_part_idx + cur_list_idx + 1]);
                m_mat_velocities_y[cur_list_idx].push_back(m_velocities_y[dist_vector_part_idx + cur_list_idx + 1]);
                m_mat_velocities_z[cur_list_idx].push_back(m_velocities_z[dist_vector_part_idx + cur_list_idx + 1]);
*/
                m_mat_positions_x[dist_vector_part_idx + cur_list_idx + 1].push_back(m_positions_x[cur_list_idx]);
                m_mat_positions_y[dist_vector_part_idx + cur_list_idx + 1].push_back(m_positions_y[cur_list_idx]);
                m_mat_positions_z[dist_vector_part_idx + cur_list_idx + 1].push_back(m_positions_z[cur_list_idx]);
/*
                m_mat_velocities_x[dist_vector_part_idx + cur_list_idx + 1].push_back(m_velocities_x[cur_list_idx]);
                m_mat_velocities_y[dist_vector_part_idx + cur_list_idx + 1].push_back(m_velocities_y[cur_list_idx]);
                m_mat_velocities_z[dist_vector_part_idx + cur_list_idx + 1].push_back(m_velocities_z[cur_list_idx]);
*/
                /* clang-format on */
            }
            if (m_mat_positions_x.size () == listed_size) {
                listed_size = listed_size * (listed_size * 0.16);
                m_listed_positions_x.reserve (listed_size);
                m_listed_positions_y.reserve (listed_size);
                m_listed_positions_z.reserve (listed_size);
                /*
                                m_listed_velocities_x.reserve (listed_size);
                                m_listed_velocities_y.reserve (listed_size);
                                m_listed_velocities_z.reserve (listed_size);
                */
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

void DatastructureList::build_lists () {
    macro_debug_1 ("starting building neighbour lists");
    unsigned long particle_cnt          = get_particle_count ();
    data_type     cutoff_radius_squared = 0.8;
    unsigned long current_list_idx      = 0;
    unsigned long next_free_list_entry  = 0;

    // TODO: Idea: dont let them be initialized each time we need to build the
    // lists
    // instead make them a member; pro: minmal performance improvement, con:
    // memory need * (4/3)
    unsigned long listed_size = particle_cnt * (particle_cnt * (0.25));
    std::cout << "listed size: " << listed_size << std::endl;
    m_listed_positions_x.resize (listed_size);
    m_listed_positions_y.resize (listed_size);
    m_listed_positions_z.resize (listed_size);

    m_listed_velocities_x.resize (listed_size);
    m_listed_velocities_y.resize (listed_size);
    m_listed_velocities_z.resize (listed_size);

    std::vector<data_type> distances_x (particle_cnt);
    std::vector<data_type> distances_y (particle_cnt);
    std::vector<data_type> distances_z (particle_cnt);

    unsigned long current_entries = 0;
    m_particle_list_ranges        = std::vector<unsigned long> (listed_size * 2);
    std::vector<data_type> distances_squared (particle_cnt - 1);
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
                                    &distances_x[cur_idx],
                                    &distances_y[cur_idx],
                                    &distances_z[cur_idx],
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

void DatastructureList::setup_iteration () {
    macro_debug_1 ("starting setting up iteration") int size = m_positions_x.size ();
    m_listed_accelerations_x                                 = std::vector<data_type> (size);
    m_listed_accelerations_y                                 = std::vector<data_type> (size);
    m_listed_accelerations_z                                 = std::vector<data_type> (size);

    if (true) {
        build_lists ();
    }
    macro_debug_1 ("finished setting up iteration")
}
/**
 *  this functions takes a range of positions and a index of a particle of wich
 * we want to
 *  know the distances to each particle in the range.
 */

void DatastructureList::calculate_distance_vectors (unsigned long p_particle_idx,

                                                    data_type*    p_distances_x,
                                                    data_type*    p_distances_y,
                                                    data_type*    p_distances_z,
                                                    data_type*    p_positions_x,
                                                    data_type*    p_positions_y,
                                                    data_type*    p_positions_z,
                                                    unsigned long start_idx,
                                                    unsigned long end_idx) {
    unsigned long cur_dist_idx;
    data_type     x = p_positions_x[p_particle_idx];
    data_type     y = p_positions_y[p_particle_idx];
    data_type     z = p_positions_z[p_particle_idx];

    int test = 0;
    for (cur_dist_idx = 0; cur_dist_idx < end_idx; cur_dist_idx++) {
        p_distances_x[start_idx + cur_dist_idx] = x - p_positions_x[p_particle_idx + cur_dist_idx + 1];
        test++;
    }

    for (cur_dist_idx = 0; cur_dist_idx < end_idx; cur_dist_idx++) {
        p_distances_y[start_idx + cur_dist_idx] = y - p_positions_y[p_particle_idx + cur_dist_idx + 1];
    }

    for (cur_dist_idx = 0; cur_dist_idx < end_idx; cur_dist_idx++) {
        p_distances_z[start_idx + cur_dist_idx] = z - p_positions_z[p_particle_idx + cur_dist_idx + 1];
    }
}
void DatastructureList::calculate_distances_squared (data_type*    p_distances_squared,
                                                     data_type*    p_distances_x,
                                                     data_type*    p_distances_y,
                                                     data_type*    p_distances_z,
                                                     unsigned long size) {
    Benchmark::begin ("Calculating Distances", false);

    unsigned long cur_part_idx;
    data_type     cur_pos_part;

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
    }
    Benchmark::end ();
}

void DatastructureList::serialize () {
    Benchmark::begin ("saving the data", false);
    m_writer.start ();
    m_writer.saveData (m_positions_x, m_positions_y, m_positions_z, m_particle_ids);
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
void DatastructureList::get_current_status (unsigned long p_idx_first,
                                            unsigned long p_segment_length,

                                            std::vector<unsigned long>* p_ids,
                                            std::vector<data_type>*     p_positions_x,
                                            std::vector<data_type>*     p_positions_y,
                                            std::vector<data_type>*     p_positions_z,
                                            std::vector<data_type>*     p_velocities_x,
                                            std::vector<data_type>*     p_velocities_y,
                                            std::vector<data_type>*     p_velocities_z,
                                            std::vector<data_type>*     p_accelerations_x,
                                            std::vector<data_type>*     p_accelerations_y,
                                            std::vector<data_type>*     p_accelerations_z) {
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

data_type DatastructureList::calculate_cnt_average_neighbours () {
    data_type accum_neighbours = 0;
    for (unsigned long i = 1; i < m_particle_list_ranges.size (); i += 2) {
        accum_neighbours += m_particle_list_ranges[i];
    }
    accum_neighbours /= get_particle_count ();
    return accum_neighbours;
}

data_type DatastructureList::get_cnt_average_neighbours () {
    return m_average_list_length;
}
