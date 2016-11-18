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
    m_index_a = !(m_index_b = 0);

    // cut_off_radius*1.2 to allow particles to move before reconstruction of cells is needed
    m_size = vec3l::max (vec3l (*m_bounds / (m_options->m_cut_off_radius * 1.2f)), max_usefull_size);
    m_size += 1L; // round up to next natural number for cell-count
    m_cells.reserve (m_size.x * m_size.y * m_size.z);
    unsigned int i, j, k;
    for (i = 0; i < m_size.x; i++) {
        for (j = 0; j < m_size.y; j++) {
            for (k = 0; k < m_size.z; k++) {
                m_cells.push_back (ParticleCell (vec3l (i, j, k), m_size, *m_bounds));
            }
        }
    }
}
ParticlesGrid::~ParticlesGrid () {
}
void ParticlesGrid::add_particle (vec3f p_position, vec3f p_velocity) {
    getCellAt (vec3l (p_position / *m_bounds * vec3f (m_size - 1L))).add_particle (p_position, p_velocity, m_max_id++);
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
void ParticlesGrid::run_simulation_lennard_jones_1_prepare_cell (ParticleCell &cell) {
    unsigned int i;
    unsigned int max = cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        lennard_jones_algorithm_1 (cell.m_positions_x[m_index_a][i],
                                   cell.m_positions_y[m_index_a][i],
                                   cell.m_positions_z[m_index_a][i],
                                   cell.m_positions_x[m_index_b][i],
                                   cell.m_positions_y[m_index_b][i],
                                   cell.m_positions_z[m_index_b][i]);
    }
}
void ParticlesGrid::run_simulation_lennard_jones_2_inside_cell (ParticleCell &cell) {
    unsigned int       i, j;
    const unsigned int max = cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        for (j = i + 1; j < max; j++) {
            lennard_jones_algorithm_2 (cell.m_positions_x[m_index_a][i],
                                       cell.m_positions_y[m_index_a][i],
                                       cell.m_positions_z[m_index_a][i],
                                       cell.m_positions_x[m_index_b][i],
                                       cell.m_positions_y[m_index_b][i],
                                       cell.m_positions_z[m_index_b][i],
                                       cell.m_positions_x[m_index_a][j],
                                       cell.m_positions_y[m_index_a][j],
                                       cell.m_positions_z[m_index_a][j],
                                       cell.m_positions_x[m_index_b][j],
                                       cell.m_positions_y[m_index_b][j],
                                       cell.m_positions_z[m_index_b][j]);
        }
    }
}
void ParticlesGrid::run_simulation_lennard_jones_3_betweenCells (ParticleCell &cell1, ParticleCell &cell2) {
    unsigned int       i, j;
    const unsigned int max1 = cell1.m_ids.size ();
    const unsigned int max2 = cell2.m_ids.size ();
    for (i = 0; i < max1; i++) {
        for (j = 0; j < max2; j++) {
            lennard_jones_algorithm_2 (cell1.m_positions_x[m_index_a][i],
                                       cell1.m_positions_y[m_index_a][i],
                                       cell1.m_positions_z[m_index_a][i],
                                       cell1.m_positions_x[m_index_b][i],
                                       cell1.m_positions_y[m_index_b][i],
                                       cell1.m_positions_z[m_index_b][i],
                                       cell2.m_positions_x[m_index_a][j],
                                       cell2.m_positions_y[m_index_a][j],
                                       cell2.m_positions_z[m_index_a][j],
                                       cell2.m_positions_x[m_index_b][j],
                                       cell2.m_positions_y[m_index_b][j],
                                       cell2.m_positions_z[m_index_b][j]);
        }
    }
}
void ParticlesGrid::run_simulation_lennard_jones_4_swap (ParticleCell &cell) {
    cell.m_positions_x[0].swap (cell.m_positions_x[1]);
    cell.m_positions_y[0].swap (cell.m_positions_y[1]);
    cell.m_positions_z[0].swap (cell.m_positions_z[1]);
}
void ParticlesGrid::run_simulation_iteration () {
#pragma omp parallel
    {
        unsigned int cell_x, cell_y, cell_z, parallel_offset;
#pragma omp for schedule(guided, 5)
        for (cell_x = 0; cell_x < m_size.x; cell_x++) {
            for (cell_y = 0; cell_y < m_size.y; cell_y++) {
                for (cell_z = 0; cell_z < m_size.z; cell_z++) {
                    ParticleCell &cell = getCellAt (cell_x, cell_y, cell_z);
                    run_simulation_lennard_jones_1_prepare_cell (cell);
                    run_simulation_lennard_jones_2_inside_cell (cell);
                }
            }
        }
        for (parallel_offset = 0; parallel_offset <= 1; parallel_offset++) {
#pragma omp for schedule(static, 1) nowait
            for (cell_x = parallel_offset; cell_x < m_size.x; cell_x += 2) {
                for (cell_y = 0; cell_y < m_size.y; cell_y++) {
                    for (cell_z = 0; cell_z < m_size.z; cell_z++) {
                        /* 3*3*3=27 'neighbors'
                         * -self => 26 'other cells'
                         * Symmetric /2 => 13 Pairs
                         */
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z),
                                                                     getCellAt (cell_x + 1, cell_y + 1, cell_z + 1)); // 1
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z),
                                                                     getCellAt (cell_x + 1, cell_y, cell_z)); // 2
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z),
                                                                     getCellAt (cell_x + 1, cell_y + 1, cell_z)); // 3
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z),
                                                                     getCellAt (cell_x + 1, cell_y, cell_z + 1)); // 4
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z),
                                                                     getCellAt (cell_x + 1, cell_y + 1, cell_z)); // 5
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z),
                                                                     getCellAt (cell_x + 1, cell_y, cell_z + 1)); // 6
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z),
                                                                     getCellAt (cell_x, cell_y + 1, cell_z + 1)); // 7
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x + 1, cell_y, cell_z),
                                                                     getCellAt (cell_x, cell_y + 1, cell_z)); // 8
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x + 1, cell_y, cell_z),
                                                                     getCellAt (cell_x, cell_y, cell_z + 1)); // 9
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y + 1, cell_z),
                                                                     getCellAt (cell_x, cell_y, cell_z + 1)); // 10
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x + 1, cell_y, cell_z),
                                                                     getCellAt (cell_x, cell_y + 1, cell_z + 1)); // 11
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y + 1, cell_z),
                                                                     getCellAt (cell_x + 1, cell_y, cell_z + 1)); // 12
                        run_simulation_lennard_jones_3_betweenCells (getCellAt (cell_x, cell_y, cell_z + 1),
                                                                     getCellAt (cell_x + 1, cell_y + 1, cell_z)); // 13
                    }
                }
            }
        }
