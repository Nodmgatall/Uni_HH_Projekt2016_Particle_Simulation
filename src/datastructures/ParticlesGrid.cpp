#include "../vec3.hpp"
#include <iostream>
#include <omp.h>
#include <vector>

#include "ParticlesGrid.hpp"

#define MIN(a, b) (((a) < (b) ? (a) : (b)))
#define NEXT_POSITION(cell, particle)                                             \
    cell.m_positions_x[m_idx_b][particle], cell.m_positions_y[m_idx_b][particle], \
        cell.m_positions_z[m_idx_b][particle]
#define CURR_POSITION(cell, particle)                                             \
    cell.m_positions_x[m_idx_a][particle], cell.m_positions_y[m_idx_a][particle], \
        cell.m_positions_z[m_idx_a][particle]
/**
 *
 * @param p_options options for the simulation
 * @param p_bounds boundary for the particles in which they can move
 */
ParticlesGrid::ParticlesGrid (s_simulator_options *p_options, vec3f *p_bounds)
: ParticlesBase (p_options, p_bounds), m_iterations_between_rearange_particles (20) {
    unsigned int idx_x, idx_y, idx_z;
    m_particle_bounds_correction          = new ParticleBoundsCorrectionWraparound (*m_bounds);
    long max_usefull_size                 = pow (m_options->m_particle_count, 1.0 / 3.0);
    m_iterations_until_rearange_particles = m_iterations_between_rearange_particles;
    m_stucture_name                       = "Grid";
    m_max_id                              = 0;
    m_idx_a = !(m_idx_b = 0);
    // cut_off_radius*1.2 to allow particles to move before reconstruction of cells is needed
    m_size = vec3l::min (vec3l (*m_bounds / (m_options->m_cut_off_radius * 1.2f)), max_usefull_size);
    m_size          = m_size + 1L; // round up to next natural number for cell-count
    m_size          = vec3l::max (m_size, vec3l (4L));
    m_size_per_cell = vec3f (m_size - 1L) / *m_bounds;
    DEBUG_BEGIN << DEBUG_VAR (m_idx_a) << DEBUG_VAR (m_idx_b) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (max_usefull_size) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (m_options->m_cut_off_radius) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (m_options->m_cut_off_radius * 1.2f) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (*m_bounds / (m_options->m_cut_off_radius * 1.2f)) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (m_size) << DEBUG_END;
    m_cells.reserve (m_size.x * m_size.y * m_size.z);
    for (idx_x = 0; idx_x < m_size.x; idx_x++) {
        for (idx_y = 0; idx_y < m_size.y; idx_y++) {
            for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                m_cells.push_back (ParticleCell (vec3l (idx_x, idx_y, idx_z), m_size, *m_bounds));
            }
        }
    }
}
/**
 * destructor
 */
ParticlesGrid::~ParticlesGrid () {
}
/**
 * adds an particle to the current simulation
 * @param p_position the position of the new particle
 */
void ParticlesGrid::add_particle (vec3f p_current_position) {
    add_particle (p_current_position, vec3f (0));
}
/**
 *
 * adds an particle to the current simulation
 * @param p_position the position of the new particle
 * @param p_velocity the initial velocity
 */
void ParticlesGrid::add_particle (vec3f p_current_position, vec3f p_current_velocity) {
    vec3f old_position = p_current_position - p_current_velocity * m_options->m_timestep;
    m_particle_bounds_correction->updatePosition (p_current_position.x,
                                                  p_current_position.y,
                                                  p_current_position.z,
                                                  old_position.x,
                                                  old_position.y,
                                                  old_position.z);
    get_cell_forParticle (p_current_position).add_particle (p_current_position, m_max_id++);
}
/**
 * saves all particles to an file
 * @param p_file_writer the wrapper which holds the file and formats the output
 */
void ParticlesGrid::serialize (std::shared_ptr<ParticleFileWriter> p_file_writer) {
    Benchmark::begin ("saving the data", false);
    p_file_writer->start ();
    for (ParticleCell cell : m_cells) {
        if (!(cell.m_ids.empty ())) {
            p_file_writer->saveData (&(cell.m_positions_x[m_idx_a]),
                                     &(cell.m_positions_y[m_idx_a]),
                                     &(cell.m_positions_z[m_idx_a]),
                                     &(cell.m_ids));
        }
    }
    p_file_writer->end ();
    Benchmark::end ();
}
/**
 * first step in each iteration. Calculates the new particle position based on its own speed
 * @param p_cell the cell contains the particles which are calculated
 */
