#ifndef PARTICLESGRID_HPP
#define PARTICLESGRID_HPP

#include "../tools/Debug.hpp"
#include "ParticlesBase.hpp"

struct ParticleCell {
    std::vector<float>         m_positions_x;
    std::vector<float>         m_positions_y;
    std::vector<float>         m_positions_z;
    std::vector<float>         m_velocities_x;
    std::vector<float>         m_velocities_y;
    std::vector<float>         m_velocities_z;
    std::vector<float>         m_accelerations_x;
    std::vector<float>         m_accelerations_y;
    std::vector<float>         m_accelerations_z;
    std::vector<unsigned long> m_ids;
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration, int p_id);
};

class ParticlesGrid : public ParticlesBase {
    private:
    unsigned long             m_max_id;
    std::vector<ParticleCell> m_cells;
    long                      m_size_x, m_size_y, m_size_z;
    ParticleCell &getCellAt (int x, int y, int z);
    void run_simulation_insideCell (ParticleCell &cell);
    void run_simulation_betweenCells (ParticleCell &cell1, ParticleCell &cell2);

    public:
    ParticlesGrid (s_simulator_options *p_options, glm::vec3 *p_bounds);
    ~ParticlesGrid ();

    void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
    void run_simulation_iteration ();
    void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration);
    unsigned long get_particle_count ();
};
#endif
