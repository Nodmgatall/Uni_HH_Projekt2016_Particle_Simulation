#include "DatastructureGrid.hpp"

DatastructureGrid::DatastructureGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name = "DatastructureGrid";
    unsigned int idx_x, idx_y, idx_z;
    long         max_usefull_size         = pow (m_options.m_particle_count, 1.0 / 3.0);
    m_iterations_until_rearange_particles = m_options.m_max_iterations_between_datastructure_rebuild;
    m_max_id                              = 0;
    // cut_off_radius*1.2 to allow particles to move before reconstruction of
    // cells is needed
    Vec3l tmp = m_options.m_bounds / (m_options.m_cut_off_radius * 1.2f);
    grid_size = Vec3l (ceil (tmp.x), ceil (tmp.y), ceil (tmp.z));
    grid_size = Vec3l::min (grid_size, max_usefull_size);
    // at least 3 cells required because of periodic boundary
    grid_size          = Vec3l::max (grid_size, Vec3l (3L));
    grid_size_per_cell = m_options.m_bounds / Vec3f (grid_size);
    m_options.m_cut_off_radius =
        MIN (grid_size_per_cell.x, MIN (grid_size_per_cell.y, grid_size_per_cell.z));
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
        std::cout << "ERROR :: cut-off-radius too small. Increasing from '"
                  << DEBUG_VAR (m_options.m_cut_off_radius) << "' to '1'!" << std::endl;
        m_options.m_cut_off_radius = 1;
    }
    std::cout << DEBUG_VAR (m_stucture_name) << std::endl;
    std::cout << DEBUG_VAR (m_options.m_cut_off_radius) << std::endl;
    std::cout << DEBUG_VAR (grid_size) << std::endl;
    std::cout << DEBUG_VAR (grid_size_per_cell) << std::endl;
    std::cout << DEBUG_VAR (m_options.m_bounds) << std::endl;
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
    return Vec3l ((long) (x / grid_size_per_cell.x) + 1,
                  (long) (y / grid_size_per_cell.y) + 1,
                  (long) (z / grid_size_per_cell.z) + 1);
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
    m_border.updatePosition (p_current_position.x,
                             p_current_position.y,
                             p_current_position.z,
                             old_position.x,
                             old_position.y,
                             old_position.z);
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