#pragma omp for schedule(guided, 5)
        for (cell_x = 0; cell_x < m_size.x; cell_x++) {
            for (cell_y = 0; cell_y < m_size.y; cell_y++) {
                for (cell_z = 0; cell_z < m_size.z; cell_z++) {
                    run_simulation_lennard_jones_4_swap (getCellAt (cell_x, cell_y, cell_z));
                }
            }
        }
    }
    m_iterations_until_rearange_particles--;
    if (!m_iterations_until_rearange_particles) {
        removeWrongParticlesFromCells ();
        m_iterations_until_rearange_particles = m_iterations_between_rearange_particles;
    }
    m_index_b = !(m_index_a = m_index_b);
}
unsigned int ParticlesGrid::getCellIndex (int x, int y, int z) {
    return x + m_size.x * (y + m_size.y * z);
}
ParticleCell &ParticlesGrid::getCellAt (int x, int y, int z) {
    x = (x + m_size.x) % m_size.x;
    y = (x + m_size.y) % m_size.y;
    z = (x + m_size.z) % m_size.z;
    return m_cells[getCellIndex (x, y, z)];
}
ParticleCell &ParticlesGrid::getCellAt (vec3l coord) {
    return getCellAt (coord.y, coord.y, coord.z);
}

void ParticlesGrid::removeWrongParticlesFromCell (ParticleCell &cell) {
    vec3l        delta (0);
    int          i;
    unsigned int j;
    for (i = cell.m_ids.size () - 1; i >= 0; i--) {
        delta = vec3l (0);
        if (cell.m_positions_x[m_index_a][i] < cell.m_corner000.x) {
            delta.x = -1;
        } else if (cell.m_positions_x[m_index_a][i] > cell.m_corner000.x) {
            delta.x = +1;
        }
        if (cell.m_positions_y[m_index_a][i] < cell.m_corner000.y) {
            delta.y = -1;
        } else if (cell.m_positions_y[m_index_a][i] > cell.m_corner000.y) {
            delta.y = +1;
        }
        if (cell.m_positions_z[m_index_a][i] < cell.m_corner000.z) {
            delta.z = -1;
        } else if (cell.m_positions_z[m_index_a][i] > cell.m_corner000.z) {
            delta.z = +1;
        }
        if (delta.x || delta.y || delta.z) {
            ParticleCell &other = getCellAt (cell.m_index + delta);
            other.m_ids.push_back (cell.m_ids[i]);
            cell.m_ids.erase (cell.m_ids.begin () + i);
            for (j = 0; j <= 1; j++) {
                other.m_positions_x[j].push_back (cell.m_positions_x[j][i]);
                other.m_positions_y[j].push_back (cell.m_positions_y[j][i]);
                other.m_positions_z[j].push_back (cell.m_positions_z[j][i]);
                cell.m_positions_x[j].erase (cell.m_positions_x[j].begin () + i);
                cell.m_positions_y[j].erase (cell.m_positions_y[j].begin () + i);
                cell.m_positions_z[j].erase (cell.m_positions_z[j].begin () + i);
            }
        }
    }
}

void ParticlesGrid::removeWrongParticlesFromCells () {
#pragma omp parallel
    {
        unsigned int i, j, k, l;
        for (l = 0; l <= 2; l++) {
#pragma omp for schedule(static, 1) nowait
            for (i = l; i < m_size.x; i += 3) {
                for (j = 0; j < m_size.y; j++) {
                    for (k = 0; k < m_size.z; k++) {
                        removeWrongParticlesFromCell (getCellAt (i, j, k));
                    }
                }
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

ParticleCell::ParticleCell (vec3l p_index, vec3l p_size, vec3f &p_bounds) {
    m_index     = p_index;
    m_corner000 = vec3f (m_index) / vec3f (p_size) * p_bounds;
    m_corner111 = vec3f (m_index + 1L) / vec3f (p_size) * p_bounds;
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