void ParticlesGrid::step_1_prepare_cell (ParticleCell &p_cell) {
    unsigned int       i;
    const unsigned int max = p_cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        LennardJonesAlgorithm::step_1 (CURR_POSITION (p_cell, i), NEXT_POSITION (p_cell, i));
    }
}
/**
 * calculates the movement of particles based on the forces between every particle-pair in the given
 * cell
 * @param p_cell the cell which contains the particles
 */
void ParticlesGrid::step_2a_calculate_inside_cell (ParticleCell &p_cell) {
    unsigned int       i, j;
    const unsigned int max   = p_cell.m_ids.size ();
    const unsigned int max_1 = max - 1;
    if (max > 0) {
        for (i = 0; i < max_1; i++) {
            for (j = i + 1; j < max; j++) {
                LennardJonesAlgorithm::step_2 (CURR_POSITION (p_cell, i),
                                               NEXT_POSITION (p_cell, i),
                                               CURR_POSITION (p_cell, j),
                                               NEXT_POSITION (p_cell, j));
            }
        }
    }
}
/**
 * calculates the movement based on forces between particles which are in different cells each
 * particle-pair consists of one particle from each cell given as parameters
 * @param p_cell1
 * @param p_cell2
 */
void ParticlesGrid::step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell &p_cell2) {
    unsigned int       i, j;
    const unsigned int max1 = p_cell1.m_ids.size ();
    const unsigned int max2 = p_cell2.m_ids.size ();
    for (i = 0; i < max1; i++) {
        for (j = 0; j < max2; j++) {
            LennardJonesAlgorithm::step_2 (CURR_POSITION (p_cell1, i),
                                           NEXT_POSITION (p_cell1, i),
                                           CURR_POSITION (p_cell2, j),
                                           NEXT_POSITION (p_cell2, j));
        }
    }
}
/**
 * runs a complete timestep simulation on all particles contained in this datastructure
 * @param p_iteration_number unused? TODO remove?!?
 */
void ParticlesGrid::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
    m_iterations_until_rearange_particles--;
    unsigned int idx_x, idx_y, idx_z, parallel_offset;
    Benchmark::begin ("step 1+2a", false);
    omp_set_num_threads (1);
#pragma omp parallel for
    for (idx_x = 0; idx_x < m_size.x; idx_x++) {
        for (idx_y = 0; idx_y < m_size.y; idx_y++) {
            for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                ParticleCell &cell = get_cell_at (idx_x, idx_y, idx_z);
                step_1_prepare_cell (cell);
                step_2a_calculate_inside_cell (cell);
            }
        }
    }
    Benchmark::end ();
    Benchmark::begin ("step 2b", false);
    for (parallel_offset = 0; parallel_offset < 2; parallel_offset++) {
#pragma omp parallel for
        for (idx_x = parallel_offset; idx_x < m_size.x; idx_x += 2) {
            for (idx_y = 0; idx_y < m_size.y; idx_y++) {
                for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                    get_cell_at (idx_x + 1, idx_y + 1, idx_z + 1)); // 1
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                    get_cell_at (idx_x + 1, idx_y, idx_z)); // 2
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                    get_cell_at (idx_x + 1, idx_y + 1, idx_z)); // 3
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                    get_cell_at (idx_x + 1, idx_y, idx_z + 1)); // 4
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                    get_cell_at (idx_x + 1, idx_y + 1, idx_z)); // 5
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                    get_cell_at (idx_x + 1, idx_y, idx_z + 1)); // 6
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                    get_cell_at (idx_x, idx_y + 1, idx_z + 1)); // 7
                    step_2b_calculate_betweenCells (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                    get_cell_at (idx_x, idx_y + 1, idx_z)); // 8
                    step_2b_calculate_betweenCells (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                    get_cell_at (idx_x, idx_y, idx_z + 1)); // 9
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y + 1, idx_z),
                                                    get_cell_at (idx_x, idx_y, idx_z + 1)); // 10
                    step_2b_calculate_betweenCells (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                    get_cell_at (idx_x, idx_y + 1, idx_z + 1)); // 11
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y + 1, idx_z),
                                                    get_cell_at (idx_x + 1, idx_y, idx_z + 1)); // 12
                    step_2b_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z + 1),
                                                    get_cell_at (idx_x + 1, idx_y + 1, idx_z)); // 13
                }
            }
        }
    }
    Benchmark::end ();
    if (!m_iterations_until_rearange_particles) {
        Benchmark::begin ("step 3", false);
        for (parallel_offset = 0; parallel_offset < 3; parallel_offset++) {
#pragma omp parallel for
            for (idx_x = parallel_offset; idx_x < m_size.x; idx_x += 3) {
                for (idx_y = 0; idx_y < m_size.y; idx_y++) {
                    for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                        ParticleCell &cell = get_cell_at (idx_x, idx_y, idx_z);
                        step_3_remove_wrong_particles_from_cell (cell);
                    }
                }
            }
        }
        Benchmark::end ();
    }
    m_iterations_until_rearange_particles = m_iterations_between_rearange_particles;
    m_idx_b = !(m_idx_a = m_idx_b);
}
/**
 * returns the coordinates of the cell for the given coordinates. no bounds check included!
 * @param x
 * @param y
 * @param z
 */
