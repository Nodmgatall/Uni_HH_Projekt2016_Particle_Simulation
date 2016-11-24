#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../Definitions.hpp"
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
    vec3f                      m_corner000, m_corner111;
    vec3l                      m_idx; // bezug auf ParticlesGrid::m_cells
    ParticleCell (vec3l p_idx, vec3l p_size, vec3f &p_bounds);
    void add_particle (vec3f p_position, int p_id);
};

class ParticlesGrid : public ParticlesBase {
    private:

    unsigned long             m_max_id;
    std::vector<ParticleCell> m_cells;
    vec3l                     m_size;
    unsigned const int        m_iterations_between_rearange_particles;
    unsigned int              m_iterations_until_rearange_particles;
    unsigned int              m_idx_a; // aktueller index
    unsigned int              m_idx_b; // neuer/alter index :: es gilt immer m_idx_a=!m_idx_b
    inline unsigned long get_cell_index (long x, long y, long z);
    inline ParticleCell &get_cell_at (vec3l coord);
    inline ParticleCell &get_cell_at (long x, long y, long z);
    inline void step_1_prepare_cell (ParticleCell &p_cell);
    inline void step_2a_calculate_inside_cell (ParticleCell &p_cell);
    inline void step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell &p_cell2);
    inline void step_3_swap_old_new_position (ParticleCell &p_cell);
    inline void step_4_remove_wrong_particles_from_cell (ParticleCell &p_cell);
    inline void moveParticle (ParticleCell &p_cell_from, ParticleCell &p_cell_to, long p_index_from);

    public:
    ParticlesGrid (s_simulator_options *p_options, vec3f *p_bounds);
    ~ParticlesGrid ();
    void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
    void run_simulation_iteration ();
    void add_particle (vec3f p_position);
    unsigned long get_particle_count ();
};
#endif
