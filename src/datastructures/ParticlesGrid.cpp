#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "ParticlesGrid.hpp"

ParticlesGrid::ParticlesGrid (s_simulator_options *p_options, glm::vec3 *p_bounds)
: ParticlesBase (p_options, p_bounds) {
    m_stucture_name = "Grid";
    m_size_x = m_size_y = m_size_z = 0;
    m_max_id                       = 0;
    m_size_x                       = m_bounds->x / m_options->m_cuttof_radius + 1;
    m_size_y                       = m_bounds->y / m_options->m_cuttof_radius + 1;
    m_size_z                       = m_bounds->z / m_options->m_cuttof_radius + 1;
    m_cells                        = std::vector<ParticleCell> (m_size_x * m_size_y * m_size_z);
    for (int i = m_size_x * m_size_y * m_size_z; i >= 0; i--) {
        m_cells.push_back (ParticleCell ());
    }
}

void ParticlesGrid::add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) {
    int x, y, z;
    x = p_position.x / m_options->m_cuttof_radius;
    y = p_position.y / m_options->m_cuttof_radius;
    z = p_position.z / m_options->m_cuttof_radius;
    (getCellAt (x, y, z)).add_particle (p_position, p_velocity, p_acceleration, m_max_id++);
}

ParticlesGrid::~ParticlesGrid () {
}

void ParticlesGrid::serialize (std::shared_ptr<ParticleFileWriter> p_file_writer) {
    for (ParticleCell cell : m_cells) {
        p_file_writer->saveData (&(cell.m_positions_x),
                                 &(cell.m_positions_y),
                                 &(cell.m_positions_y),
                                 &(cell.m_velocities_x),
                                 &(cell.m_velocities_y),
                                 &(cell.m_velocities_z),
                                 &(cell.m_accelerations_x),
                                 &(cell.m_accelerations_y),
                                 &(cell.m_accelerations_z),
                                 &(cell.m_ids));
    }
}
void ParticlesGrid::run_simulation_insideCell (ParticleCell cell) {
    unsigned int       i, j;
    const unsigned int max = cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        for (j = i + 1; j < max; j++) {
            m_algorithm (cell.m_positions_x[i],
                         cell.m_positions_y[i],
                         cell.m_positions_z[i],
                         cell.m_velocities_x[i],
                         cell.m_velocities_y[i],
                         cell.m_velocities_z[i],
                         cell.m_accelerations_x[i],
                         cell.m_accelerations_y[i],
                         cell.m_accelerations_z[i],
                         cell.m_positions_x[j],
                         cell.m_positions_y[j],
                         cell.m_positions_z[j],
                         cell.m_velocities_x[j],
                         cell.m_velocities_y[j],
                         cell.m_velocities_z[j],
                         cell.m_accelerations_x[j],
                         cell.m_accelerations_y[j],
                         cell.m_accelerations_z[j]);
        }
    }
}
void ParticlesGrid::run_simulation_betweenCells (ParticleCell cell1, ParticleCell cell2) {
    unsigned int       i, j;
    const unsigned int max1 = cell1.m_ids.size ();
    const unsigned int max2 = cell2.m_ids.size ();
    for (i = 0; i < max1; i++) {
        for (j = 0; j < max2; j++) {
            m_algorithm (cell1.m_positions_x[i],
                         cell1.m_positions_y[i],
                         cell1.m_positions_z[i],
                         cell1.m_velocities_x[i],
                         cell1.m_velocities_y[i],
                         cell1.m_velocities_z[i],
                         cell1.m_accelerations_x[i],
                         cell1.m_accelerations_y[i],
                         cell1.m_accelerations_z[i],
                         cell2.m_positions_x[j],
                         cell2.m_positions_y[j],
                         cell2.m_positions_z[j],
                         cell2.m_velocities_x[j],
                         cell2.m_velocities_y[j],
                         cell2.m_velocities_z[j],
                         cell2.m_accelerations_x[j],
                         cell2.m_accelerations_y[j],
                         cell2.m_accelerations_z[j]);
        }
    }
}
void ParticlesGrid::run_simulation_iteration () {
    unsigned int i, j, k;
    for (i = 0; i < m_size_x; i++) {
        for (j = 0; j < m_size_y; j++) {
            for (k = 0; k < m_size_z; k++) {
                run_simulation_insideCell (getCellAt (i, j, k));
            }
        }
    }
    for (i = 0; i < m_size_x - 1; i++) {
        for (j = 0; j < m_size_y - 1; j++) {
            for (k = 0; k < m_size_z - 1; k++) {
                run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k));
                run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j + 1, k));
                run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k + 1));
                run_simulation_betweenCells(getCellAt (i, j, k),getCellAt (i+1, j+1, k)) ;
                run_simulation_betweenCells(getCellAt (i, j, k),getCellAt (i+1, j, k+1)) ;
                run_simulation_betweenCells(getCellAt (i, j, k),getCellAt (i, j+1, k+1)) ;
                run_simulation_betweenCells(getCellAt (i, j, k),getCellAt (i+1, j+1, k+1)) ;
                //missing some pairs !!!! TODO
            }
        }
    }
}

ParticleCell ParticlesGrid::getCellAt (int x, int y, int z) {
    DEBUG_BEGIN << DEBUG_VAR (x + m_size_x * (y + m_size_y * z)) << DEBUG_END;
    return m_cells[x + m_size_x * (y + m_size_y * z)];
}

unsigned long ParticlesGrid::get_particle_count () {
    unsigned long particle_count = 0;
    for (ParticleCell cell : m_cells) {
        particle_count += cell.m_positions_x.size ();
    }
    return particle_count;
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
