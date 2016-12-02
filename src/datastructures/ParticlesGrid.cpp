#include "../vec3.hpp"
#include <iostream>
#include <omp.h>
#include <vector>

#include "ParticlesGrid.hpp"

#define MIN(a, b) (((a) < (b) ? (a) : (b)))

ParticlesGrid::ParticlesGrid (s_simulator_options *p_options, vec3f *p_bounds)
: ParticlesBase (p_options, p_bounds), m_iterations_between_rearange_particles (20) {
    long max_usefull_size                 = pow (m_options->m_particle_count, 1.0 / 3.0);
    m_iterations_until_rearange_particles = m_iterations_between_rearange_particles;
    m_stucture_name                       = "Grid";
    m_max_id                              = 0;
    m_idx_a = !(m_idx_b = 0);
    // cut_off_radius*1.2 to allow particles to move before reconstruction of cells is needed
    m_size = vec3l::min (vec3l (*m_bounds / (m_options->m_cut_off_radius * 1.2f)), max_usefull_size);
    m_size = m_size + 1L; // round up to next natural number for cell-count
    m_size = vec3l::max (m_size, vec3l (4L));
    DEBUG_BEGIN << DEBUG_VAR (m_idx_a) << DEBUG_VAR (m_idx_b) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (max_usefull_size) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (m_options->m_cut_off_radius) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (m_options->m_cut_off_radius * 1.2f) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (*m_bounds / (m_options->m_cut_off_radius * 1.2f)) << DEBUG_END;
    DEBUG_BEGIN << DEBUG_VAR (m_size) << DEBUG_END;
    m_cells.reserve (m_size.x * m_size.y * m_size.z);
    unsigned int idx_x, idx_y, idx_z;
    for (idx_x = 0; idx_x < m_size.x; idx_x++) {
        for (idx_y = 0; idx_y < m_size.y; idx_y++) {
            for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                m_cells.push_back (ParticleCell (vec3l (idx_x, idx_y, idx_z), m_size, *m_bounds));
            }
        }
    }
}
ParticlesGrid::~ParticlesGrid () {
}
void ParticlesGrid::add_particle (vec3f p_position) {
    get_cell_at (vec3l (p_position / *m_bounds * vec3f (m_size - 1L))).add_particle (p_position, m_max_id++);
}
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
void ParticlesGrid::step_1_prepare_cell (ParticleCell &p_cell) {
    unsigned int       i;
    const unsigned int max = p_cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        LennardJonesAlgorithm::step_1 (p_cell.m_positions_x[m_idx_a][i],
                                       p_cell.m_positions_y[m_idx_a][i],
                                       p_cell.m_positions_z[m_idx_a][i],
                                       p_cell.m_positions_x[m_idx_b][i],
                                       p_cell.m_positions_y[m_idx_b][i],
                                       p_cell.m_positions_z[m_idx_b][i]);
    }
}
void ParticlesGrid::step_2a_calculate_inside_cell (ParticleCell &p_cell) {
    unsigned int       i, j;
    const unsigned int max   = p_cell.m_ids.size ();
    const unsigned int max_1 = max - 1;
    if (max > 0) {
        for (i = 0; i < max_1; i++) {
            for (j = i + 1; j < max; j++) {
                LennardJonesAlgorithm::step_2 (p_cell.m_positions_x[m_idx_a][i],
                                               p_cell.m_positions_y[m_idx_a][i],
                                               p_cell.m_positions_z[m_idx_a][i],
                                               p_cell.m_positions_x[m_idx_b][i],
                                               p_cell.m_positions_y[m_idx_b][i],
                                               p_cell.m_positions_z[m_idx_b][i],
                                               p_cell.m_positions_x[m_idx_a][j],
                                               p_cell.m_positions_y[m_idx_a][j],
                                               p_cell.m_positions_z[m_idx_a][j],
                                               p_cell.m_positions_x[m_idx_b][j],
                                               p_cell.m_positions_y[m_idx_b][j],
                                               p_cell.m_positions_z[m_idx_b][j]);
            }
        }
    }
}
void ParticlesGrid::step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell &p_cell2) {
    unsigned int       i, j;
    const unsigned int max1 = p_cell1.m_ids.size ();
    const unsigned int max2 = p_cell2.m_ids.size ();
    for (i = 0; i < max1; i++) {
        for (j = 0; j < max2; j++) {
            LennardJonesAlgorithm::step_2 (p_cell1.m_positions_x[m_idx_a][i],
                                           p_cell1.m_positions_y[m_idx_a][i],
                                           p_cell1.m_positions_z[m_idx_a][i],
                                           p_cell1.m_positions_x[m_idx_b][i],
                                           p_cell1.m_positions_y[m_idx_b][i],
                                           p_cell1.m_positions_z[m_idx_b][i],
                                           p_cell2.m_positions_x[m_idx_a][j],
                                           p_cell2.m_positions_y[m_idx_a][j],
                                           p_cell2.m_positions_z[m_idx_a][j],
                                           p_cell2.m_positions_x[m_idx_b][j],
                                           p_cell2.m_positions_y[m_idx_b][j],
                                           p_cell2.m_positions_z[m_idx_b][j]);
        }
    }
}
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
unsigned long ParticlesGrid::get_cell_index (long x, long y, long z) {
    return x + m_size.x * (y + m_size.y * z);
}
ParticleCell &ParticlesGrid::get_cell_at (long x, long y, long z) {
    x = (x + m_size.x) % m_size.x; // apply periodic border
    y = (y + m_size.y) % m_size.y;
    z = (z + m_size.z) % m_size.z;
    return m_cells[get_cell_index (x, y, z)];
}
ParticleCell &ParticlesGrid::get_cell_at (vec3l coord) {
    return get_cell_at (coord.y, coord.y, coord.z);
}
void ParticlesGrid::step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell) {
    vec3l delta (0);
    int   i;
    for (i = p_cell.m_ids.size () - 1; i >= 0; i--) {
        delta = vec3l (0);
        if (p_cell.m_positions_x[m_idx_a][i] < p_cell.m_corner000.x) {
            delta.x = -1;
            while (p_cell.m_positions_x[m_idx_a][i] < 0) {
                p_cell.m_positions_x[m_idx_a][i] += m_bounds->x;
            }
        } else if (p_cell.m_positions_x[m_idx_a][i] > p_cell.m_corner111.x) {
            delta.x = +1;
            while (p_cell.m_positions_x[m_idx_a][i] > m_bounds->x) {
                p_cell.m_positions_x[m_idx_a][i] -= m_bounds->x;
            }
        }
        if (p_cell.m_positions_y[m_idx_a][i] < p_cell.m_corner000.y) {
            delta.y = -1;
            while (p_cell.m_positions_y[m_idx_a][i] < 0) {
                p_cell.m_positions_y[m_idx_a][i] += m_bounds->y;
            }
        } else if (p_cell.m_positions_y[m_idx_a][i] > p_cell.m_corner111.y) {
            delta.y = +1;
            while (p_cell.m_positions_y[m_idx_a][i] > m_bounds->y) {
                p_cell.m_positions_y[m_idx_a][i] -= m_bounds->y;
            }
        }
        if (p_cell.m_positions_z[m_idx_a][i] < p_cell.m_corner000.z) {
            delta.z = -1;
            while (p_cell.m_positions_z[m_idx_a][i] < 0) {
                p_cell.m_positions_z[m_idx_a][i] += m_bounds->z;
            }
        } else if (p_cell.m_positions_z[m_idx_a][i] > p_cell.m_corner111.z) {
            delta.z = +1;
            while (p_cell.m_positions_z[m_idx_a][i] > m_bounds->z) {
                p_cell.m_positions_z[m_idx_a][i] -= m_bounds->z;
            }
        }
        if (delta.x || delta.y || delta.z) {
            vec3f position (p_cell.m_positions_x[m_idx_a][i],
                            p_cell.m_positions_y[m_idx_a][i],
                            p_cell.m_positions_z[m_idx_a][i]);
            ParticleCell &other_cell = get_cell_at (vec3l (position / *m_bounds * vec3f (m_size - 1L)));
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
