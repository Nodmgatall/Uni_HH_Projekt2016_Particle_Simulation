#include "DatastructureGrid.hpp"
DatastructureGrid::DatastructureGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name = "DatastructureGrid";
    unsigned int idx_x, idx_y, idx_z;
    long         max_usefull_size = pow (m_options.m_particle_count, 1.0 / 3.0);
    m_max_id                      = 0;
    Vec3f tmp                     = m_options.m_bounds / (m_options.m_cut_off_radius * m_cut_off_factor);
    grid_size                     = Vec3l (ceil (tmp.x), ceil (tmp.y), ceil (tmp.z));
    grid_size                     = Vec3l::min (grid_size, max_usefull_size);

    // at least 3 cells required because of periodic boundary
    grid_size = Vec3l::max (grid_size, Vec3l (3L));
    { // force odd count off cells in each direction
        if (grid_size.x % 2 == 0)
            grid_size.x--;
        if (grid_size.y % 2 == 0)
            grid_size.y--;
        if (grid_size.z % 2 == 0)
            grid_size.z--;
    }
    grid_size_per_cell         = m_options.m_bounds / Vec3f (grid_size);
    m_options.m_cut_off_radius = MIN (grid_size_per_cell.x, MIN (grid_size_per_cell.y, grid_size_per_cell.z));
    grid_size += 2; // 2 border cells (each border needs 1)
    m_particle_groups.reserve (grid_size.x * grid_size.y * grid_size.z);
    for (idx_x = 0; idx_x < grid_size.x; idx_x++) {
        for (idx_y = 0; idx_y < grid_size.y; idx_y++) {
            for (idx_z = 0; idx_z < grid_size.z; idx_z++) {
                m_particle_groups.push_back (ParticleGroup (Vec3l (idx_x, idx_y, idx_z), grid_size_per_cell));
            }
        }
    }
    if (m_options.m_cut_off_radius < 1) {
        m_standard_stream << "ERROR :: cut-off-radius too small. Increasing from '" << DEBUG_VAR (m_options.m_cut_off_radius) << "' to '1'!" << std::endl;
        m_options.m_cut_off_radius = 1;
    }
    m_standard_stream << DEBUG_VAR (m_stucture_name) << std::endl;
    m_standard_stream << DEBUG_VAR (grid_size) << std::endl;
    m_standard_stream << DEBUG_VAR (grid_size_per_cell) << std::endl;
    m_standard_stream << DEBUG_VAR (m_cut_off_factor) << std::endl;
    m_standard_stream << DEBUG_VAR (m_speed_factor) << std::endl;
    m_standard_stream << DEBUG_VAR (m_options.m_bounds) << std::endl;
    m_standard_stream << DEBUG_VAR (m_options.m_timestep) << std::endl;
    m_standard_stream << DEBUG_VAR (m_options.m_cut_off_radius) << std::endl;
}
DatastructureGrid::~DatastructureGrid () {
}
unsigned long DatastructureGrid::grid_get_cell_index (long x, long y, long z) {
    return x + grid_size.x * (y + grid_size.y * z);
}
ParticleGroup& DatastructureGrid::grid_get_cell_at (long x, long y, long z) {
    return m_particle_groups[grid_get_cell_index (x, y, z)];
}
ParticleGroup& DatastructureGrid::grid_get_cell_for_particle (data_type x, data_type y, data_type z) {
    Vec3l idx = grid_get_cell_index_for_particle (x, y, z);
    return m_particle_groups[grid_get_cell_index (idx.x, idx.y, idx.z)];
}
Vec3l DatastructureGrid::grid_get_cell_index_for_particle (data_type x, data_type y, data_type z) {
    return Vec3l ((long) (x / grid_size_per_cell.x) + 1, (long) (y / grid_size_per_cell.y) + 1, (long) (z / grid_size_per_cell.z) + 1);
}
ParticleGroup& DatastructureGrid::grid_get_cell_for_particle (Vec3f m_position) {
    return grid_get_cell_for_particle (m_position.x, m_position.y, m_position.z);
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
    m_border.updatePosition (p_current_position.x, p_current_position.y, p_current_position.z, old_position.x, old_position.y, old_position.z);
    ParticleGroup& cell = grid_get_cell_for_particle (p_current_position);
    cell.add_particle (p_current_position, old_position, m_idx_a, id);
}
void DatastructureGrid::grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell) {
    unsigned long      i;
    const unsigned int max   = p_cell.m_ids.size ();
    const unsigned int max_1 = max - 1;
    if (max > 1) {
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
void DatastructureGrid::grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j) {
    unsigned int       i;
    const unsigned int max = p_cell_i.m_ids.size ();
    if (p_cell_j.m_ids.size () > 0) {
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
}
void DatastructureGrid::grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, data_type offset_x, data_type offset_y, data_type offset_z) {
    unsigned int       i;
    const unsigned int max = p_cell_i.m_ids.size ();
    if (p_cell_j.m_ids.size () > 0) {
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
}
void DatastructureGrid::grid_step_3_remove_wrong_particles_from_cell (ParticleGroup& p_cell) {
    step_3_fit_into_borders (p_cell);
    int i;
    for (i = p_cell.m_ids.size () - 1; i >= 0; i--) {
        Vec3l idx = grid_get_cell_index_for_particle (p_cell.m_positions_x[m_idx_a][i], p_cell.m_positions_y[m_idx_a][i], p_cell.m_positions_z[m_idx_a][i]);
        if (idx != p_cell.m_idx) {
            ParticleGroup& other_cell = grid_get_cell_at (idx.x, idx.y, idx.z);
            grid_moveParticle (p_cell, other_cell, i);
        }
    }
}
bool DatastructureGrid::grid_step_2 () {
    unsigned int    idx;
    unsigned int    idx_x, idx_y, idx_z;
    unsigned int    idx_x_2, idx_y_2, idx_z_2;
    unsigned int    parallel_offset_x, parallel_offset_y, parallel_offset_z;
    const long      border_cells_ignored_count = 1; // 0 or 1
    const long      lx                         = border_cells_ignored_count;
    const long      ly                         = border_cells_ignored_count;
    const long      lz                         = border_cells_ignored_count;
    const long      rx                         = grid_size.x - 1 - border_cells_ignored_count;
    const long      ry                         = grid_size.y - 1 - border_cells_ignored_count;
    const long      rz                         = grid_size.z - 1 - border_cells_ignored_count;
    const data_type ox                         = m_options.m_bounds.x;
    const data_type oy                         = m_options.m_bounds.y;
    const data_type oz                         = m_options.m_bounds.z;
    const long      ux                         = (rx - lx) / 2;
    const long      uy                         = (ry - ly) / 2;
    const long      uz                         = (rz - lz) / 2;
    const long      uyz                        = uy * uz;
    const long      uxyz                       = ux * uyz;
    m_verbose_stream << "l:" << lx << "," << ly << "," << lz << std::endl;
    m_verbose_stream << "r:" << rx << "," << ry << "," << rz << std::endl;
    m_verbose_stream << "u:" << ux << "," << uy << "," << uz << std::endl;
    // omp_set_num_threads (1);
    { // Cells in the middle of the simulated Volume
        m_verbose_stream << "grid_step_2::1" << std::endl;
        for (parallel_offset_x = 0; parallel_offset_x < 2; parallel_offset_x++) {
            for (parallel_offset_y = 0; parallel_offset_y < 2; parallel_offset_y++) {
                for (parallel_offset_z = 0; parallel_offset_z < 2; parallel_offset_z++) {
#pragma omp parallel for private(idx, idx_x, idx_y, idx_z, idx_x_2, idx_y_2, idx_z_2)
                    for (idx = 0; idx < uxyz; idx++) {
                        idx_z_2 = idx % uz;
                        idx_y_2 = (idx / uz) % uy;
                        idx_x_2 = ((idx / uz) / uy);
                        idx_x   = lx + idx_x_2 * 2 + parallel_offset_x;
                        idx_y   = ly + idx_y_2 * 2 + parallel_offset_y;
                        idx_z   = lz + idx_z_2 * 2 + parallel_offset_z;
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, idx_z + 1), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 1), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 1), grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 1));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 1), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1), grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                    }
                }
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the X-Border
        m_verbose_stream << "grid_step_2::2" << std::endl;
        for (parallel_offset_y = 0; parallel_offset_y < 2; parallel_offset_y++) {
            for (parallel_offset_z = 0; parallel_offset_z < 2; parallel_offset_z++) {
#pragma omp parallel for private(idx_y, idx_z)
                for (idx_y = parallel_offset_y + ly; idx_y < ry; idx_y += 2) {
                    for (idx_z = parallel_offset_z + lz; idx_z < rz; idx_z += 2) {
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, idx_z + 1), grid_get_cell_at (rx, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, idx_z + 0), grid_get_cell_at (rx, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, idx_z + 0), grid_get_cell_at (rx, idx_y + 0, idx_z + 1));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 0, idx_z + 1), grid_get_cell_at (rx, idx_y + 0, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, idx_z + 1), grid_get_cell_at (rx, idx_y + 0, idx_z + 0), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, idx_z + 0), grid_get_cell_at (rx, idx_y + 0, idx_z + 0), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, idx_z + 0), grid_get_cell_at (rx, idx_y + 0, idx_z + 1), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 1), grid_get_cell_at (rx, idx_y + 0, idx_z + 0), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0), grid_get_cell_at (rx, idx_y + 0, idx_z + 0), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0), grid_get_cell_at (rx, idx_y + 0, idx_z + 1), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 1), grid_get_cell_at (rx, idx_y + 1, idx_z + 0), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0), grid_get_cell_at (rx, idx_y + 1, idx_z + 0), ox, 0, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0), grid_get_cell_at (rx, idx_y + 1, idx_z + 1), ox, 0, 0);
                    }
                }
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the Y-Border
        m_verbose_stream << "grid_step_2::3" << std::endl;
        for (parallel_offset_x = 0; parallel_offset_x < 2; parallel_offset_x++) {
            for (parallel_offset_z = 0; parallel_offset_z < 2; parallel_offset_z++) {
#pragma omp parallel for private(idx_x, idx_z)
                for (idx_x = parallel_offset_x + lx; idx_x < rx; idx_x += 2) {
                    for (idx_z = parallel_offset_z + lz; idx_z < rz; idx_z += 2) {
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 1), grid_get_cell_at (idx_x + 0, ry, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0), grid_get_cell_at (idx_x + 0, ry, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0), grid_get_cell_at (idx_x + 0, ry, idx_z + 1));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ry, idx_z + 1), grid_get_cell_at (idx_x + 0, ry, idx_z + 0));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, idx_z + 1), grid_get_cell_at (idx_x + 0, ry, idx_z + 0), 0, oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, idx_z + 0), grid_get_cell_at (idx_x + 0, ry, idx_z + 0), 0, oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, idx_z + 0), grid_get_cell_at (idx_x + 0, ry, idx_z + 1), 0, oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 1), grid_get_cell_at (idx_x + 0, ly, idx_z + 0), 0, -oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0), grid_get_cell_at (idx_x + 0, ly, idx_z + 0), 0, -oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0), grid_get_cell_at (idx_x + 0, ly, idx_z + 1), 0, -oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, idx_z + 1), grid_get_cell_at (idx_x + 0, ry, idx_z + 0), 0, oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, idx_z + 0), grid_get_cell_at (idx_x + 0, ry, idx_z + 0), 0, oy, 0);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, idx_z + 0), grid_get_cell_at (idx_x + 0, ry, idx_z + 1), 0, oy, 0);
                    }
                }
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the Z-Border
        m_verbose_stream << "grid_step_2::4" << std::endl;
        for (parallel_offset_x = 0; parallel_offset_x < 2; parallel_offset_x++) {
            for (parallel_offset_y = 0; parallel_offset_y < 2; parallel_offset_y++) {
#pragma omp parallel for private(idx_x, idx_y)
                for (idx_x = parallel_offset_x + lx; idx_x < rx; idx_x += 2) {
                    for (idx_y = parallel_offset_y + ly; idx_y < ry; idx_y += 2) {
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, rz), grid_get_cell_at (idx_x + 0, idx_y + 0, rz));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz), grid_get_cell_at (idx_x + 0, idx_y + 0, rz));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz), grid_get_cell_at (idx_x + 0, idx_y + 1, rz));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, rz), grid_get_cell_at (idx_x + 0, idx_y + 0, rz));
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, lz), grid_get_cell_at (idx_x + 0, idx_y + 0, rz), 0, 0, oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, rz), grid_get_cell_at (idx_x + 0, idx_y + 0, lz), 0, 0, -oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, lz), grid_get_cell_at (idx_x + 0, idx_y + 0, rz), 0, 0, oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz), grid_get_cell_at (idx_x + 0, idx_y + 0, lz), 0, 0, -oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, lz), grid_get_cell_at (idx_x + 0, idx_y + 1, rz), 0, 0, oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz), grid_get_cell_at (idx_x + 0, idx_y + 1, lz), 0, 0, -oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, lz), grid_get_cell_at (idx_x + 0, idx_y + 0, rz), 0, 0, oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, rz), grid_get_cell_at (idx_x + 0, idx_y + 0, lz), 0, 0, -oz);
                        grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 0, lz), grid_get_cell_at (idx_x + 0, idx_y + 0, rz), 0, 0, oz);
                    }
                }
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the YZ-Border
        m_verbose_stream << "grid_step_2::5" << std::endl;
        for (parallel_offset_x = 0; parallel_offset_x < 2; parallel_offset_x++) {
#pragma omp parallel for private(idx_x)
            for (idx_x = parallel_offset_x + lx; idx_x < rx; idx_x += 2) {
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, rz), grid_get_cell_at (idx_x + 0, ry, rz));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, rz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, rz), grid_get_cell_at (idx_x + 0, ry, lz), 0, oy, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, 0, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, rz), grid_get_cell_at (idx_x + 0, ry, lz), 0, 0, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, lz), grid_get_cell_at (idx_x + 0, ly, rz), 0, -oy, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, rz), grid_get_cell_at (idx_x + 0, ly, rz), 0, -oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, rz), grid_get_cell_at (idx_x + 0, ly, lz), 0, -oy, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, rz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, rz), grid_get_cell_at (idx_x + 0, ry, lz), 0, oy, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ry, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, 0, oz);
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the XZ-Border
        m_verbose_stream << "grid_step_2::6" << std::endl;
        for (parallel_offset_y = 0; parallel_offset_y < 2; parallel_offset_y++) {
#pragma omp parallel for private(idx_y)
            for (idx_y = parallel_offset_y + ly; idx_y < ry; idx_y += 2) {
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, rz), grid_get_cell_at (rx, idx_y + 0, rz));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, lz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, rz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, rz), grid_get_cell_at (rx, idx_y + 0, lz), ox, 0, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, lz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 0, lz), ox, 0, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, lz), grid_get_cell_at (rx, idx_y + 1, rz), ox, 0, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 1, rz), ox, 0, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 1, lz), ox, 0, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, lz), grid_get_cell_at (rx, idx_y + 0, rz), 0, 0, oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, rz), grid_get_cell_at (rx, idx_y + 0, lz), 0, 0, -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 0, lz), grid_get_cell_at (rx, idx_y + 0, rz), 0, 0, oz);
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the XY-Border
        m_verbose_stream << "grid_step_2::7" << std::endl;
        for (parallel_offset_z = 0; parallel_offset_z < 2; parallel_offset_z++) {
#pragma omp parallel for private(idx_z)
            for (idx_z = parallel_offset_z + lz; idx_z < rz; idx_z += 2) {
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ry, idx_z + 1), grid_get_cell_at (rx, ry, idx_z + 0));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, idx_z + 1), grid_get_cell_at (rx, ry, idx_z + 0), ox, oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 0), ox, oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 1), ox, oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, idx_z + 1), grid_get_cell_at (rx, ry, idx_z + 0), ox, 0, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 0), ox, 0, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 1), ox, 0, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, idx_z + 1), grid_get_cell_at (rx, ly, idx_z + 0), ox, -oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ly, idx_z + 0), ox, -oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ly, idx_z + 1), ox, -oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, idx_z + 1), grid_get_cell_at (rx, ry, idx_z + 0), 0, oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 0), 0, oy, 0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 1), 0, oy, 0);
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the XYZ-Corner
        m_verbose_stream << "grid_step_2::8" << std::endl;
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, lz), grid_get_cell_at (rx, ry, rz), ox, oy, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, rz), grid_get_cell_at (rx, ry, rz), ox, oy, 0);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, rz), grid_get_cell_at (rx, ry, lz), ox, oy, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, lz), grid_get_cell_at (rx, ry, rz), ox, 0, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ry, rz), ox, 0, 0);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ry, lz), ox, 0, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, lz), grid_get_cell_at (rx, ly, rz), ox, -oy, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ly, rz), ox, -oy, 0);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ly, lz), ox, -oy, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, lz), grid_get_cell_at (rx, ry, rz), 0, oy, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, rz), grid_get_cell_at (rx, ry, rz), 0, oy, 0);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, rz), grid_get_cell_at (rx, ry, lz), 0, oy, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ry, lz), grid_get_cell_at (rx, ry, rz), 0, 0, oz);
    }
    return false;
}
bool DatastructureGrid::run_simulation_iteration (unsigned long p_iteration_number) {
    unsigned int i, j;
    m_error_happened = false;
    (void) p_iteration_number;
    m_standard_stream << DEBUG_VAR (p_iteration_number) << std::endl;
    m_iterations_until_rearange_particles--;
    unsigned int idx_x, idx_y, idx_z;
    {
        m_verbose_stream << "grid_step_1" << std::endl;
#pragma omp parallel for private(idx_x, idx_y, idx_z)
        for (idx_x = 0; idx_x < grid_size.x; idx_x++) {
            for (idx_y = 0; idx_y < grid_size.y; idx_y++) {
                for (idx_z = 0; idx_z < grid_size.z; idx_z++) {
                    ParticleGroup& cell = grid_get_cell_at (idx_x, idx_y, idx_z);
                    step_1_prepare_cell (cell);
                    grid_step_2a_calculate_inside_cell (cell);
                }
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    m_verbose_stream << "grid_step_2" << std::endl;
    grid_step_2 ();
    if (m_error_happened)
        return m_error_happened;
    if (m_error_happened)
        return m_error_happened;
    {
        if (m_iterations_until_rearange_particles == 1) {
#ifdef CALCULATE_STATISTICS
            g_statistics.m_total_datastructure_rebuild_count++;
#endif
            // attention for mixed grid-list
            m_verbose_stream << "grid_step_3" << std::endl;
            // the following loops cannot be parallelized because removed particles can jump to any other cell -> concurrent write in random cells
            for (idx_x = 0; idx_x < grid_size.x; idx_x++) {
                for (idx_y = 0; idx_y < grid_size.y; idx_y++) {
                    for (idx_z = 0; idx_z < grid_size.z; idx_z++) {
                        ParticleGroup& cell = grid_get_cell_at (idx_x, idx_y, idx_z);
                        grid_step_3_remove_wrong_particles_from_cell (cell);
                    }
                }
            }
            if (m_error_happened)
                return m_error_happened;
        } else if (m_iterations_until_rearange_particles < 1) {
            calculate_next_datastructure_rebuild ();
        }
    }
    m_idx_b = !(m_idx_a = m_idx_b);
#ifdef CALCULATE_ENERGY_CONSERVATION
    g_sum_energy = 0;
    for (i = 0; i < m_particle_groups.size (); i++) {
        ParticleGroup& group = m_particle_groups[i];
        for (j = 0; j < group.m_ids.size (); j++) {
            data_type m = 1;
            Vec3f     v = Vec3f (group.m_positions_x[m_idx_b][j] - group.m_positions_x[m_idx_a][j],
                             group.m_positions_y[m_idx_b][j] - group.m_positions_y[m_idx_a][j],
                             group.m_positions_z[m_idx_b][j] - group.m_positions_z[m_idx_a][j]);
            g_sum_energy += 0.5 * m * v.length () * v.length ();
        }
    }
    m_verbose_stream << DEBUG_VAR (g_sum_energy) << " Joule" << std::endl;
    g_sum_energy_valid = true;
#endif
    return m_error_happened;
}
inline void DatastructureGrid::grid_moveParticle (ParticleGroup& p_cell_from, ParticleGroup& p_cell_to, long p_index_from) {
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
void DatastructureGrid::add_particle (Vec3f p_position) {
    add_particle (p_position, Vec3f (0));
}
