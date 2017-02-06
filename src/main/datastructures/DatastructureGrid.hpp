#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP
#include "DatastructureBase.hpp"
#include "Definitions.hpp"
#include "Vec3.hpp"
class DatastructureGrid : public DatastructureBase {
  protected:
    /**
     * the count of cells in 3 dimensions
     * refer to m_cells
     */
    Vec3l grid_size;
    /**
     * the coordinate space captured by each cell
     */
    Vec3f grid_size_per_cell;
    /**
     * return the combined index for the cell at the given index
     * @param x index
     * @param y index
     * @param z index
     */
    unsigned long grid_get_cell_index (long x, long y, long z);
    /**
     * returns the cell at the given index
     * @param x index
     * @param y index
     * @param z index
     * @return the cell
     */
    ParticleGroup& grid_get_cell_at (long x, long y, long z);
    /**
     * return the cell for the given coordinate
     * @param x coordinate
     * @param y coordinate
     * @param z coordinate
     * @return the cell
     */
    ParticleGroup& grid_get_cell_for_particle (data_type x, data_type y, data_type z);
    /**
     *
     * @param x
     * @param y
     * @param z
     * @return the index for the cell given as x y and z
     */
    Vec3l grid_get_cell_index_for_particle (data_type x, data_type y, data_type z);
    /**
     * return the cell for the given position
     * @param m_position the position
     * @return the cell
     */
    ParticleGroup& grid_get_cell_for_particle (Vec3f m_position);
    /**
     * moves an particle from one cell to another
     * @param p_cell_from
     * @param p_cell_to
     * @param p_index_from
     */
    void grid_moveParticle (ParticleGroup& p_cell_from, ParticleGroup& p_cell_to, long p_index_from);
    /**
     * complete second step of calculation
     */
    bool grid_step_2 ();
    /**
     * calculates the movement of particles based on the forces between every
     * particle-pair in the given
     * cell
     * @param p_cell the cell which contains the particles
     */
    virtual void grid_step_2a_calculate_inside_cell (ParticleGroup& p_cell);
    /**
     * calculates the movement based on forces between particles which are in
     * different cells each particle-pair consists of one particle from each cell given as
     * parameters
     * @param p_cell1
     * @param p_cell2
     */
    virtual void grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j);
    /**
     * calculates the movement based on forces between particles which are in
     * different cells each particle-pair consists of one particle from each cell given as
     * if this function is called it is assumed, that the given cells are only neigbours over
     * the borders of the simulated volume
     * parameters
     * @param p_cell1
     * @param p_cell2
     */
    virtual void grid_step_2b_calculate_between_cells (ParticleGroup& p_cell_i, ParticleGroup& p_cell_j, data_type p_offset_x, data_type p_offset_y, data_type p_offset_z);
    /**
     * verify that all particles in cell are in the correct cell. if there are
     * particles which should be
     * in an other cell, these particles get moved
     * @param p_cell
     */
    void grid_step_3_remove_wrong_particles_from_cell (ParticleGroup& p_cell);

  public:
    /**
     * constructor
     */
    DatastructureGrid (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_particle_writer);
    /**
     * destructor
     */
    virtual ~DatastructureGrid ();
    virtual bool run_simulation_iteration (unsigned long p_iteration_number = 0) override;
    void add_particle (Vec3f p_position) override;
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id = -1) override;
};
#endif
