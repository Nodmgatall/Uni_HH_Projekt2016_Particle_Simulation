#include "Particles.hpp"
#include <glm/glm.hpp>
#include <vector>

glm::vec3 Particles::get_velocity (int particle_id) {
	return m_velocities[particle_id];
}

std::vector<glm::vec3> *Particles::get_velocities () {
	return &m_velocities;
}

unsigned long Particles::get_particle_count () {
    return	m_positions.size ();
}

void Particles::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
	m_positions.push_back (p_position);
	m_velocities.push_back (p_velocity);
	m_accelerations.push_back (p_acceleration);
}
