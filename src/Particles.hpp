#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <glm/glm.hpp>
#include <vector>
class Particles {
	public:
    Particles(unsigned long p_particle_cnt);
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec3> m_velocities;
	std::vector<glm::vec3> m_accelerations;
	glm::vec3 get_velocity (int particle_id);
	std::vector<glm::vec3> *get_velocities ();
	void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
	unsigned long get_particle_count();
};
#endif
