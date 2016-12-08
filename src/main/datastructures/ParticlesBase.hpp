#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../Definitions.hpp"
#include "../IO/OptionsSimulation.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include "../Vec3.hpp"
#include "../algorithms/LennardJonesAlgorithm.hpp"
#include "../borders/ParticleBoundsCorrection.hpp"
#include <iostream>
#include <vector>

class ParticlesBase {
    protected:
    std::function<bool(data_type &p_position_1x,
                       data_type &p_position_1y,
                       data_type &p_position_1z,
                       data_type &p_position_delta_1x,
                       data_type &p_position_delta_1y,
                       data_type &p_position_delta_1z,
                       data_type &p_position_2x,
                       data_type &p_position_2y,
                       data_type &p_position_2z,
                       data_type &p_position_delta_2x,
                       data_type &p_position_delta_2y,
                       data_type &p_position_delta_2z)>
                              m_algorithm;
    std::string               m_stucture_name;
    s_simulator_options &     m_options;
    Vec3f &                   m_bounds;
    ParticleBoundsCorrection &m_particle_bounds_correction;

    public:
    virtual ~ParticlesBase () {
    }
    ParticlesBase (s_simulator_options &p_options, Vec3f &p_bounds, ParticleBoundsCorrection &p_particle_bounds_correction);
    virtual void run_simulation_iteration (unsigned long p_iteration_number = 0) = 0;
    virtual void add_particle (Vec3f p_position)                                 = 0;
    virtual void add_particle (Vec3f p_position, Vec3f p_velocity) = 0;
    void        print_structure_name ();
    std::string get_structure_name ();
    void set_algorithm (const std::function<bool(data_type &p_position_1x,
                                                 data_type &p_position_1y,
                                                 data_type &p_position_1z,
                                                 data_type &p_position_delta_1x,
                                                 data_type &p_position_delta_1y,
                                                 data_type &p_position_delta_1z,
                                                 data_type &p_position_2x,
                                                 data_type &p_position_2y,
                                                 data_type &p_position_2z,
                                                 data_type &p_position_delta_2x,
                                                 data_type &p_position_delta_2y,
                                                 data_type &p_position_delta_2z)> &algorithm);
    virtual unsigned long get_particle_count ()                           = 0;
    virtual void serialize (std::shared_ptr<ParticleFileWriter> p_writer) = 0;
};
#endif
