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
    short m_cnt_iterations_without_rebuild;

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

    std::vector<float> m_accelerations_x;
    std::vector<float> m_accelerations_y;
    std::vector<float> m_accelerations_z;
    // used in first implementaion of build lists and run iteration
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
    // used in build_lists_smarter and run_iteration 2nd implementation
    std::vector<std::vector<float>> m_mat_velocities_x;
    std::vector<std::vector<float>> m_mat_velocities_y;
    std::vector<std::vector<float>> m_mat_velocities_z;

    std::vector<std::vector<float>> m_mat_positions_x;
    std::vector<std::vector<float>> m_mat_positions_y;
    std::vector<std::vector<float>> m_mat_positions_z;

    std::vector<std::vector<float>> m_mat_accelerations_x;
    std::vector<std::vector<float>> m_mat_accelerations_y;
    std::vector<std::vector<float>> m_mat_accelerations_z;

    ParticlesList (s_simulator_options *p_options, vec3f *p_bounds);

    ~ParticlesList ();
    void add_particle (vec3f p_position);
    void add_particle (vec3f p_position, vec3f p_velocity);
    unsigned long get_particle_count ();
    void run_simulation_iteration (unsigned long p_iteration_number);
    void build_lists ();
    void build_lists_smarter (float *       p_distances_x,
                              float *       p_distances_y,
                              float *       p_distances_z,
                              float *       p_distances_squared,
                              unsigned long p_size_distance_vectors);
    void calculate_distance_vectors (unsigned long p_particle_idx,
                                     float *       p_distances_x,
                                     float *       p_distances_y,
                                     float *       p_distances_z,
                                     float *       p_positions_x,
                                     float *       p_positions_y,
                                     float *       p_positions_z,
                                     unsigned long start_idx,
                                     unsigned long end_idx);
    float get_cnt_average_neighbours ();
    void calculate_distances_squared (float *       p_distances_squared,
                                      float *       p_distances_x,
                                      float *       p_distances_y,
                                      float *       p_distances_z,
                                      unsigned long size);
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
