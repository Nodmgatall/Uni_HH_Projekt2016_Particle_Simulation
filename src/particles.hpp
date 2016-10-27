#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>
#include <glm/glm.hpp>

class Particles {
	public:
		std::vector<glm::vec3> m_position;
		std::vector<glm::vec3> m_velocities;
		std::vector<glm::vec3> m_acceleration;

		glm::vec3 get_velocity(int particle_id);
		std::vector<glm::vec3> *get_velocities();

};

#endif
