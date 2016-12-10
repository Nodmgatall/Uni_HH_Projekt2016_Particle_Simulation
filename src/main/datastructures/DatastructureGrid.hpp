#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../Definitions.hpp"
#include "../Vec3.hpp"
#include "DatastructureBase.hpp"

struct ParticleCell {
    std::vector<data_type>     m_positions_x[2];
    std::vector<data_type>     m_positions_y[2];
    std::vector<data_type>     m_positions_z[2];
    std::vector<unsigned long> m_ids;
    Vec3f                      m_corner000, m_corner111;
    Vec3l                      m_idx; // refer to ParticlesGrid::m_cells
    ParticleCell (Vec3l p_idx, Vec3l p_size, Vec3f& p_bounds);
    void add_particle (Vec3f p_current_position, Vec3f p_old_position, int p_current_index, int p_id);
};

class DatastructureGrid : public DatastructureBase {
  protected:
    /**
     * the index for the "next" inserted particle
     */
    unsigned long m_max_id;
    /**
     * the cells in which the particles are stored
     */
    std::vector<ParticleCell> m_cells;
    /**
     * the count of cells in 3 dimensions
     * refer to m_cells
     */
    Vec3l m_size;
    /**
     * the coordinate space captured by each cell
     */
    Vec3f m_size_per_cell;
    /**
     * the number of iterations until next test that all particles stay within the given bounds
     */
    int m_iterations_until_rearange_particles;
    /**
     * the current position of particles is stored in the array with this index
     * m_idx_a != m_idx_b
     */
    unsigned int m_idx_a;
    /**
     * the last/next position of particles is stored in the array with this index
     * m_idx_a != m_idx_b
     */
    unsigned int  m_idx_b;
    unsigned long get_cell_index (long x, long y, long z);
    ParticleCell& get_cell_at (long x, long y, long z);
    ParticleCell& get_cell_for_particle (data_type x, data_type y, data_type z);
    ParticleCell& get_cell_for_particle (Vec3f m_position);
    void moveParticle (ParticleCell& p_cell_from, ParticleCell& p_cell_to, long p_index_from);
    void step_1_prepare_cell (ParticleCell& p_cell);
    void step_2a_calculate_inside_cell (ParticleCell& p_cell);
    void step_2b_calculate_between_neigbours (unsigned int& p_x, unsigned int& p_y, unsigned int& p_z);
    void step_2b_calculate_between_cells (ParticleCell& p_cell_i, ParticleCell& p_cell_j);
    void step_3_remove_wrong_particles_from_cell (ParticleCell& p_cell);

  public:
    DatastructureGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    ~DatastructureGrid ();
    void serialize ();
    void run_simulation_iteration (unsigned long p_iteration_number = 0);
    void add_particle (Vec3f p_current_position);
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity);
    unsigned long get_particle_count ();
};
#endif
