#include "DatastructureGrid.hpp"

DatastructureGrid::DatastructureGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name  = "DatastructureGrid";
    m_error_happened = false;
    unsigned int idx_x, idx_y, idx_z;
    long         max_usefull_size         = pow (m_options.m_particle_count, 1.0 / 3.0);
    m_iterations_until_rearange_particles = m_options.m_max_iterations_between_datastructure_rebuild;
    m_max_id                              = 0;
    m_idx_a = !(m_idx_b = 0);
    // cut_off_radius*1.2 to allow particles to move before reconstruction of
    // cells is needed
    m_size = Vec3l::min (Vec3l (m_options.m_bounds / (m_options.m_cut_off_radius * 1.2f)), max_usefull_size);
    // m_size          = m_size + 1L; // round up to next natural number for cell-count
    m_size          = Vec3l::max (m_size, Vec3l (2L));
    m_size_per_cell = m_options.m_bounds / Vec3f (m_size);
    m_size += 2; // 2 randzellen (links+rechts jeweils 1)
    m_cells.reserve (m_size.x * m_size.y * m_size.z);
    for (idx_x = 0; idx_x < m_size.x; idx_x++) {
        for (idx_y = 0; idx_y < m_size.y; idx_y++) {
            for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                m_cells.push_back (ParticleCell (Vec3l (idx_x, idx_y, idx_z), m_size_per_cell));
            }
        }
    }
    if (m_options.m_cut_off_radius < 1) {
        std::cout << DEBUG_VAR (m_options.m_cut_off_radius) << std::endl;
        m_options.m_cut_off_radius = 1;
    }
    std::cout << DEBUG_VAR (m_stucture_name) << std::endl;
    std::cout << DEBUG_VAR (m_size) << std::endl;
    std::cout << DEBUG_VAR (m_size_per_cell) << std::endl;
    std::cout << DEBUG_VAR (m_options.m_bounds) << std::endl;
}
DatastructureGrid::~DatastructureGrid () {
}
unsigned long DatastructureGrid::get_cell_index (long x, long y, long z) {
    return x + m_size.x * (y + m_size.y * z);
}
ParticleCell& DatastructureGrid::get_cell_at (long x, long y, long z) {
    return m_cells[get_cell_index (x, y, z)];
}
ParticleCell& DatastructureGrid::get_cell_for_particle (data_type x, data_type y, data_type z) {
    Vec3l idx = get_cell_index_for_particle (x, y, z);
    return m_cells[get_cell_index (idx.x, idx.y, idx.z)];
}
Vec3l DatastructureGrid::get_cell_index_for_particle (data_type x, data_type y, data_type z) {
    return Vec3l ((long) (x / m_size_per_cell.x) + 1,
                  (long) (y / m_size_per_cell.y) + 1,
                  (long) (z / m_size_per_cell.z) + 1);
}
ParticleCell& DatastructureGrid::get_cell_for_particle (Vec3f m_position) {
    return get_cell_for_particle (m_position.x, m_position.y, m_position.z);
}
void DatastructureGrid::add_particle (Vec3f p_current_position) {
    add_particle (p_current_position, Vec3f (0));
}
void DatastructureGrid::add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id) {
    long id = 0;
    if (p_id >= 0) {
        id       = p_id;
        m_max_id = MAX (m_max_id, p_id + 1);
    } else {
        id = m_max_id++;
    }
    Vec3f old_position = p_current_position - p_current_velocity * m_options.m_timestep;

    m_border.updatePosition (p_current_position.x,
                             p_current_position.y,
                             p_current_position.z,
                             old_position.x,
                             old_position.y,
                             old_position.z);
    ParticleCell& cell = get_cell_for_particle (p_current_position);
    cell.add_particle (p_current_position, old_position, m_idx_a, id);
}
void DatastructureGrid::serialize () {
    Benchmark::begin ("saving the data", false);
    m_writer.start ();
    for (ParticleCell cell : m_cells) {
        if (!(cell.m_ids.empty ())) {
            m_writer.saveData (cell.m_positions_x[m_idx_a],
                               cell.m_positions_y[m_idx_a],
                               cell.m_positions_z[m_idx_a],
                               cell.m_ids);
        }
    }
    m_writer.end ();
    Benchmark::end ();
}
void DatastructureGrid::step_1_prepare_cell (ParticleCell& p_cell) {
    unsigned int       i;
    const unsigned int max = p_cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        m_algorithm.step_1 (p_cell.m_positions_x[m_idx_a][i],
                            p_cell.m_positions_y[m_idx_a][i],
                            p_cell.m_positions_z[m_idx_a][i],
                            p_cell.m_positions_x[m_idx_b][i],
                            p_cell.m_positions_y[m_idx_b][i],
                            p_cell.m_positions_z[m_idx_b][i]);
    }
}
void DatastructureGrid::step_2a_calculate_inside_cell (ParticleCell& p_cell) {
    unsigned long      i;
    const unsigned int max   = p_cell.m_ids.size ();
    const unsigned int max_1 = max - 1;
    if (max > 0) {
        for (i = 0; i < max_1; i++) {
            m_algorithm.step_2 (p_cell.m_positions_x[m_idx_a][i],
                                p_cell.m_positions_y[m_idx_a][i],
                                p_cell.m_positions_z[m_idx_a][i],
                                p_cell.m_positions_x[m_idx_b][i],
                                p_cell.m_positions_y[m_idx_b][i],
                                p_cell.m_positions_z[m_idx_b][i],
                                p_cell.m_positions_x[m_idx_a].data (),
                                p_cell.m_positions_y[m_idx_a].data (),
                                p_cell.m_positions_z[m_idx_a].data (),
                                p_cell.m_positions_x[m_idx_b].data (),
                                p_cell.m_positions_y[m_idx_b].data (),
                                p_cell.m_positions_z[m_idx_b].data (),
                                i + 1,
                                max);
        }
    }
}
void DatastructureGrid::step_2b_calculate_between_cells (ParticleCell& p_cell_i, ParticleCell& p_cell_j) {
    unsigned int       i;
    const unsigned int max = p_cell_i.m_ids.size ();
    for (i = 0; i < max; i++) {
        m_algorithm.step_2 (p_cell_i.m_positions_x[m_idx_a][i],
                            p_cell_i.m_positions_y[m_idx_a][i],
                            p_cell_i.m_positions_z[m_idx_a][i],
                            p_cell_i.m_positions_x[m_idx_b][i],
                            p_cell_i.m_positions_y[m_idx_b][i],
                            p_cell_i.m_positions_z[m_idx_b][i],
                            p_cell_j.m_positions_x[m_idx_a].data (),
                            p_cell_j.m_positions_y[m_idx_a].data (),
                            p_cell_j.m_positions_z[m_idx_a].data (),
                            p_cell_j.m_positions_x[m_idx_b].data (),
                            p_cell_j.m_positions_y[m_idx_b].data (),
                            p_cell_j.m_positions_z[m_idx_b].data (),
                            0,
                            p_cell_j.m_ids.size ());
    }
}
void DatastructureGrid::step_2b_calculate_between_cells_offset (ParticleCell& p_cell_i,
                                                                ParticleCell& p_cell_j,
                                                                data_type     offset_x,
                                                                data_type     offset_y,
                                                                data_type     offset_z) {
    unsigned int       i;
    const unsigned int max = p_cell_i.m_ids.size ();
    for (i = 0; i < max; i++) {
        m_algorithm.step_2_offset (offset_x,
                                   offset_y,
                                   offset_z,
                                   p_cell_i.m_positions_x[m_idx_a][i],
                                   p_cell_i.m_positions_y[m_idx_a][i],
                                   p_cell_i.m_positions_z[m_idx_a][i],
                                   p_cell_i.m_positions_x[m_idx_b][i],
                                   p_cell_i.m_positions_y[m_idx_b][i],
                                   p_cell_i.m_positions_z[m_idx_b][i],
                                   p_cell_j.m_positions_x[m_idx_a].data (),
                                   p_cell_j.m_positions_y[m_idx_a].data (),
                                   p_cell_j.m_positions_z[m_idx_a].data (),
                                   p_cell_j.m_positions_x[m_idx_b].data (),
                                   p_cell_j.m_positions_y[m_idx_b].data (),
                                   p_cell_j.m_positions_z[m_idx_b].data (),
                                   0,
                                   p_cell_j.m_ids.size ());
    }
}