void DatastructureGrid::grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i,
                                                              ParticleGroup& p_cell_j,
                                                              data_type      offset_x,
                                                              data_type      offset_y,
                                                              data_type      offset_z) {
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
        Vec3l idx = grid_get_cell_index_for_particle (p_cell.m_positions_x[m_idx_a][i],
                                                      p_cell.m_positions_y[m_idx_a][i],
                                                      p_cell.m_positions_z[m_idx_a][i]);
        if (idx != p_cell.m_idx) {
            ParticleGroup& other_cell = grid_get_cell_at (idx.x, idx.y, idx.z);
            grid_moveParticle (p_cell, other_cell, i);
        }
    }
}
bool DatastructureGrid::grid_step_2 () {
    unsigned int idx_x, idx_y, idx_z;
    Benchmark::begin ("step 2b", false);
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
    { // Cells in the middle of the simulated Volume
        for (idx_x = lx; idx_x < rx; idx_x++) {
            for (idx_y = ly; idx_y < ry; idx_y++) {
                for (idx_z = lz; idx_z < rz; idx_z++) {
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, idx_z + 1),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 1),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 1),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 1));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 1),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, idx_z + 0),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1));
                    grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 1),
                                                          grid_get_cell_at (idx_x + 0, idx_y + 0, idx_z + 0));
                }
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the X-Border
        for (idx_y = ly; idx_y < ry; idx_y++) {
            for (idx_z = lz; idx_z < rz; idx_z++) {
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, idx_z + 1),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 0));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 0));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 1));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 0, idx_z + 1),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 0));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, idx_z + 1),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 0),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 0),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 1, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 1),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 1),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 0),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 0),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 0, idx_z + 1),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 1),
                                                      grid_get_cell_at (rx, idx_y + 1, idx_z + 0),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 1, idx_z + 0),
                                                      ox,
                                                      0,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, idx_y + 0, idx_z + 0),
                                                      grid_get_cell_at (rx, idx_y + 1, idx_z + 1),
                                                      ox,
                                                      0,
                                                      0);
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the Y-Border
        for (idx_x = lx; idx_x < rx; idx_x++) {
            for (idx_z = lz; idx_z < rz; idx_z++) {
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 1),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 0));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 0));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 1));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ry, idx_z + 1),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 0));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, idx_z + 1),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 0),
                                                      0,
                                                      oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 0),
                                                      0,
                                                      oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ly, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 1),
                                                      0,
                                                      oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 1),
                                                      grid_get_cell_at (idx_x + 0, ly, idx_z + 0),
                                                      0,
                                                      -oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ly, idx_z + 0),
                                                      0,
                                                      -oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ly, idx_z + 1),
                                                      0,
                                                      -oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, idx_z + 1),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 0),
                                                      0,
                                                      oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 0),
                                                      0,
                                                      oy,
                                                      0);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, ly, idx_z + 0),
                                                      grid_get_cell_at (idx_x + 0, ry, idx_z + 1),
                                                      0,
                                                      oy,
                                                      0);
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the Z-Border
        for (idx_x = lx; idx_x < rx; idx_x++) {
            for (idx_y = ly; idx_y < ry; idx_y++) {
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, rz));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, rz));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 1, rz));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, rz));
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, lz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, rz),
                                                      0,
                                                      0,
                                                      oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 1, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, lz),
                                                      0,
                                                      0,
                                                      -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, lz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, rz),
                                                      0,
                                                      0,
                                                      oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, lz),
                                                      0,
                                                      0,
                                                      -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, lz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 1, rz),
                                                      0,
                                                      0,
                                                      oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, idx_y + 0, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 1, lz),
                                                      0,
                                                      0,
                                                      -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, lz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, rz),
                                                      0,
                                                      0,
                                                      oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 1, rz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, lz),
                                                      0,
                                                      0,
                                                      -oz);
                grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 0, idx_y + 0, lz),
                                                      grid_get_cell_at (idx_x + 0, idx_y + 0, rz),
                                                      0,
                                                      0,
                                                      oz);
            }
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the YZ-Border
        for (idx_x = lx; idx_x < rx; idx_x++) {
            grid_step_2b_calculate_between_cells (grid_get_cell_at (idx_x + 1, ry, rz),
                                                  grid_get_cell_at (idx_x + 0, ry, rz));
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ly, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ly, rz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ly, rz), grid_get_cell_at (idx_x + 0, ry, lz), 0, oy, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ry, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, 0, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ry, rz), grid_get_cell_at (idx_x + 0, ry, lz), 0, 0, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ry, lz), grid_get_cell_at (idx_x + 0, ly, rz), 0, -oy, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ry, rz), grid_get_cell_at (idx_x + 0, ly, rz), 0, -oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 1, ry, rz), grid_get_cell_at (idx_x + 0, ly, lz), 0, -oy, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 0, ly, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 0, ly, rz), grid_get_cell_at (idx_x + 0, ry, rz), 0, oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 0, ly, rz), grid_get_cell_at (idx_x + 0, ry, lz), 0, oy, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (idx_x + 0, ry, lz), grid_get_cell_at (idx_x + 0, ry, rz), 0, 0, oz);
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the XZ-Border
        for (idx_y = ly; idx_y < ry; idx_y++) {
            grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, idx_y + 1, rz),
                                                  grid_get_cell_at (rx, idx_y + 0, rz));
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 1, lz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 1, rz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 1, rz), grid_get_cell_at (rx, idx_y + 0, lz), ox, 0, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 0, lz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 0, rz), ox, 0, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 0, lz), ox, 0, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 0, lz), grid_get_cell_at (rx, idx_y + 1, rz), ox, 0, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 1, rz), ox, 0, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, idx_y + 0, rz), grid_get_cell_at (rx, idx_y + 1, lz), ox, 0, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (rx, idx_y + 1, lz), grid_get_cell_at (rx, idx_y + 0, rz), 0, 0, oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (rx, idx_y + 1, rz), grid_get_cell_at (rx, idx_y + 0, lz), 0, 0, -oz);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (rx, idx_y + 0, lz), grid_get_cell_at (rx, idx_y + 0, rz), 0, 0, oz);
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the XY-Border
        for (idx_z = lz; idx_z < rz; idx_z++) {
            grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ry, idx_z + 1),
                                                  grid_get_cell_at (rx, ry, idx_z + 0));
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ly, idx_z + 1), grid_get_cell_at (rx, ry, idx_z + 0), ox, oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 0), ox, oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 1), ox, oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ry, idx_z + 1), grid_get_cell_at (rx, ry, idx_z + 0), ox, 0, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 0), ox, 0, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 1), ox, 0, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ry, idx_z + 1), grid_get_cell_at (rx, ly, idx_z + 0), ox, -oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ly, idx_z + 0), ox, -oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (lx, ry, idx_z + 0), grid_get_cell_at (rx, ly, idx_z + 1), ox, -oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (rx, ly, idx_z + 1), grid_get_cell_at (rx, ry, idx_z + 0), 0, oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (rx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 0), 0, oy, 0);
            grid_step_2b_calculate_between_cells (
                grid_get_cell_at (rx, ly, idx_z + 0), grid_get_cell_at (rx, ry, idx_z + 1), 0, oy, 0);
        }
    }
    if (m_error_happened)
        return m_error_happened;
    { // Wraparound-interaction at the XYZ-Corner
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, lz), grid_get_cell_at (rx, ry, rz), ox, oy, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, rz), grid_get_cell_at (rx, ry, rz), ox, oy, 0);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ly, rz), grid_get_cell_at (rx, ry, lz), ox, oy, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, lz), grid_get_cell_at (rx, ry, rz), ox, 0, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ry, rz), ox, 0, 0);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ry, lz), ox, 0, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, lz), grid_get_cell_at (rx, ly, rz), ox, -oy, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ly, rz), ox, -oy, 0);
        grid_step_2b_calculate_between_cells (
            grid_get_cell_at (lx, ry, rz), grid_get_cell_at (rx, ly, lz), ox, -oy, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, lz), grid_get_cell_at (rx, ry, rz), 0, oy, oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, rz), grid_get_cell_at (rx, ry, rz), 0, oy, 0);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ly, rz), grid_get_cell_at (rx, ry, lz), 0, oy, -oz);
        grid_step_2b_calculate_between_cells (grid_get_cell_at (rx, ry, lz), grid_get_cell_at (rx, ry, rz), 0, 0, oz);
    }
    Benchmark::end ();
    return false;
}

