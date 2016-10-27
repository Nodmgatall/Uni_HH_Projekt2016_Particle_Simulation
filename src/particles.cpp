#include "particles.hpp"
#include <vector>
#include <glm/glm.hpp>

glm::vec3 Particles::get_velocity (int particle_id) {
	return m_velocities[particle_id];
}

std::vector<glm::vec3>* Particles::get_velocities () {
	return &m_velocities;
}
