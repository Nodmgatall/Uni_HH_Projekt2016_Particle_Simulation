#ifndef PARTICLELIST_HPP
#define PARTICLELIST_HPP
#include "DatastructureBase.hpp"
#include <vector>
class DatastructureList : public DatastructureBase {
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
    data_type                  m_shell_thickness;
    std::vector<unsigned long> m_unused_ids;
    std::vector<unsigned long> m_particle_ids;
    std::vector<data_type>     m_positions_x_now;
    std::vector<data_type>     m_positions_y_now;
    std::vector<data_type>     m_positions_z_now;
    std::vector<data_type>     m_positions_x_old;
    std::vector<data_type>     m_positions_y_old;
    std::vector<data_type>     m_positions_z_old;
    // used in first implementaion of build lists and run iteration
    // pairs of data: first is start second is end
    // used in build_lists_smarter and run_iteration 2nd implementation
    std::vector<unsigned long> m_neighbour_idxs_list;
    std::vector<unsigned long> m_neighbour_section_idxs;
    DatastructureList (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    ~DatastructureList ();
    void add_particle (Vec3f p_position);
    void add_particle (Vec3f p_position, Vec3f p_velocity, int p_id = -1);
    unsigned long get_particle_count ();
    bool run_simulation_iteration (unsigned long p_iteration_number);
    void      build_lists ();
    data_type get_cnt_average_neighbours ();
    void calculate_distances_squared (unsigned long particle_idx, data_type* p_distances_squared);
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
    void check_boundaries ();
    // void update_original_vectors (unsigned long p_start_idx, unsigned long
    // p_segment_length);
};
#endif
