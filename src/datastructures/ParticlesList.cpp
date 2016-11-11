#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "../tools/Debug.hpp"
#include "ParticlesList.hpp"

ParticlesList::ParticlesList (s_simulator_options *p_options, glm::vec3 *p_bounds)
: ParticlesBase (p_options, p_bounds) {
    m_stucture_name = "List";
    macro_debug_1("constructor of ParticleList called")
   }
ParticlesList::~ParticlesList () {
}

void ParticlesList::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
    (void) p_acceleration;
    if (m_unused_ids.empty ()) {
        m_particle_ids.push_back (m_unused_ids.front ());
        m_unused_ids.erase (m_unused_ids.begin ());
    } else {
        m_particle_ids.push_back (m_last_id++);
    }

    m_velocities_x.push_back (p_velocity.x);
    m_velocities_y.push_back (p_velocity.y);
    m_velocities_z.push_back (p_velocity.z);

    m_positions_x.push_back (p_position.x);
    m_positions_y.push_back (p_position.y);
    m_positions_z.push_back (p_position.z);
}

void ParticlesList::run_simulation_iteration () {
    macro_debug_1("running iteration")
    build_lists();
    std::cout << "lol" << std::endl;
}

unsigned long ParticlesList::get_particle_count()
{
    return m_positions_x.size();
}

void ParticlesList::build_lists () {
    unsigned long particle_cnt          = get_particle_count ();
    float         cutoff_radius_squared = m_cutoff_radius * m_cutoff_radius;
    unsigned long current_list_idx      = 0;
    unsigned long next_free_list_entry  = 0;

    // TODO: Idea: dont let them be initialized each time we need to build the lists
    // instead make them a member; pro: minmal performance improvement, con: memory need * (4/3)

    unsigned long listed_size = particle_cnt * (particle_cnt * (0.16 * 2));
    m_listed_positions_x      = std::vector<float> (listed_size);
    m_listed_positions_x      = std::vector<float> (listed_size);
    m_listed_positions_x      = std::vector<float> (listed_size);
    m_particle_list_ranges    = std::vector<unsigned long> (listed_size * 2);
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
        m_particle_list_ranges[current_list_idx++] = next_free_list_entry;
        for (unsigned long other_idx = cur_idx; other_idx < particle_cnt; other_idx++) {
            if (distances_squared[other_idx] < cutoff_radius_squared) {
                m_listed_positions_x[next_free_list_entry] = m_positions_x[other_idx];
                m_listed_positions_y[next_free_list_entry] = m_positions_y[other_idx];
                m_listed_positions_z[next_free_list_entry] = m_positions_z[other_idx];
                next_free_list_entry++;
            }
            if (listed_size == m_particle_list_ranges.size ()) {
                listed_size = listed_size * 1.16;
                m_particle_list_ranges.resize (listed_size);
                m_listed_positions_x.resize (listed_size);
                m_listed_positions_y.resize (listed_size);
                m_listed_positions_z.resize (listed_size);
            }
        }
        m_particle_list_ranges[current_list_idx++] = next_free_list_entry;
    }
}
void ParticlesList::calculate_distances_squared (unsigned long       particle_idx,
                                                 std::vector<float> *p_distances_squared,
                                                 std::vector<float> *p_positions_x,
                                                 std::vector<float> *p_positions_y,
                                                 std::vector<float> *p_positions_z,
                                                 unsigned long       start_idx,
                                                 unsigned long       end_idx) {
macro_debug_1("starting distance calculation")
    
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

macro_debug_1("starting 1d calc")
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

macro_debug_1("starting sqrt")
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
macro_debug_1("starting summation")
    // summing up the squared distances
    // frist x + y
    for (cur_part_idx = 0; cur_part_idx < range; cur_part_idx++) {
        (*p_distances_squared)[cur_part_idx] = x_distances[cur_part_idx] + y_distances[cur_part_idx];
    }
    // then the result + z
    for (cur_part_idx = 0; cur_part_idx < range; cur_part_idx++) {
        (*p_distances_squared)[cur_part_idx] += z_distances[cur_part_idx];
    }
}
