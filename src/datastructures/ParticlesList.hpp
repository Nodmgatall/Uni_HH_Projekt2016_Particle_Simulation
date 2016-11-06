#ifndef PARTICLELIST_HPP
#define PARTICLELIST_HPP

#include <vector>
#include "ParticlesBase.hpp"

class ParticlesList : public ParticlesBase {
    public:
    ParticlesList();
	glm::vec3 get_velocity (int p_particle_id);
	std::vector<glm::vec3> *	get_velocities ();
	std::vector<glm::vec3> *	get_positions ();
	std::vector<glm::vec3> *	get_accelerations ();
	std::vector<unsigned long> *get_ids ();
	void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
	unsigned long get_particle_count ();
};
#endif
