#include "ParticlesGrid.hpp"

#define NEXT_POSITION(cell, particle)                                             \
    cell.m_positions_x[m_idx_b][particle], cell.m_positions_y[m_idx_b][particle], \
        cell.m_positions_z[m_idx_b][particle]
#define OLD_POSITION(cell, particle) NEXT_POSITION (cell, particle)
#define CURR_POSITION(cell, particle)                                             \
    cell.m_positions_x[m_idx_a][particle], cell.m_positions_y[m_idx_a][particle], \
        cell.m_positions_z[m_idx_a][particle]

ParticlesGrid::ParticlesGrid (s_options &               p_options,
                              ParticleBoundsCorrection &p_particle_bounds_correction,
                              AlgorithmBase &           p_algorithm)
: ParticlesBase (p_options, p_particle_bounds_correction, p_algorithm),
  m_iterations_between_rearange_particles (20) {
    unsigned int idx_x, idx_y, idx_z;
    long         max_usefull_size         = pow (m_options.m_particle_count, 1.0 / 3.0);
    m_iterations_until_rearange_particles = m_iterations_between_rearange_particles;
    m_stucture_name                       = "Grid";
    m_max_id                              = 0;
    m_idx_a = !(m_idx_b = 0);
    // cut_off_radius*1.2 to allow particles to move before reconstruction of cells is needed
    m_size = Vec3l::min (Vec3l (m_options.m_bounds / (m_options.m_cut_off_radius * 1.2f)), max_usefull_size);
    m_size          = m_size + 1L; // round up to next natural number for cell-count
    m_size          = Vec3l::max (m_size, Vec3l (4L));
    m_size_per_cell = Vec3f (m_size - 1L) / m_options.m_bounds;
    m_cells.reserve (m_size.x * m_size.y * m_size.z);
    for (idx_x = 0; idx_x < m_size.x; idx_x++) {
        for (idx_y = 0; idx_y < m_size.y; idx_y++) {
            for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                m_cells.push_back (ParticleCell (Vec3l (idx_x, idx_y, idx_z), m_size, m_options.m_bounds));
            }
        }
    }
}
ParticlesGrid::~ParticlesGrid () {
}
unsigned long ParticlesGrid::get_cell_index (long x, long y, long z) {
    return x + m_size.x * (y + m_size.y * z);
}
ParticleCell &ParticlesGrid::get_cell_at (long x, long y, long z) {
    return m_cells[get_cell_index (x, y, z)];
}
ParticleCell &ParticlesGrid::get_cell_for_particle (data_type x, data_type y, data_type z) {
    return get_cell_at (x * m_size_per_cell.x, y * m_size_per_cell.y, z * m_size_per_cell.z);
}
ParticleCell &ParticlesGrid::get_cell_for_particle (Vec3f m_position) {
    return get_cell_for_particle (m_position.x, m_position.y, m_position.z);
}
/**
 * adds an particle to the current simulation
 * @param p_position the position of the new particle
 */
void ParticlesGrid::add_particle (Vec3f p_current_position) {
    add_particle (p_current_position, Vec3f (0));
}
/**
 *
 * adds an particle to the current simulation
 * @param p_position the position of the new particle
 * @param p_velocity the initial velocity
 */
void ParticlesGrid::add_particle (Vec3f p_current_position, Vec3f p_current_velocity) {
    Vec3f old_position = p_current_position - p_current_velocity * m_options.m_timestep;
    m_particle_bounds_correction.updatePosition (p_current_position.x,
                                                 p_current_position.y,
                                                 p_current_position.z,
                                                 old_position.x,
                                                 old_position.y,
                                                 old_position.z);

    get_cell_for_particle (p_current_position).add_particle (p_current_position, old_position, m_idx_a, m_max_id++);
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
        m_algorithm.step_1 (CURR_POSITION (p_cell, i), NEXT_POSITION (p_cell, i));
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
                m_algorithm.step_2 (CURR_POSITION (p_cell, i),
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
            m_algorithm.step_2 (CURR_POSITION (p_cell1, i),
                                NEXT_POSITION (p_cell1, i),
                                CURR_POSITION (p_cell2, j),
                                NEXT_POSITION (p_cell2, j));
        }
    }
}
/**
 * verify that all particles in cell are in the correct cell. if there are particles which should be
 * in an other cell, these particles get moved
 * @param p_cell
 */
void ParticlesGrid::step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell) {
    int i;
    for (i = p_cell.m_ids.size () - 1; i >= 0; i--) {
        if (m_particle_bounds_correction.updatePosition (CURR_POSITION (p_cell, i),
                                                         NEXT_POSITION (p_cell, i),
                                                         p_cell.m_corner000,
                                                         p_cell.m_corner111)) {
            ParticleCell &other_cell = get_cell_for_particle (CURR_POSITION (p_cell, i));
            moveParticle (p_cell, other_cell, i);
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
#ifdef OMP_AVAILABLE
    omp_set_num_threads (1);
#pragma omp parallel for
#endif
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
    // TODO wraparount cell combinations never evaluated -> upper_loop_limit!!
    for (parallel_offset = 0; parallel_offset < 2; parallel_offset++) {
#ifdef OMP_AVAILABLE
#pragma omp parallel for
#endif
        for (idx_x = parallel_offset; idx_x < m_size.x - 1; idx_x += 2) {
            for (idx_y = 0; idx_y < m_size.y - 1; idx_y++) {
                for (idx_z = 0; idx_z < m_size.z - 1; idx_z++) {
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
#ifdef OMP_AVAILABLE
#pragma omp parallel for
#endif
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
 * moves an particle from one cell to another
 * @param p_cell_from
 * @param p_cell_to
 * @param p_index_from
 */
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
/**
 * @return the total number of particles in all cells
 */
unsigned long ParticlesGrid::get_particle_count () {
    unsigned long particle_count = 0;
    for (ParticleCell cell : m_cells) {
        particle_count += cell.m_ids.size ();
    }
    return particle_count;
}
ParticleCell::ParticleCell (Vec3l p_idx, Vec3l p_size, Vec3f &p_bounds) {
    m_idx       = p_idx;
    m_corner000 = Vec3f (m_idx) / Vec3f (p_size) * p_bounds;
    m_corner111 = Vec3f (m_idx + 1L) / Vec3f (p_size) * p_bounds;
}
void ParticleCell::add_particle (Vec3f p_current_position, Vec3f p_old_position, int p_current_index, int p_id) {
    m_positions_x[p_current_index].push_back (p_current_position.x);
    m_positions_y[p_current_index].push_back (p_current_position.y);
    m_positions_z[p_current_index].push_back (p_current_position.z);
    m_positions_x[!p_current_index].push_back (p_old_position.x);
    m_positions_y[!p_current_index].push_back (p_old_position.y);
    m_positions_z[!p_current_index].push_back (p_old_position.z);
    m_ids.push_back (p_id);
}
