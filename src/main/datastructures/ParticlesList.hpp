#ifndef PARTICLELIST_HPP
#define PARTICLELIST_HPP

#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleWriterBase.hpp"
#include "ParticlesBase.hpp"
#include <vector>

class ParticlesList : public ParticlesBase {
  private:
    data_type m_average_list_length;
    data_type m_next_list_size_multiplier;
    short     m_duration_list;
    short     m_cnt_iterations_without_rebuild;

    data_type calculate_cnt_average_neighbours ();
    void      calculate_duration_list ();
    void      setup_iteration ();

  public:
    unsigned long              m_last_id;
    data_type                  m_cutoff_radius;
    std::vector<unsigned long> m_unused_ids;
    std::vector<unsigned long> m_particle_ids;

    std::vector<data_type> m_velocities_x;
    std::vector<data_type> m_velocities_y;
    std::vector<data_type> m_velocities_z;

    std::vector<data_type> m_positions_x;
    std::vector<data_type> m_positions_y;
    std::vector<data_type> m_positions_z;

    std::vector<data_type> m_accelerations_x;
    std::vector<data_type> m_accelerations_y;
    std::vector<data_type> m_accelerations_z;
    // used in first implementaion of build lists and run iteration
    // pairs of data: first is start second is end

    std::vector<unsigned long> m_particle_list_ranges;

    std::vector<data_type> m_listed_velocities_x;
    std::vector<data_type> m_listed_velocities_y;
    std::vector<data_type> m_listed_velocities_z;

    std::vector<data_type> m_listed_positions_x;
    std::vector<data_type> m_listed_positions_y;
    std::vector<data_type> m_listed_positions_z;

    std::vector<data_type> m_listed_accelerations_x;
    std::vector<data_type> m_listed_accelerations_y;
    std::vector<data_type> m_listed_accelerations_z;
    // used in build_lists_smarter and run_iteration 2nd implementation
    std::vector<std::vector<data_type>> m_mat_velocities_x;
    std::vector<std::vector<data_type>> m_mat_velocities_y;
    std::vector<std::vector<data_type>> m_mat_velocities_z;

    std::vector<std::vector<data_type>> m_mat_positions_x;
    std::vector<std::vector<data_type>> m_mat_positions_y;
    std::vector<std::vector<data_type>> m_mat_positions_z;

    std::vector<std::vector<data_type>> m_mat_accelerations_x;
    std::vector<std::vector<data_type>> m_mat_accelerations_y;
    std::vector<std::vector<data_type>> m_mat_accelerations_z;

    ParticlesList (s_options&                p_options,
                   ParticleBoundsCorrection& p_particle_bounds_correction,
                   AlgorithmBase&            p_algorithm,
                   ParticleWriterBase&       p_particle_writer);

    ~ParticlesList ();
    void add_particle (Vec3f p_position);
    void add_particle (Vec3f p_position, Vec3f p_velocity);
    unsigned long get_particle_count ();
    void run_simulation_iteration (unsigned long p_iteration_number);
    void build_lists ();
    void build_lists_smarter (data_type*    p_distances_x,
                              data_type*    p_distances_y,
                              data_type*    p_distances_z,
                              data_type*    p_distances_squared,
                              unsigned long p_size_distance_vectors);
    void calculate_distance_vectors (unsigned long p_particle_idx,
                                     data_type*    p_distances_x,
                                     data_type*    p_distances_y,
                                     data_type*    p_distances_z,
                                     data_type*    p_positions_x,
                                     data_type*    p_positions_y,
                                     data_type*    p_positions_z,
                                     unsigned long start_idx,
                                     unsigned long end_idx);
    data_type get_cnt_average_neighbours ();
    void calculate_distances_squared (data_type*    p_distances_squared,
                                      data_type*    p_distances_x,
                                      data_type*    p_distances_y,
                                      data_type*    p_distances_z,
                                      unsigned long size);
    void serialize ();
    void get_current_status (unsigned long               p_idx_first,
                             unsigned long               p_segment_length,
                             std::vector<unsigned long>* p_ids,
                             std::vector<data_type>*     p_positions_x,
                             std::vector<data_type>*     p_positions_y,
                             std::vector<data_type>*     p_positions_z,
                             std::vector<data_type>*     p_velocities_x,
                             std::vector<data_type>*     p_velocities_y,
                             std::vector<data_type>*     p_velocities_z,
                             std::vector<data_type>*     p_accelerations_x,
                             std::vector<data_type>*     p_accelerations_y,
                             std::vector<data_type>*     p_accelerations_z);
    // void update_original_vectors (unsigned long p_start_idx, unsigned long
    // p_segment_length);
};
#endif
