#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "ParticlesGrid.hpp"

ParticlesGrid::ParticlesGrid () {
    m_stucture_name = "Grid";
}

void ParticlesGrid::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
}

ParticlesGrid::~ParticlesGrid () {
}

void ParticlesGrid::run_simulation_iteration () { /*
     unsigned long i, j;
     for (i = 0; i < m_ids.size (); i++) {
         for (j = i + 1; j < m_ids.size (); j++) {
             m_algorithm (m_positions[i], m_velocities[i], m_accelerations[i], m_positions[j],
     m_velocities[j], m_accelerations[j]);
         }
     }
 */
}
