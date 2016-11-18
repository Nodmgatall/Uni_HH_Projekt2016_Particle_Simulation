#include "../vec3.hpp"
#include <iostream>
#include <omp.h>
#include <vector>

#include "ParticlesGrid.hpp"

ParticlesGrid::ParticlesGrid (s_simulator_options *p_options, vec3f *p_bounds)
: ParticlesBase (p_options, p_bounds), m_iterations_between_rearange_particles (20) {
    long max_usefull_size                 = pow (m_options->m_particle_count, 1.0 / 3.0);
    m_iterations_until_rearange_particles = m_iterations_between_rearange_particles;
    m_stucture_name                       = "Grid";
    m_max_id                              = 0;
    m_idx_a = !(m_idx_b = 0);
    // cut_off_radius*1.2 to allow particles to move before reconstruction of cells is needed
    m_size = vec3l::max (vec3l (*m_bounds / (m_options->m_cut_off_radius * 1.2f)), max_usefull_size);
    m_size += 1L; // round up to next natural number for cell-count
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
void ParticlesGrid::add_particle (vec3f p_position, vec3f p_velocity) {
    get_cell_at (vec3l (p_position / *m_bounds * vec3f (m_size - 1L))).add_particle (p_position, p_velocity, m_max_id++);
}
void ParticlesGrid::serialize (std::shared_ptr<ParticleFileWriter> p_file_writer) {
    Benchmark::begin ("saving the data", false);
    p_file_writer->start ();
    for (ParticleCell cell : m_cells) {
        if (!(cell.m_ids.empty ())) {
            /*  p_file_writer->saveData (&(cell.m_positions_x),
                                     &(cell.m_positions_y),
                                     &(cell.m_positions_y),
                                     &(cell.m_positions_delta_x),
                                     &(cell.m_positions_delta_y),
                                     &(cell.m_positions_delta_z),
                                     &(cell.m_positions_delta_x), // TODO remove
                                     &(cell.m_positions_delta_y), // TODO remove
                                     &(cell.m_positions_delta_z), // TODO remove
             &(cell.m_ids));*/
        }
    }
    p_file_writer->end ();
    Benchmark::end ();
}
void ParticlesGrid::step_1_prepare_cell (ParticleCell &cell) {
    unsigned int       i;
    const unsigned int max = cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        lennard_jones_algorithm_1 (cell.m_positions_x[m_idx_a][i],
                                   cell.m_positions_y[m_idx_a][i],
                                   cell.m_positions_z[m_idx_a][i],
                                   cell.m_positions_x[m_idx_b][i],
                                   cell.m_positions_y[m_idx_b][i],
                                   cell.m_positions_z[m_idx_b][i]);
    }
}
void ParticlesGrid::step_2_calculate_inside_cell (ParticleCell &cell) {
    unsigned int       i, j;
    const unsigned int max   = cell.m_ids.size ();
    const unsigned int max_1 = max - 1;
    if (max > 0) {
        for (i = 0; i < max_1; i++) {
            for (j = i + 1; j < max; j++) {
                lennard_jones_algorithm_2 (cell.m_positions_x[m_idx_a][i],
                                           cell.m_positions_y[m_idx_a][i],
                                           cell.m_positions_z[m_idx_a][i],
                                           cell.m_positions_x[m_idx_b][i],
                                           cell.m_positions_y[m_idx_b][i],
                                           cell.m_positions_z[m_idx_b][i],
                                           cell.m_positions_x[m_idx_a][j],
                                           cell.m_positions_y[m_idx_a][j],
                                           cell.m_positions_z[m_idx_a][j],
                                           cell.m_positions_x[m_idx_b][j],
                                           cell.m_positions_y[m_idx_b][j],
                                           cell.m_positions_z[m_idx_b][j]);
            }
        }
    }
}
void ParticlesGrid::step_3_calculate_betweenCells (ParticleCell &cell1, ParticleCell &cell2) {
    unsigned int       i, j;
    const unsigned int max1 = cell1.m_ids.size ();
    const unsigned int max2 = cell2.m_ids.size ();
    for (i = 0; i < max1; i++) {
        for (j = 0; j < max2; j++) {
            lennard_jones_algorithm_2 (cell1.m_positions_x[m_idx_a][i],
                                       cell1.m_positions_y[m_idx_a][i],
                                       cell1.m_positions_z[m_idx_a][i],
                                       cell1.m_positions_x[m_idx_b][i],
                                       cell1.m_positions_y[m_idx_b][i],
                                       cell1.m_positions_z[m_idx_b][i],
                                       cell2.m_positions_x[m_idx_a][j],
                                       cell2.m_positions_y[m_idx_a][j],
                                       cell2.m_positions_z[m_idx_a][j],
                                       cell2.m_positions_x[m_idx_b][j],
                                       cell2.m_positions_y[m_idx_b][j],
                                       cell2.m_positions_z[m_idx_b][j]);
        }
    }
}
void ParticlesGrid::step_4_swap_old_new_position (ParticleCell &cell) {
    cell.m_positions_x[0].swap (cell.m_positions_x[1]);
    cell.m_positions_y[0].swap (cell.m_positions_y[1]);
    cell.m_positions_z[0].swap (cell.m_positions_z[1]);
}
void ParticlesGrid::run_simulation_iteration () {
    m_iterations_until_rearange_particles--;
    unsigned int idx_x, idx_y, idx_z, parallel_offset;
    Benchmark::begin ("step 1+2", false);
    //#pragma omp parallel for
    for (idx_x = 0; idx_x < m_size.x; idx_x++) {
        for (idx_y = 0; idx_y < m_size.y; idx_y++) {
            for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                ParticleCell &cell = get_cell_at (idx_x, idx_y, idx_z);
                step_1_prepare_cell (cell);
                step_2_calculate_inside_cell (cell);
            }
        }
    }
    Benchmark::end ();
    Benchmark::begin ("step 3", false);
    for (parallel_offset = 0; parallel_offset < 2; parallel_offset++) {
#pragma omp parallel for
        for (idx_x = parallel_offset; idx_x < m_size.x; idx_x += 2) {
            for (idx_y = 0; idx_y < m_size.y; idx_y++) {
                for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                    /* 3*3*3=27 'neighbors'
                     * -self => 26 'other cells'
                     * Symmetric /2 => 13 Pairs
                     */
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                   get_cell_at (idx_x + 1, idx_y + 1, idx_z + 1)); // 1
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                   get_cell_at (idx_x + 1, idx_y, idx_z)); // 2
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                   get_cell_at (idx_x + 1, idx_y + 1, idx_z)); // 3
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                   get_cell_at (idx_x + 1, idx_y, idx_z + 1)); // 4
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                   get_cell_at (idx_x + 1, idx_y + 1, idx_z)); // 5
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                   get_cell_at (idx_x + 1, idx_y, idx_z + 1)); // 6
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z),
                                                   get_cell_at (idx_x, idx_y + 1, idx_z + 1)); // 7
                    step_3_calculate_betweenCells (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                   get_cell_at (idx_x, idx_y + 1, idx_z)); // 8
                    step_3_calculate_betweenCells (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                   get_cell_at (idx_x, idx_y, idx_z + 1)); // 9
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y + 1, idx_z),
                                                   get_cell_at (idx_x, idx_y, idx_z + 1)); // 10
                    step_3_calculate_betweenCells (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                   get_cell_at (idx_x, idx_y + 1, idx_z + 1)); // 11
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y + 1, idx_z),
                                                   get_cell_at (idx_x + 1, idx_y, idx_z + 1)); // 12
                    step_3_calculate_betweenCells (get_cell_at (idx_x, idx_y, idx_z + 1),
                                                   get_cell_at (idx_x + 1, idx_y + 1, idx_z)); // 13
                }
            }
        }
    }
    Benchmark::end ();
    if (m_iterations_until_rearange_particles) {
        Benchmark::begin ("step 4", false);
#pragma omp parallel for
        for (idx_x = 0; idx_x < m_size.x; idx_x++) {
            for (idx_y = 0; idx_y < m_size.y; idx_y++) {
                for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                    step_4_swap_old_new_position (get_cell_at (idx_x, idx_y, idx_z));
                }
            }
        }
        Benchmark::end ();
    } else {
        Benchmark::begin ("step 4+5", false);
        for (parallel_offset = 0; parallel_offset < 3; parallel_offset++) {
#pragma omp parallel for
            for (idx_x = parallel_offset; idx_x < m_size.x; idx_x += 3) {
                for (idx_y = 0; idx_y < m_size.y; idx_y++) {
                    for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                        ParticleCell &cell = get_cell_at (idx_x, idx_y, idx_z);
                        step_4_swap_old_new_position (cell);
                        step_5_remove_wrong_particles_from_cell (cell);
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
    x = (x + m_size.x) % m_size.x;
    y = (x + m_size.y) % m_size.y;
    z = (x + m_size.z) % m_size.z;
    return m_cells[get_cell_index (x, y, z)];
}
ParticleCell &ParticlesGrid::get_cell_at (vec3l coord) {
    return get_cell_at (coord.y, coord.y, coord.z);
}
void ParticlesGrid::step_5_remove_wrong_particles_from_cell (ParticleCell &cell) {
    vec3l        delta (0);
    int          i;
    unsigned int j;
    for (i = cell.m_ids.size () - 1; i >= 0; i--) {
        delta = vec3l (0);
        if (cell.m_positions_x[m_idx_a][i] < cell.m_corner000.x) {
            delta.x = -1;
        } else if (cell.m_positions_x[m_idx_a][i] > cell.m_corner000.x) {
            delta.x = +1;
        }
        if (cell.m_positions_y[m_idx_a][i] < cell.m_corner000.y) {
            delta.y = -1;
        } else if (cell.m_positions_y[m_idx_a][i] > cell.m_corner000.y) {
            delta.y = +1;
        }
        if (cell.m_positions_z[m_idx_a][i] < cell.m_corner000.z) {
            delta.z = -1;
        } else if (cell.m_positions_z[m_idx_a][i] > cell.m_corner000.z) {
            delta.z = +1;
        }
        if (delta.x || delta.y || delta.z) {
            ParticleCell &other = get_cell_at (cell.m_idx + delta);
            other.m_ids.push_back (cell.m_ids[i]);
            cell.m_ids.erase (cell.m_ids.begin () + i);
            for (j = 0; j <= 1; j++) {
                other.m_positions_x[j].push_back (cell.m_positions_x[j][i]);
                other.m_positions_y[j].push_back (cell.m_positions_y[j][i]);
                other.m_positions_z[j].push_back (cell.m_positions_z[j][i]);
                cell.m_positions_y[j].erase (cell.m_positions_y[j].begin () + i);
                cell.m_positions_z[j].erase (cell.m_positions_z[j].begin () + i);
            }
        }
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
void ParticleCell::add_particle (vec3f p_position, vec3f p_velocity, int p_id) {
    unsigned int i;
    for (i = 0; i <= 1; i++) {
        m_positions_x[i].push_back (p_position.x);
        m_positions_y[i].push_back (p_position.y);
        m_positions_z[i].push_back (p_position.z);
    }
    m_ids.push_back (p_id);
}
