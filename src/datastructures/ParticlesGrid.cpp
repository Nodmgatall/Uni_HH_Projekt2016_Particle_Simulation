#include "../vec3.hpp"
#include <iostream>
#include <omp.h>
#include <vector>

#include "ParticlesGrid.hpp"

ParticlesGrid::ParticlesGrid (s_simulator_options *p_options, vec3f *p_bounds)
: ParticlesBase (p_options, p_bounds) {
    int  abs_size;
    long max_usefull_size = pow (m_options->m_particle_count, 1.0 / 3.0);
    m_stucture_name       = "Grid";
    m_max_id              = 0;
    // cut_off_radius*1.2 to allow particles to move before reconstruction of cells is needed
    m_size = vec3l::max (vec3l (*m_bounds / (m_options->m_cut_off_radius * 1.2f)), max_usefull_size);
    m_size += 1L; // round up to next natural number for cell-count
    abs_size = m_size.x * m_size.y * m_size.z;
    m_cells.reserve (abs_size);
    for (int i = 0; i < abs_size; i++) {
        m_cells.push_back (ParticleCell ());
    }
}
ParticlesGrid::~ParticlesGrid () {
}
void ParticlesGrid::add_particle (vec3f p_position, vec3f p_velocity) {
    getCellAt (vec3l (p_position/ *m_bounds * vec3f (m_size - 1L))).add_particle (p_position, p_velocity, m_max_id++);
}
void ParticlesGrid::serialize (std::shared_ptr<ParticleFileWriter> p_file_writer) {
    Benchmark::begin ("saving the data", false);
    p_file_writer->start ();
    for (ParticleCell cell : m_cells) {
        if (!(cell.m_ids.empty ())) {
            p_file_writer->saveData (&(cell.m_positions_x),
                                     &(cell.m_positions_y),
                                     &(cell.m_positions_y),
                                     &(cell.m_positions_delta_x),
                                     &(cell.m_positions_delta_y),
                                     &(cell.m_positions_delta_z),
                                     &(cell.m_positions_delta_x), // TODO remove
                                     &(cell.m_positions_delta_y), // TODO remove
                                     &(cell.m_positions_delta_z), // TODO remove
                                     &(cell.m_ids));
        }
    }
    p_file_writer->end ();
    Benchmark::end ();
}
void ParticlesGrid::run_simulation_insideCell (ParticleCell &cell) {
    unsigned int       i, j;
    const unsigned int max = cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        for (j = i + 1; j < max; j++) {
            m_algorithm (cell.m_positions_x[i],
                         cell.m_positions_y[i],
                         cell.m_positions_z[i],
                         cell.m_positions_delta_x[i],
                         cell.m_positions_delta_y[i],
                         cell.m_positions_delta_z[i],
                         cell.m_positions_x[j],
                         cell.m_positions_y[j],
                         cell.m_positions_z[j],
                         cell.m_positions_delta_x[j],
                         cell.m_positions_delta_y[j],
                         cell.m_positions_delta_z[j]);
        }
    }
}
void ParticlesGrid::run_simulation_betweenCells (ParticleCell &cell1, ParticleCell &cell2) {
    unsigned int       i, j;
    const unsigned int max1 = cell1.m_ids.size ();
    const unsigned int max2 = cell2.m_ids.size ();
    for (i = 0; i < max1; i++) {
        for (j = 0; j < max2; j++) {
            m_algorithm (cell1.m_positions_x[i],
                         cell1.m_positions_y[i],
                         cell1.m_positions_z[i],
                         cell1.m_positions_delta_x[i],
                         cell1.m_positions_delta_y[i],
                         cell1.m_positions_delta_z[i],
                         cell2.m_positions_x[j],
                         cell2.m_positions_y[j],
                         cell2.m_positions_z[j],
                         cell2.m_positions_delta_x[j],
                         cell2.m_positions_delta_y[j],
                         cell2.m_positions_delta_z[j]);
        }
    }
}
void ParticlesGrid::run_simulation_iteration () {
#pragma omp parallel
    {
        unsigned int   i, j, k;
#pragma omp for nowait schedule(static, 1)
        for (i = 0; i < m_size.x - 1; i += 2) {
            for (j = 0; j < m_size.y - 1; j++) {
                for (k = 0; k < m_size.z - 1; k++) {
                    /* 3*3*3=27 'neighbors'
                     * -self => 26 'other cells'
                     * Symmetric /2 => 13 Pairs
                     */
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j + 1, k + 1)); // 1
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k)); // 2
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j + 1, k)); // 3
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k + 1)); // 4
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j + 1, k)); // 5
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k + 1)); // 6
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i, j + 1, k + 1)); // 7
                    run_simulation_betweenCells (getCellAt (i + 1, j, k), getCellAt (i, j + 1, k)); // 8
                    run_simulation_betweenCells (getCellAt (i + 1, j, k), getCellAt (i, j, k + 1)); // 9
                    run_simulation_betweenCells (getCellAt (i, j + 1, k), getCellAt (i, j, k + 1)); // 10
                    run_simulation_betweenCells (getCellAt (i + 1, j, k), getCellAt (i, j + 1, k + 1)); // 11
                    run_simulation_betweenCells (getCellAt (i, j + 1, k), getCellAt (i + 1, j, k + 1)); // 12
                    run_simulation_betweenCells (getCellAt (i, j, k + 1), getCellAt (i + 1, j + 1, k)); // 13
                }
            }
        }
