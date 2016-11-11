#ifndef PARTICLELIST_HPP
#define PARTICLELIST_HPP

#include "ParticlesBase.hpp"
#include <vector>

class ParticlesList : public ParticlesBase {
    public:
    ParticlesList (s_simulator_options *p_options, glm::vec3 *p_bounds);
    ~ParticlesList ();
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
    void run_simulation_iteration ();
};
#endif