unsigned long ParticlesGrid::get_cell_index (long x, long y, long z) {
    return x + m_size.x * (y + m_size.y * z);
}
ParticleCell &ParticlesGrid::get_cell_at (long x, long y, long z) {
    return m_cells[get_cell_index (x, y, z)];
}
ParticleCell &ParticlesGrid::get_cell_at (vec3l coord) {
    return get_cell_at (coord.y, coord.y, coord.z);
}
ParticleCell &ParticlesGrid::get_cell_for_particle (float x, float y, float z) {
    int a = x / m_bounds->x * (m_size.x - 1);
    int b = y / m_bounds->y * (m_size.y - 1);
    int c = z / m_bounds->z * (m_size.z - 1);
    return get_cell_at (a, b, c);
}
ParticleCell &ParticlesGrid::get_cell_forParticle (vec3f m_position) {
    return get_cell_at (m_position.x * m_size_per_cell.x,
                        m_position.y * m_size_per_cell.y,
                        m_position.z * m_size_per_cell.z);
}
void ParticlesGrid::step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell) {
    int i;
    for (i = p_cell.m_ids.size () - 1; i >= 0; i--) {
        if (m_particle_bounds_correction->updatePosition (CURR_POSITION (p_cell, i),
                                                          NEXT_POSITION (p_cell, i),
                                                          p_cell.m_corner000,
                                                          p_cell.m_corner111)) {
            ParticleCell &other_cell = get_cell_for_particle (CURR_POSITION (p_cell, i));
            moveParticle (p_cell, other_cell, i);
        }
    }
}

inline void ParticlesGrid::moveParticle (ParticleCell &p_cell_from, ParticleCell &p_cell_to, long p_index_from) {
    unsigned int j;
    p_cell_to.m_ids.push_back (p_cell_from.m_ids[p_index_from]);
    p_cell_from.m_ids.erase (p_cell_from.m_ids.begin () + p_index_from);
    for (j = 0; j <= 1; j++) {
        p_cell_to.m_positions_x[j].push_back (p_cell_from.m_positions_x[j][p_index_from]);
        p_cell_to.m_positions_y[j].push_back (p_cell_from.m_positions_y[j][p_index_from]);
        p_cell_to.m_positions_z[j].push_back (p_cell_from.m_positions_z[j][p_index_from]);
        p_cell_from.m_positions_y[j].erase (p_cell_from.m_positions_y[j].begin () + p_index_from);
        p_cell_from.m_positions_z[j].erase (p_cell_from.m_positions_z[j].begin () + p_index_from);
    }
}

unsigned long ParticlesGrid::get_particle_count () {
    unsigned long particle_count = 0;
    for (ParticleCell cell : m_cells) {
        particle_count += cell.m_ids.size ();
    }
    return particle_count;
}
ParticleCell::ParticleCell (vec3l p_idx, vec3l p_size, vec3f &p_bounds) {
    m_idx       = p_idx;
    m_corner000 = vec3f (m_idx) / vec3f (p_size) * p_bounds;
    m_corner111 = vec3f (m_idx + 1L) / vec3f (p_size) * p_bounds;
}
void ParticleCell::add_particle (vec3f p_position, int p_id) {
    unsigned int i;
    for (i = 0; i <= 1; i++) {
        m_positions_x[i].push_back (p_position.x);
        m_positions_y[i].push_back (p_position.y);
        m_positions_z[i].push_back (p_position.z);
    }
    m_ids.push_back (p_id);
}
