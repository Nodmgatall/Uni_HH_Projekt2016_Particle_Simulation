#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "ParticlesGrid.hpp"

ParticlesGrid::ParticlesGrid () {
    m_stucture_name = "Grid";
}

glm::vec3 ParticlesGrid::get_velocity (int particle_id) {
    return m_velocities[particle_id];
}
std::vector<glm::vec3> *ParticlesGrid::get_positions () {
    return &m_positions;
}

std::vector<glm::vec3> *ParticlesGrid::get_accelerations () {
    return &m_accelerations;
}

std::vector<glm::vec3> *ParticlesGrid::get_velocities () {
    return &m_velocities;
}
std::vector<unsigned long> *ParticlesGrid::get_ids () {
    return &m_ids;
}

unsigned long ParticlesGrid::get_particle_count () {
    return m_positions.size ();
}

void ParticlesGrid::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
    m_positions.push_back (p_position);
    m_velocities.push_back (p_velocity);
    m_accelerations.push_back (p_acceleration);
    m_ids.push_back (m_max_used_id);
    m_max_used_id++;
}

ParticlesGrid::~ParticlesGrid () {
}