#pragma omp for nowait schedule(guided, 5)
        for (i = 1; i < m_size.x - 1; i += 2) {
            for (j = 0; j < m_size.y - 1; j++) {
                for (k = 0; k < m_size.z - 1; k++) {
                    /* 3*3*3=27 'neighbors'
                     * -self => 26 'other cells'
                     * Symmetric /2 => 13 Pairs
                     */
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j + 1, k + 1)); // 1
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k)); // 2
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j + 1, k)); // 3
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k + 1)); // 4
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j + 1, k)); // 5
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i + 1, j, k + 1)); // 6
                    run_simulation_betweenCells (getCellAt (i, j, k), getCellAt (i, j + 1, k + 1)); // 7
                    run_simulation_betweenCells (getCellAt (i + 1, j, k), getCellAt (i, j + 1, k)); // 8
                    run_simulation_betweenCells (getCellAt (i + 1, j, k), getCellAt (i, j, k + 1)); // 9
                    run_simulation_betweenCells (getCellAt (i, j + 1, k), getCellAt (i, j, k + 1)); // 10
                    run_simulation_betweenCells (getCellAt (i + 1, j, k), getCellAt (i, j + 1, k + 1)); // 11
                    run_simulation_betweenCells (getCellAt (i, j + 1, k), getCellAt (i + 1, j, k + 1)); // 12
                    run_simulation_betweenCells (getCellAt (i, j, k + 1), getCellAt (i + 1, j + 1, k)); // 13
                }
            }
        }
#pragma omp for schedule(guided, 5)
        for (i = 0; i < m_size.x; i++) {
            for (j = 0; j < m_size.y; j++) {
                for (k = 0; k < m_size.z; k++) {
                    run_simulation_insideCell (getCellAt (i, j, k));
                }
            }
        }
    }
}
ParticleCell &ParticlesGrid::getCellAt (int x, int y, int z) {
    return m_cells[x + m_size.x * (y + m_size.y * z)];
}
ParticleCell &ParticlesGrid::getCellAt (vec3l coord) {
    return getCellAt(coord.y,coord.y,coord.z);
}
unsigned long ParticlesGrid::get_particle_count () {
    unsigned long particle_count = 0;
    for (ParticleCell cell : m_cells) {
        particle_count += cell.m_ids.size ();
    }
    return particle_count;
}
void ParticleCell::add_particle (vec3f p_position, vec3f p_velocity, int p_id) {
    m_positions_x.push_back (p_position.x);
    m_positions_y.push_back (p_position.y);
    m_positions_z.push_back (p_position.z);
    m_positions_delta_x.push_back (p_velocity.x);
    m_positions_delta_y.push_back (p_velocity.y);
    m_positions_delta_z.push_back (p_velocity.z);
    m_ids.push_back (p_id);
}
