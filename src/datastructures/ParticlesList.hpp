#ifndef PARTICLELIST_HPP
#define PARTICLELIST_HPP

#include "ParticlesBase.hpp"
#include <vector>

class ParticlesList : public ParticlesBase {
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
    std::vector<float>         m_listed_velocities_x;
    std::vector<float>         m_listed_velocities_y;
    std::vector<float>         m_listed_velocities_z;

    std::vector<float> m_listed_positions_x;
    std::vector<float> m_listed_positions_y;
    std::vector<float> m_listed_positions_z;

    ParticlesList (s_simulator_options *p_options, glm::vec3 *p_bounds);

    ~ParticlesList ();
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
    void run_simulation_iteration ();
    void build_lists ();
    void calculate_distances_squared (unsigned long       partice_idx,
                                      std::vector<float> *distances,
                                      std::vector<float> *x_distances,
                                      std::vector<float> *y_distances,
                                      std::vector<float> *z_distances,
                                      unsigned long       start_idx,
                                      unsigned long       end_idx);
};
#endif
