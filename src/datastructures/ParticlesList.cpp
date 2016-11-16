#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include "../tools/Debug.hpp"
#include "ParticlesList.hpp"

ParticlesList::ParticlesList (s_simulator_options *p_options, glm::vec3 *p_bounds)
: ParticlesBase (p_options, p_bounds), m_average_list_length (0.16), m_next_list_size_multiplier (1.1) {
    m_stucture_name = "List";
    macro_debug_1 ("constructor of ParticleList called")
}
ParticlesList::~ParticlesList () {
}

void ParticlesList::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
    (void) p_acceleration;
    if (!m_unused_ids.empty ()) {
        m_unused_ids.erase (m_unused_ids.begin ());
        std::cout << "Not implemented: program will exit" << std::endl;
        exit(EXIT_SUCCESS);
    } else {
        m_particle_ids.push_back (m_last_id++);
    m_velocities_x.push_back (p_velocity.x);
    m_velocities_y.push_back (p_velocity.y);
    m_velocities_z.push_back (p_velocity.z);

    m_positions_x.push_back (p_position.x);
    m_positions_y.push_back (p_position.y);
    m_positions_z.push_back (p_position.z);

    m_accelerations_x.push_back (0);
    m_accelerations_y.push_back (0);
    m_accelerations_z.push_back (0);
    }
}

void ParticlesList::run_simulation_iteration () {
    macro_debug_1 ("running iteration") 
        setup_iteration ();
    macro_debug_1 ("iteration done")
}

unsigned long ParticlesList::get_particle_count () {
    return m_positions_x.size ();
}

void ParticlesList::build_lists () {
    macro_debug_1 ("starting building neighbour lists") unsigned long particle_cnt = get_particle_count ();
    float                                                             cutoff_radius_squared = 0.8;
    unsigned long                                                     current_list_idx      = 0;
    unsigned long                                                     next_free_list_entry  = 0;

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
    
    unsigned long current_entries = 0;
    m_particle_list_ranges = std::vector<unsigned long> (listed_size * 2);
    std::vector<float> distances_squared (particle_cnt);
    for (unsigned long cur_idx = 0; cur_idx < particle_cnt; cur_idx++) {
        /* clang-format off */
        calculate_distances_squared (cur_idx,
                                    &distances_squared,
                                    &m_positions_x,
                                    &m_positions_y,
                                    &m_positions_z, 
                                    0, particle_cnt);
        /* clang-format on */
        m_particle_list_ranges[current_list_idx] = next_free_list_entry;
        current_list_idx++;

            int cnt_neighbours = 0;
        for (unsigned long other_idx = 0; other_idx < particle_cnt; other_idx++) {

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
                macro_debug("resizing lists to: ", listed_size)

                m_particle_list_ranges.resize (listed_size * 2);
                m_listed_positions_x.resize (listed_size);
                m_listed_positions_y.resize (listed_size);
                m_listed_positions_z.resize (listed_size);
                m_listed_velocities_x.resize (listed_size);
                m_listed_velocities_y.resize (listed_size);
                m_listed_velocities_z.resize (listed_size);
            }
        }
        macro_debug("found neigbours cnt:" , cnt_neighbours)
        m_particle_list_ranges[current_list_idx++] = next_free_list_entry;
    }
    m_particle_list_ranges.shrink_to_fit ();
    m_listed_positions_x.shrink_to_fit ();
    m_listed_positions_y.shrink_to_fit ();
    m_listed_positions_z.shrink_to_fit ();
    m_listed_velocities_x.shrink_to_fit ();
    m_listed_velocities_y.shrink_to_fit ();
    m_listed_velocities_z.shrink_to_fit ();
    macro_debug("shrunk list ranges to: ", m_particle_list_ranges.size())
    macro_debug("shrunk lists to: ", m_positions_x.size())
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

void ParticlesList::calculate_distances_squared (unsigned long       particle_idx,
                                                 std::vector<float> *p_distances_squared,
                                                 std::vector<float> *p_positions_x,
                                                 std::vector<float> *p_positions_y,
                                                 std::vector<float> *p_positions_z,
                                                 unsigned long       start_idx,
                                                 unsigned long       end_idx) {
    //ISSUES:
    //calculates distance to itself
    Benchmark::begin("Calculating Distances", false);

    unsigned long      cur_part_idx;
    unsigned long      other_part_idx;
    float              cur_pos_part;
    unsigned           cur_dist_idx;
    unsigned long      range = end_idx - start_idx;
    float              x     = m_positions_x[particle_idx];
    float              y     = m_positions_y[particle_idx];
    float              z     = m_positions_z[particle_idx];
    std::vector<float> x_distances (range);
    std::vector<float> y_distances (range);
    std::vector<float> z_distances (range);

    // calculating 1dimensional distances element wise
    for (cur_dist_idx = 0, other_part_idx = start_idx; other_part_idx < end_idx; cur_dist_idx++, other_part_idx++) {
        x_distances[cur_dist_idx] = x - (*p_positions_x)[other_part_idx];
    }

    for (cur_dist_idx = 0, other_part_idx = start_idx; other_part_idx < end_idx; cur_dist_idx++, other_part_idx++) {
        y_distances[cur_dist_idx] = y - (*p_positions_y)[other_part_idx];
    }

    for (cur_dist_idx = 0, other_part_idx = start_idx; other_part_idx < end_idx; cur_dist_idx++, other_part_idx++) {
        z_distances[cur_dist_idx] = z - (*p_positions_z)[other_part_idx];
    }

    // square every entry in vector:
    // x
    for (cur_part_idx = 0; cur_part_idx < range; cur_part_idx++) {
        cur_pos_part              = x_distances[cur_part_idx];
        x_distances[cur_part_idx] = cur_pos_part * cur_pos_part;
    }
    // y
    for (cur_part_idx = 0; cur_part_idx < range; cur_part_idx++) {
        cur_pos_part              = z_distances[cur_part_idx];
        y_distances[cur_part_idx] = cur_pos_part * cur_pos_part;
    }

    // z
    for (cur_part_idx = 0; cur_part_idx < range; cur_part_idx++) {
        cur_pos_part              = z_distances[cur_part_idx];
        z_distances[cur_part_idx] = cur_pos_part * cur_pos_part;
    }
    // summing up the squared distances
    // frist x + y
    for (cur_part_idx = 0; cur_part_idx < range; cur_part_idx++) {
        (*p_distances_squared)[cur_part_idx] = x_distances[cur_part_idx] + y_distances[cur_part_idx];
    }
    // then the result + z
    for (cur_part_idx = 0; cur_part_idx < range; cur_part_idx++) {
        (*p_distances_squared)[cur_part_idx] += z_distances[cur_part_idx];
        macro_debug("distance: ", (*p_distances_squared)[cur_part_idx])
    }
    Benchmark::end();
}

void ParticlesList::serialize (std::shared_ptr<ParticleFileWriter> p_writer) {

    Benchmark::begin ("saving the data", false);
    p_writer->saveData (&m_positions_x,
                        &m_positions_y,
                        &m_positions_z,
                        &m_velocities_x,
                        &m_velocities_y,
                        &m_velocities_z,
                        &m_accelerations_x,
                        &m_accelerations_y,
                        &m_accelerations_z,
                        &m_particle_ids);
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
