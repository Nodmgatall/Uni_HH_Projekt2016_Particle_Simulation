#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "ParticlesList.hpp"

ParticlesList::ParticlesList (s_simulator_options *p_options, glm::vec3 *p_bounds)
: ParticlesBase (p_options, p_bounds) {
    m_stucture_name = "List";
}
ParticlesList::~ParticlesList () {
}

void ParticlesList::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
}

void ParticlesList::run_simulation_iteration () {
}
