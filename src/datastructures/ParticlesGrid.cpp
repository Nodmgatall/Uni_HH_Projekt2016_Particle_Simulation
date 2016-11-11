#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "ParticlesGrid.hpp"

ParticlesGrid::ParticlesGrid (s_simulator_options *p_options, glm::vec3 *p_bounds)
: ParticlesBase (p_options, p_bounds) {
    m_stucture_name = "Grid";
    m_cells         = new std::vector<ParticleCell>;
    m_size_x = m_size_y = m_size_z = 0;
    m_max_id                       = 0;
    DEBUG_BEGIN << "aaaa" << DEBUG_END;
    int i;
    m_size_x = m_bounds->x / m_options->m_cuttof_radius + 1;
    m_size_y = m_bounds->y / m_options->m_cuttof_radius + 1;
    m_size_z = m_bounds->z / m_options->m_cuttof_radius + 1;
    m_cells->reserve (m_size_x * m_size_y * m_size_z);
    DEBUG_BEGIN << DEBUG_VAR (m_size_x * m_size_y * m_size_z) << DEBUG_END;
    for (i = m_size_x * m_size_y * m_size_z; i >= 0; i--) {
        m_cells->push_back (ParticleCell ());
    }
}

void ParticlesGrid::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
    DEBUG_BEGIN << "bbbb" << DEBUG_END;

    int x, y, z;
    x = p_position.x / m_options->m_cuttof_radius;
    y = p_position.y / m_options->m_cuttof_radius;
    z = p_position.z / m_options->m_cuttof_radius;
    getCellAt (x, y, z).add_particle (p_position, p_velocity, p_acceleration, m_max_id++);
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

ParticleCell ParticlesGrid::getCellAt (int x, int y, int z) {
    DEBUG_BEGIN << DEBUG_VAR (x + m_size_x * (y + m_size_y * z)) << DEBUG_END;
    return (*m_cells)[x + m_size_x * (y + m_size_y * z)];
}
void ParticleCell::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration, int p_id) {
    m_positions_x.push_back (p_position.x);
    m_positions_y.push_back (p_position.y);
    m_positions_z.push_back (p_position.z);
    m_velocities_x.push_back (p_velocity.x);
    m_velocities_y.push_back (p_velocity.y);
    m_velocities_z.push_back (p_velocity.z);
    m_accelerations_x.push_back (p_acceleration.x);
    m_accelerations_y.push_back (p_acceleration.y);
    m_accelerations_z.push_back (p_acceleration.z);
    m_ids.push_back (p_id);
}
