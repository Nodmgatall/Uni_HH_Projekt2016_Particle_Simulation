#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../tools/Debug.hpp"
#include "ParticlesBase.hpp"

class ParticlesGrid : public ParticlesBase {
    public:
    ParticlesGrid ();
    std::vector<glm::vec3> *    get_velocities ();
    std::vector<glm::vec3> *    get_positions ();
    std::vector<glm::vec3> *    get_accelerations ();
    void                        run_simulation_iteration ();
    std::vector<unsigned long> *get_ids ();
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
    unsigned long get_particle_count ();
    ~ParticlesGrid ();
};
#endif
