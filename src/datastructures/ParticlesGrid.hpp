#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../tools/Debug.hpp"
#include "ParticlesBase.hpp"

struct ParticleCell {
    std::vector<float> m_positions_x;
    std::vector<float> m_positions_y;
    std::vector<float> m_positions_z;
    std::vector<float> m_velocities_x;
    std::vector<float> m_velocities_y;
    std::vector<float> m_velocities_z;
    std::vector<float> m_accelerations_x;
    std::vector<float> m_accelerations_y;
    std::vector<float> m_accelerations_z;
};

class ParticlesGrid : public ParticlesBase {
    private:
    std::vector<std::vector<std::vector<ParticleCell>>> m_cells;

    public:
    ParticlesGrid ();
    ~ParticlesGrid ();
    void run_simulation_iteration ();
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
};
#endif