bool DatastructureGrid::run_simulation_iteration (unsigned long p_iteration_number) {
    m_error_happened = false;
    (void) p_iteration_number;
    std::cout << DEBUG_VAR (p_iteration_number) << std::endl;
    m_iterations_until_rearange_particles--;
    unsigned int idx_x, idx_y, idx_z;
    {
        Benchmark::begin ("step 1+2a", false);
        for (idx_x = 0; idx_x < grid_size.x; idx_x++) {
            for (idx_y = 0; idx_y < grid_size.y; idx_y++) {
                for (idx_z = 0; idx_z < grid_size.z; idx_z++) {
                    ParticleGroup& cell = grid_get_cell_at (idx_x, idx_y, idx_z);
                    step_1_prepare_cell (cell);
                    grid_step_2a_calculate_inside_cell (cell);
                }
            }
        }
        Benchmark::end ();
    }
    if (m_error_happened)
        return m_error_happened;
    grid_step_2 ();
    if (m_error_happened)
        return m_error_happened;

    if (m_error_happened)
        return m_error_happened;
    {
        if (m_iterations_until_rearange_particles < 1) {
            Benchmark::begin ("step 3", false);
            for (idx_x = 0; idx_x < grid_size.x; idx_x++) {
                for (idx_y = 0; idx_y < grid_size.y; idx_y++) {
                    for (idx_z = 0; idx_z < grid_size.z; idx_z++) {
                        ParticleGroup& cell = grid_get_cell_at (idx_x, idx_y, idx_z);
                        grid_step_3_remove_wrong_particles_from_cell (cell);
                    }
                }
            }
            Benchmark::end ();
            if (m_error_happened)
                return m_error_happened;
            m_iterations_until_rearange_particles = m_options.m_max_iterations_between_datastructure_rebuild;
        }
    }
    m_idx_b = !(m_idx_a = m_idx_b);
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
