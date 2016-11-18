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
    vec3l                      m_index;
    ParticleCell (vec3l p_index, vec3l p_size, vec3f &p_bounds);
    void add_particle (vec3f p_position, vec3f p_velocity, int p_id);
};

class ParticlesGrid : public ParticlesBase {
    private:
    unsigned long             m_max_id;
    std::vector<ParticleCell> m_cells;
    vec3l                     m_size;
    unsigned const int        m_iterations_between_rearange_particles;
    unsigned int              m_iterations_until_rearange_particles;
    unsigned int              m_index_a, m_index_b;
    inline unsigned int getCellIndex (int x, int y, int z);
    inline ParticleCell &getCellAt (vec3l coord);
    inline ParticleCell &getCellAt (int x, int y, int z);
    inline void run_simulation_lennard_jones_1_prepare_cell (ParticleCell &cell);
    inline void run_simulation_lennard_jones_2_inside_cell (ParticleCell &cell);
    inline void run_simulation_lennard_jones_3_betweenCells (ParticleCell &cell1, ParticleCell &cell2);
    inline void run_simulation_lennard_jones_4_swap (ParticleCell &cell);
    inline void removeWrongParticlesFromCell (ParticleCell &cell);
    inline void removeWrongParticlesFromCells ();

    public:
    ParticlesGrid (s_simulator_options *p_options, vec3f *p_bounds);
    ~ParticlesGrid ();

    void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
    void run_simulation_iteration ();
    void add_particle (vec3f p_position, vec3f p_velocity);
    unsigned long get_particle_count ();
};
#endif
