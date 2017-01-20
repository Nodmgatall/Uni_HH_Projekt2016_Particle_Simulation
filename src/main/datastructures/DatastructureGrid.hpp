#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "DatastructureBase.hpp"
#include "Definitions.hpp"
#include "Vec3.hpp"

struct ParticleCell {
    std::vector<data_type>     m_positions_x[2];
    std::vector<data_type>     m_positions_y[2];
    std::vector<data_type>     m_positions_z[2];
    std::vector<unsigned long> m_ids;
    Vec3f                      m_corner000, m_corner111;
    Vec3l                      m_idx;
    ParticleCell (Vec3l p_idx, Vec3f p_size_per_cell);
    /**
     * adds an particle to this cell
     * @param p_current_position the current position of the particle to add
     * @param p_old_position the position which the particle had the last timestep
     * @param p_current_index in which array should the current value be stored
     * @param p_id the id for the added particle
     */
    void add_particle (Vec3f p_current_position, Vec3f p_old_position, int p_current_index, int p_id);
    friend std::ostream& operator<< (std::ostream& stream, const ParticleCell& cell) {
        stream << DEBUG_VAR (cell.m_corner000) << std::endl;
        stream << DEBUG_VAR (cell.m_corner111) << std::endl;
        stream << DEBUG_VAR (cell.m_idx) << std::endl;
        stream << DEBUG_VAR (cell.m_ids) << std::endl;
        stream << DEBUG_VAR (cell.m_positions_x) << std::endl;
        stream << DEBUG_VAR (cell.m_positions_y) << std::endl;
        stream << DEBUG_VAR (cell.m_positions_z) << std::endl;

        return stream;
    }
};

class DatastructureGrid : public DatastructureBase {
  protected:
    bool m_error_happened;
    /**
     * the index for the "next" inserted particle
     */
    long m_max_id;
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
    unsigned int m_idx_b;
    /**
     * return the combined index for the cell at the given index
     * @param x index
     * @param y index
     * @param z index
     */
    unsigned long get_cell_index (long x, long y, long z);
    /**
     * returns the cell at the given index
     * @param x index
     * @param y index
     * @param z index
     * @return the cell
     */
    ParticleCell& get_cell_at (long x, long y, long z);
    /**
     * return the cell for the given coordinate
     * @param x coordinate
     * @param y coordinate
     * @param z coordinate
     * @return the cell
     */
    ParticleCell& get_cell_for_particle (data_type x, data_type y, data_type z);
    Vec3l get_cell_index_for_particle (data_type x, data_type y, data_type z);
    /**
     * return the cell for the given position
     * @param m_position the position
     * @return the cell
     */
    ParticleCell& get_cell_for_particle (Vec3f m_position);
    /**
     * moves an particle from one cell to another
     * @param p_cell_from
     * @param p_cell_to
     * @param p_index_from
     */
    void moveParticle (ParticleCell& p_cell_from, ParticleCell& p_cell_to, long p_index_from);
    /**
     * first step in each iteration. Calculates the new particle position based on
     * its own speed
     * @param p_cell the cell contains the particles which are calculated
     */
    void step_1_prepare_cell (ParticleCell& p_cell);
    /**
     * calculates the movement of particles based on the forces between every
     * particle-pair in the given
     * cell
     * @param p_cell the cell which contains the particles
     */
    void step_2a_calculate_inside_cell (ParticleCell& p_cell);
    /**
     * calculates the movement based on forces between particles which are in
     * different cells each particle-pair consists of one particle from each cell given as
     * parameters
     * @param p_cell1
     * @param p_cell2
     */
    void step_2b_calculate_between_cells (ParticleCell& p_cell_i, ParticleCell& p_cell_j);
    void step_2b_calculate_between_cells (ParticleCell& p_cell_i,
                                          ParticleCell& p_cell_j,
                                          data_type     offset_x,
                                          data_type     offset_y,
                                          data_type     offset_z);
    /**
     * verify that all particles in cell are in the correct cell. if there are
     * particles which should be
     * in an other cell, these particles get moved
     * @param p_cell
     */
    void step_3_remove_wrong_particles_from_cell (ParticleCell& p_cell);

  public:
    /**
     * constructor
     */
    DatastructureGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    /**
     * destructor
     */
    ~DatastructureGrid ();
    void serialize ();
    bool run_simulation_iteration (unsigned long p_iteration_number = 0);
    void add_particle (Vec3f p_current_position);
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id = -1);
    unsigned long get_particle_count ();
};
#endif
