#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../tools/Debug.hpp"
#include "ParticlesBase.hpp"

class ParticlesGrid : public ParticlesBase {
    public:
    ParticlesGrid ();
    ~ParticlesGrid ();
    void run_simulation_iteration ();
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
};
#endif
