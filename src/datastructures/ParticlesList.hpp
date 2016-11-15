#ifndef PARTICLELIST_HPP
#define PARTICLELIST_HPP

#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include "ParticlesBase.hpp"
#include <vector>

class ParticlesList : public ParticlesBase {
    private:
    float m_average_list_length;
    float m_next_list_size_multiplier;
    short m_duration_list;

    float calculate_cnt_average_neighbours ();
    void  calculate_duration_list ();
    void  setup_iteration ();

    public:
    unsigned long              m_last_id;
    float                      m_cutoff_radius;
    std::vector<unsigned long> m_unused_ids;
    std::vector<unsigned long> m_particle_ids;

    std::vector<float> m_velocities_x;
    std::vector<float> m_velocities_y;
    std::vector<float> m_velocities_z;

    std::vector<float> m_positions_x;
    std::vector<float> m_positions_y;
    std::vector<float> m_positions_z;

    // pairs of data: first is start second is end
    std::vector<unsigned long> m_particle_list_ranges;

    std::vector<float> m_listed_velocities_x;
    std::vector<float> m_listed_velocities_y;
    std::vector<float> m_listed_velocities_z;

    std::vector<float> m_listed_positions_x;
    std::vector<float> m_listed_positions_y;
    std::vector<float> m_listed_positions_z;

    std::vector<float> m_listed_accelerations_x;
    std::vector<float> m_listed_accelerations_y;
    std::vector<float> m_listed_accelerations_z;

    ParticlesList (s_simulator_options *p_options, glm::vec3 *p_bounds);

    ~ParticlesList ();
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
    unsigned long get_particle_count ();
    void          run_simulation_iteration ();
    void          build_lists ();
    void calculate_distances_squared (unsigned long       partice_idx,
                                      std::vector<float> *distances,
                                      std::vector<float> *x_distances,
                                      std::vector<float> *y_distances,
                                      std::vector<float> *z_distances,
                                      unsigned long       start_idx,
                                      unsigned long       end_idx);
    float get_cnt_average_neighbours ();
    void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
    void get_current_status (unsigned long               p_idx_first,
                             unsigned long               p_segment_length,
                             std::vector<unsigned long> *p_ids,
                             std::vector<float> *        p_positions_x,
                             std::vector<float> *        p_positions_y,
                             std::vector<float> *        p_positions_z,
                             std::vector<float> *        p_velocities_x,
                             std::vector<float> *        p_velocities_y,
                             std::vector<float> *        p_velocities_z,
                             std::vector<float> *        p_accelerations_x,
                             std::vector<float> *        p_accelerations_y,
                             std::vector<float> *        p_accelerations_z);
    // void update_original_vectors (unsigned long p_start_idx, unsigned long p_segment_length);
};
#endif
