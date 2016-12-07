#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../Definitions.hpp"
#include "../algorithms/ParticleBoundsCorrection.hpp"
#include "../algorithms/ParticleBoundsCorrectionWraparound.hpp"
#include "../tools/Debug.hpp"
#include "ParticlesBase.hpp"

/*
 * Partikel, die auf der einen Seite das Grid verlassen, kommen auf der anderen Seite wieder rein.
 * */
struct ParticleCell {
    std::vector<float>         m_positions_x[2];
    std::vector<float>         m_positions_y[2];
    std::vector<float>         m_positions_z[2];
    std::vector<unsigned long> m_ids;
    Vec3f                      m_corner000, m_corner111;
    Vec3l                      m_idx; // bezug auf ParticlesGrid::m_cells
    ParticleCell (Vec3l p_idx, Vec3l p_size, Vec3f &p_bounds);
    void add_particle (Vec3f p_current_position, Vec3f p_old_position, int p_current_index, int p_id);
};

class ParticlesGrid : public ParticlesBase {
    private:
    ParticleBoundsCorrection *m_particle_bounds_correction;
    unsigned long             m_max_id;
    std::vector<ParticleCell> m_cells;
    Vec3l                     m_size;
    Vec3f                     m_size_per_cell;
    unsigned const int        m_iterations_between_rearange_particles;
    unsigned int              m_iterations_until_rearange_particles;
    unsigned int              m_idx_a; // aktueller index
    unsigned int              m_idx_b; // neuer/alter index :: es gilt immer m_idx_a=!m_idx_b
    inline unsigned long get_cell_index (long x, long y, long z);
    inline ParticleCell &get_cell_at (long x, long y, long z);
    ParticleCell &get_cell_for_particle (float x, float y, float z);
    ParticleCell &get_cell_for_particle (Vec3f m_position);
    inline void moveParticle (ParticleCell &p_cell_from, ParticleCell &p_cell_to, long p_index_from);
    inline void step_1_prepare_cell (ParticleCell &p_cell);
    inline void step_2a_calculate_inside_cell (ParticleCell &p_cell);
    inline void step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell &p_cell2);
    inline void step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell);

    public:
    ParticlesGrid (s_simulator_options *p_options, Vec3f *p_bounds);
    ~ParticlesGrid ();
    void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
    void run_simulation_iteration (unsigned long p_iteration_number = 0);
    void add_particle (Vec3f p_current_position);
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity);
    unsigned long get_particle_count ();
};
#endif