void DatastructureGrid::step_3_remove_wrong_particles_from_cell (ParticleCell& p_cell) {
    int i, j;
    for (i = p_cell.m_ids.size () - 1; i >= 0; i--) {
        Vec3l idx;
        while (p_cell.m_positions_x[m_idx_a][i] < 0) {
            if (p_cell.m_positions_x[m_idx_a][i] < -m_options.m_bounds.x * 1000) {
                m_error_stream << "something went badly wrong " << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_x[j][i] += m_options.m_bounds.x;
            }
        }
        while (p_cell.m_positions_x[m_idx_a][i] >= m_options.m_bounds.x) {
            if (p_cell.m_positions_x[m_idx_a][i] > m_options.m_bounds.x * 1000) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_x[j][i] -= m_options.m_bounds.x;
            }
        }
        while (p_cell.m_positions_y[m_idx_a][i] < 0) {
            if (p_cell.m_positions_y[m_idx_a][i] < -m_options.m_bounds.y * 1000) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_y[j][i] += m_options.m_bounds.y;
            }
        }
        while (p_cell.m_positions_y[m_idx_a][i] > m_options.m_bounds.y) {
            if (p_cell.m_positions_x[m_idx_a][i] > m_options.m_bounds.y * 1000) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_y[j][i] -= m_options.m_bounds.y;
            }
        }
        while (p_cell.m_positions_z[m_idx_a][i] < 0) {
            if (p_cell.m_positions_z[m_idx_a][i] < -m_options.m_bounds.z * 1000) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_z[j][i] += m_options.m_bounds.z;
            }
        }
        while (p_cell.m_positions_z[m_idx_a][i] >= m_options.m_bounds.z) {
            if (p_cell.m_positions_z[m_idx_a][i] > m_options.m_bounds.z * 1000) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_z[j][i] -= m_options.m_bounds.z;
            }
        }
        idx = get_cell_index_for_particle (p_cell.m_positions_x[m_idx_a][i],
                                           p_cell.m_positions_y[m_idx_a][i],
                                           p_cell.m_positions_z[m_idx_a][i]);
        if (idx != p_cell.m_idx) {
            ParticleCell& other_cell = get_cell_at (idx.x, idx.y, idx.z);
            moveParticle (p_cell, other_cell, i);
        }
    }
}
bool DatastructureGrid::run_simulation_iteration (unsigned long p_iteration_number) {
    m_error_happened = false;
    (void) p_iteration_number;
    std::cout << DEBUG_VAR (p_iteration_number) << std::endl;
    m_iterations_until_rearange_particles--;
    unsigned int idx_x, idx_y, idx_z, parallel_offset;
    Benchmark::begin ("step 1+2a", false);

    for (idx_x = 0; idx_x < m_size.x; idx_x++) {
        for (idx_y = 0; idx_y < m_size.y; idx_y++) {
            for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                ParticleCell& cell = get_cell_at (idx_x, idx_y, idx_z);
                step_1_prepare_cell (cell);
                step_2a_calculate_inside_cell (cell);
            }
        }
    }
    Benchmark::end ();
    Benchmark::begin ("step 2b", false);
    {
        const long lx = 0;
        const long ly = 0;
        const long lz = 0;
        const long rx = m_size.x - 1;
        const long ry = m_size.y - 1;
        const long rz = m_size.z - 1;
        { // Cells in the middle of the simulated Volume
            for (parallel_offset = 0; parallel_offset < 2; parallel_offset++) {
                for (idx_x = lx + parallel_offset; idx_x < rx; idx_x += 2) {
                    for (idx_y = ly; idx_y < ry; idx_y++) {
                        for (idx_z = lz; idx_z < rz; idx_z++) {
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 1, idx_z + 1),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 1, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 1, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z + 1),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z + 1),
                                                             get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 1, idx_z + 1));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 0, idx_y + 1, idx_z + 1),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                            step_2b_calculate_between_cells (get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1),
                                                             get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                        }
                    }
                }
            }
        }
        { // Wraparound-interaction at the X-Border
            idx_x = rx;
            for (idx_y = ly; idx_y < ry; idx_y++) {
                for (idx_z = lz; idx_z < rz; idx_z++) {
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 1, idx_z + 1),
                                                            get_cell_at (idx_x, idx_y + 0, idx_z + 0),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 1, idx_z + 0),
                                                            get_cell_at (idx_x, idx_y + 0, idx_z + 0),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 1, idx_z + 0),
                                                            get_cell_at (idx_x, idx_y + 0, idx_z + 1),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z + 1),
                                                            get_cell_at (idx_x, idx_y + 0, idx_z + 0),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z + 0),
                                                            get_cell_at (idx_x, idx_y + 0, idx_z + 0),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z + 0),
                                                            get_cell_at (idx_x, idx_y + 0, idx_z + 1),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z + 1),
                                                            get_cell_at (idx_x, idx_y + 1, idx_z + 0),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z + 0),
                                                            get_cell_at (idx_x, idx_y + 1, idx_z + 0),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z + 0),
                                                            get_cell_at (idx_x, idx_y + 1, idx_z + 1),
                                                            m_options.m_bounds.x,
                                                            0,
                                                            0);
                    step_2b_calculate_between_cells (get_cell_at (idx_x, idx_y + 1, idx_z + 1),
                                                     get_cell_at (idx_x, idx_y + 0, idx_z + 0));
                    step_2b_calculate_between_cells (get_cell_at (idx_x, idx_y + 1, idx_z + 0),
                                                     get_cell_at (idx_x, idx_y + 0, idx_z + 0));
                    step_2b_calculate_between_cells (get_cell_at (idx_x, idx_y + 1, idx_z + 0),
                                                     get_cell_at (idx_x, idx_y + 0, idx_z + 1));
                    step_2b_calculate_between_cells (get_cell_at (idx_x, idx_y + 0, idx_z + 1),
                                                     get_cell_at (idx_x, idx_y + 0, idx_z + 0));
                }
            }
        }
        { // Wraparound-interaction at the Y-Border
            idx_y = ry;
            for (idx_x = lx; idx_x < rx; idx_x++) {
                for (idx_z = lz; idx_z < rz; idx_z++) {
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y, idx_z + 1),
                                                     get_cell_at (idx_x + 0, idx_y, idx_z + 0));
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y, idx_z + 0),
                                                     get_cell_at (idx_x + 0, idx_y, idx_z + 0));
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y, idx_z + 0),
                                                     get_cell_at (idx_x + 0, idx_y, idx_z + 1));
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 0, idx_y, idx_z + 1),
                                                     get_cell_at (idx_x + 0, idx_y, idx_z + 0));
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, 0, idx_z + 1),
                                                            get_cell_at (idx_x + 0, idx_y, idx_z + 0),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, 0, idx_z + 0),
                                                            get_cell_at (idx_x + 0, idx_y, idx_z + 0),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, 0, idx_z + 0),
                                                            get_cell_at (idx_x + 0, idx_y, idx_z + 1),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, idx_z + 1),
                                                            get_cell_at (idx_x + 0, 0, idx_z + 0),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, idx_z + 0),
                                                            get_cell_at (idx_x + 0, 0, idx_z + 0),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, idx_z + 0),
                                                            get_cell_at (idx_x + 0, 0, idx_z + 1),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, 0, idx_z + 1),
                                                            get_cell_at (idx_x + 0, idx_y, idx_z + 0),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, 0, idx_z + 0),
                                                            get_cell_at (idx_x + 0, idx_y, idx_z + 0),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, 0, idx_z + 0),
                                                            get_cell_at (idx_x + 0, idx_y, idx_z + 1),
                                                            0,
                                                            -m_options.m_bounds.y,
                                                            0);
                }
            }
        }
        { // Wraparound-interaction at the Z-Border
            idx_z = rz;
            for (idx_x = lx; idx_x < rx; idx_x++) {
                for (idx_y = ly; idx_y < ry; idx_y++) {
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 1, idx_z),
                                                     get_cell_at (idx_x + 0, idx_y + 0, idx_z));
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z),
                                                     get_cell_at (idx_x + 0, idx_y + 0, idx_z));
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y + 0, idx_z),
                                                     get_cell_at (idx_x + 0, idx_y + 1, idx_z));
                    step_2b_calculate_between_cells (get_cell_at (idx_x + 0, idx_y + 1, idx_z),
                                                     get_cell_at (idx_x + 0, idx_y + 0, idx_z));
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y + 1, 0),
                                                            get_cell_at (idx_x + 0, idx_y + 0, idx_z),
                                                            0,
                                                            0,
                                                            m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y + 1, idx_z),
                                                            get_cell_at (idx_x + 0, idx_y + 0, 0),
                                                            0,
                                                            0,
                                                            -m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y + 0, 0),
                                                            get_cell_at (idx_x + 0, idx_y + 0, idx_z),
                                                            0,
                                                            0,
                                                            m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y + 0, idx_z),
                                                            get_cell_at (idx_x + 0, idx_y + 0, 0),
                                                            0,
                                                            0,
                                                            -m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y + 0, 0),
                                                            get_cell_at (idx_x + 0, idx_y + 1, idx_z),
                                                            0,
                                                            0,
                                                            m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y + 0, idx_z),
                                                            get_cell_at (idx_x + 0, idx_y + 1, 0),
                                                            0,
                                                            0,
                                                            -m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, idx_y + 1, 0),
                                                            get_cell_at (idx_x + 0, idx_y + 0, idx_z),
                                                            0,
                                                            0,
                                                            m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, idx_y + 1, idx_z),
                                                            get_cell_at (idx_x + 0, idx_y + 0, 0),
                                                            0,
                                                            0,
                                                            -m_options.m_bounds.z);
                    step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, idx_y + 0, 0),
                                                            get_cell_at (idx_x + 0, idx_y + 0, idx_z),
                                                            0,
                                                            0,
                                                            m_options.m_bounds.z);
                }
            }
        }
        { // Wraparound-interaction at the YZ-Border
            idx_y = ry;
            idx_z = rz;
            for (idx_x = lx; idx_x < rx; idx_x++) {
                step_2b_calculate_between_cells (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                 get_cell_at (idx_x + 0, idx_y, idx_z));
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, 0, 0),
                                                        get_cell_at (idx_x + 0, idx_y, idx_z),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, 0, idx_z),
                                                        get_cell_at (idx_x + 0, idx_y, idx_z),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, 0, idx_z),
                                                        get_cell_at (idx_x + 0, idx_y, 0),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, 0),
                                                        get_cell_at (idx_x + 0, idx_y, idx_z),
                                                        0,
                                                        0,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                        get_cell_at (idx_x + 0, idx_y, 0),
                                                        0,
                                                        0,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, 0),
                                                        get_cell_at (idx_x + 0, 0, idx_z),
                                                        0,
                                                        -m_options.m_bounds.y,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                        get_cell_at (idx_x + 0, 0, idx_z),
                                                        0,
                                                        -m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 1, idx_y, idx_z),
                                                        get_cell_at (idx_x + 0, 0, 0),
                                                        0,
                                                        -m_options.m_bounds.y,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, 0, 0),
                                                        get_cell_at (idx_x + 0, idx_y, idx_z),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, 0, idx_z),
                                                        get_cell_at (idx_x + 0, idx_y, idx_z),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, 0, idx_z),
                                                        get_cell_at (idx_x + 0, idx_y, 0),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x + 0, idx_y, 0),
                                                        get_cell_at (idx_x + 0, idx_y, idx_z),
                                                        0,
                                                        0,
                                                        m_options.m_bounds.z);
            }
        }
        { // Wraparound-interaction at the XZ-Border
            idx_x = rx;
            idx_z = rz;
            for (idx_y = ly; idx_y < ry; idx_y++) {
                step_2b_calculate_between_cells (get_cell_at (idx_x, idx_y + 1, idx_z),
                                                 get_cell_at (idx_x, idx_y + 0, idx_z));
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 1, 0),
                                                        get_cell_at (idx_x, idx_y + 0, idx_z),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 1, idx_z),
                                                        get_cell_at (idx_x, idx_y + 0, idx_z),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 1, idx_z),
                                                        get_cell_at (idx_x, idx_y + 0, 0),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, 0),
                                                        get_cell_at (idx_x, idx_y + 0, idx_z),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z),
                                                        get_cell_at (idx_x, idx_y + 0, idx_z),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z),
                                                        get_cell_at (idx_x, idx_y + 0, 0),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, 0),
                                                        get_cell_at (idx_x, idx_y + 1, idx_z),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z),
                                                        get_cell_at (idx_x, idx_y + 1, idx_z),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y + 0, idx_z),
                                                        get_cell_at (idx_x, idx_y + 1, 0),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x, idx_y + 1, 0),
                                                        get_cell_at (idx_x, idx_y + 0, idx_z),
                                                        0,
                                                        0,
                                                        m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x, idx_y + 1, idx_z),
                                                        get_cell_at (idx_x, idx_y + 0, 0),
                                                        0,
                                                        0,
                                                        -m_options.m_bounds.z);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x, idx_y + 0, 0),
                                                        get_cell_at (idx_x, idx_y + 0, idx_z),
                                                        0,
                                                        0,
                                                        m_options.m_bounds.z);
            }
        }
        { // Wraparound-interaction at the XY-Border
            idx_x = rx;
            idx_y = ry;
            for (idx_z = lz; idx_z < rz; idx_z++) {
                step_2b_calculate_between_cells (get_cell_at (idx_x, idx_y, idx_z + 1),
                                                 get_cell_at (idx_x, idx_y, idx_z + 0));
                step_2b_calculate_between_cells_offset (get_cell_at (0, 0, idx_z + 1),
                                                        get_cell_at (idx_x, idx_y, idx_z + 0),
                                                        m_options.m_bounds.x,
                                                        m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, 0, idx_z + 0),
                                                        get_cell_at (idx_x, idx_y, idx_z + 0),
                                                        m_options.m_bounds.x,
                                                        m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, 0, idx_z + 0),
                                                        get_cell_at (idx_x, idx_y, idx_z + 1),
                                                        m_options.m_bounds.x,
                                                        m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z + 1),
                                                        get_cell_at (idx_x, idx_y, idx_z + 0),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z + 0),
                                                        get_cell_at (idx_x, idx_y, idx_z + 0),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z + 0),
                                                        get_cell_at (idx_x, idx_y, idx_z + 1),
                                                        m_options.m_bounds.x,
                                                        0,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z + 1),
                                                        get_cell_at (idx_x, 0, idx_z + 0),
                                                        m_options.m_bounds.x,
                                                        -m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z + 0),
                                                        get_cell_at (idx_x, 0, idx_z + 0),
                                                        m_options.m_bounds.x,
                                                        -m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z + 0),
                                                        get_cell_at (idx_x, 0, idx_z + 1),
                                                        m_options.m_bounds.x,
                                                        -m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x, 0, idx_z + 1),
                                                        get_cell_at (idx_x, idx_y, idx_z + 0),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x, 0, idx_z + 0),
                                                        get_cell_at (idx_x, idx_y, idx_z + 0),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        0);
                step_2b_calculate_between_cells_offset (get_cell_at (idx_x, 0, idx_z + 0),
                                                        get_cell_at (idx_x, idx_y, idx_z + 1),
                                                        0,
                                                        m_options.m_bounds.y,
                                                        0);
            }
        }
        { // Wraparound-interaction at the XYZ-Corner
            idx_x = rx;
            idx_y = ry;
            idx_z = rz;
            step_2b_calculate_between_cells_offset (get_cell_at (0, 0, 0),
                                                    get_cell_at (idx_x, idx_y, idx_z),
                                                    m_options.m_bounds.x,
                                                    m_options.m_bounds.y,
                                                    m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (0, 0, idx_z),
                                                    get_cell_at (idx_x, idx_y, idx_z),
                                                    m_options.m_bounds.x,
                                                    m_options.m_bounds.y,
                                                    0);
            step_2b_calculate_between_cells_offset (get_cell_at (0, 0, idx_z),
                                                    get_cell_at (idx_x, idx_y, 0),
                                                    m_options.m_bounds.x,
                                                    m_options.m_bounds.y,
                                                    -m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, 0),
                                                    get_cell_at (idx_x, idx_y, idx_z),
                                                    m_options.m_bounds.x,
                                                    0,
                                                    m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z),
                                                    get_cell_at (idx_x, idx_y, idx_z),
                                                    m_options.m_bounds.x,
                                                    0,
                                                    0);
            step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z),
                                                    get_cell_at (idx_x, idx_y, 0),
                                                    m_options.m_bounds.x,
                                                    0,
                                                    -m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, 0),
                                                    get_cell_at (idx_x, 0, idx_z),
                                                    m_options.m_bounds.x,
                                                    -m_options.m_bounds.y,
                                                    m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z),
                                                    get_cell_at (idx_x, 0, idx_z),
                                                    m_options.m_bounds.x,
                                                    -m_options.m_bounds.y,
                                                    0);
            step_2b_calculate_between_cells_offset (get_cell_at (0, idx_y, idx_z),
                                                    get_cell_at (idx_x, 0, 0),
                                                    m_options.m_bounds.x,
                                                    -m_options.m_bounds.y,
                                                    -m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (idx_x, 0, 0),
                                                    get_cell_at (idx_x, idx_y, idx_z),
                                                    0,
                                                    m_options.m_bounds.y,
                                                    m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (idx_x, 0, idx_z),
                                                    get_cell_at (idx_x, idx_y, idx_z),
                                                    0,
                                                    m_options.m_bounds.y,
                                                    0);
            step_2b_calculate_between_cells_offset (get_cell_at (idx_x, 0, idx_z),
                                                    get_cell_at (idx_x, idx_y, 0),
                                                    0,
                                                    m_options.m_bounds.y,
                                                    -m_options.m_bounds.z);
            step_2b_calculate_between_cells_offset (get_cell_at (idx_x, idx_y, 0),
                                                    get_cell_at (idx_x, idx_y, idx_z),
                                                    0,
                                                    0,
                                                    m_options.m_bounds.z);
        }
    }
    Benchmark::end ();
    if (m_iterations_until_rearange_particles < 1) {
        Benchmark::begin ("step 3", false);
        for (idx_x = 0; idx_x < m_size.x; idx_x++) {
            for (idx_y = 0; idx_y < m_size.y; idx_y++) {
                for (idx_z = 0; idx_z < m_size.z; idx_z++) {
                    ParticleCell& cell = get_cell_at (idx_x, idx_y, idx_z);
                    step_3_remove_wrong_particles_from_cell (cell);
                }
            }
        }
        Benchmark::end ();
        m_iterations_until_rearange_particles = m_options.m_max_iterations_between_datastructure_rebuild;
    }
    m_idx_b = !(m_idx_a = m_idx_b);
    return m_error_happened;
}
inline void DatastructureGrid::moveParticle (ParticleCell& p_cell_from, ParticleCell& p_cell_to, long p_index_from) {
    unsigned int j;
    p_cell_to.m_ids.push_back (p_cell_from.m_ids[p_index_from]);
    p_cell_from.m_ids.erase (p_cell_from.m_ids.begin () + p_index_from);
    for (j = 0; j <= 1; j++) {
        p_cell_to.m_positions_x[j].push_back (p_cell_from.m_positions_x[j][p_index_from]);
        p_cell_to.m_positions_y[j].push_back (p_cell_from.m_positions_y[j][p_index_from]);
        p_cell_to.m_positions_z[j].push_back (p_cell_from.m_positions_z[j][p_index_from]);
        p_cell_from.m_positions_x[j].erase (p_cell_from.m_positions_x[j].begin () + p_index_from);
        p_cell_from.m_positions_y[j].erase (p_cell_from.m_positions_y[j].begin () + p_index_from);
        p_cell_from.m_positions_z[j].erase (p_cell_from.m_positions_z[j].begin () + p_index_from);
    }
}
unsigned long DatastructureGrid::get_particle_count () {
    unsigned long particle_count = 0;
    for (ParticleCell cell : m_cells) {
        particle_count += cell.m_ids.size ();
    }
    return particle_count;
}
ParticleCell::ParticleCell (Vec3l p_idx, Vec3f p_size_per_cell) {
    m_idx       = p_idx;
    m_corner000 = Vec3f (m_idx - 1L) * p_size_per_cell;
    m_corner111 = Vec3f (m_idx) * p_size_per_cell;
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
