#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../Definitions.hpp"
#include "../tools/Debug.hpp"
#include "ParticlesBase.hpp"

struct ParticleCell {
    std::vector<float>         m_positions_x;
    std::vector<float>         m_positions_y;
    std::vector<float>         m_positions_z;
    std::vector<float>         m_positions_delta_x;
    std::vector<float>         m_positions_delta_y;
    std::vector<float>         m_positions_delta_z;
    std::vector<unsigned long> m_ids;
    void add_particle (vec3f p_position, vec3f p_velocity, int p_id);
};

class ParticlesGrid : public ParticlesBase {
    private:
    unsigned long             m_max_id;
    std::vector<ParticleCell> m_cells;
    vec3l                     m_size;
    ParticleCell &getCellAt (int x, int y, int z);
    void run_simulation_insideCell (ParticleCell &cell);
    void run_simulation_betweenCells (ParticleCell &cell1, ParticleCell &cell2);

    public:
    ParticlesGrid (s_simulator_options *p_options, vec3f *p_bounds);
    ~ParticlesGrid ();

    void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
    void run_simulation_iteration ();
    void add_particle (vec3f p_position, vec3f p_velocity);
    unsigned long get_particle_count ();
};
#endif
