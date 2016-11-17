#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../Definitions.hpp"
#include "../IO/OptionsSimulation.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include "../vec3.hpp"
#include <iostream>
#include <vector>

class ParticlesBase {
    protected:
    std::function<bool(float &p_position_1x,
                       float &p_position_1y,
                       float &p_position_1z,
                       float &p_position_delta_1x,
                       float &p_position_delta_1y,
                       float &p_position_delta_1z,
                       float &p_position_2x,
                       float &p_position_2y,
                       float &p_position_2z,
                       float &p_position_delta_2x,
                       float &p_position_delta_2y,
                       float &p_position_delta_2z)>
                         m_algorithm;
    std::string          m_stucture_name;
    s_simulator_options *m_options;
    vec3f *              m_bounds;

    public:
    virtual ~ParticlesBase () {
    }
    ParticlesBase (s_simulator_options *p_options, vec3f *p_bounds);
    virtual void run_simulation_iteration () = 0;
    virtual void add_particle (vec3f p_position, vec3f p_velocity) = 0;
    void        print_structure_name ();
    std::string get_structure_name ();
    void set_algorithm (const std::function<bool(float &p_position_1x,
                                                 float &p_position_1y,
                                                 float &p_position_1z,
                                                 float &p_position_delta_1x,
                                                 float &p_position_delta_1y,
                                                 float &p_position_delta_1z,
                                                 float &p_position_2x,
                                                 float &p_position_2y,
                                                 float &p_position_2z,
                                                 float &p_position_delta_2x,
                                                 float &p_position_delta_2y,
                                                 float &p_position_delta_2z)> &algorithm);
    virtual unsigned long get_particle_count ()                           = 0;
    virtual void serialize (std::shared_ptr<ParticleFileWriter> p_writer) = 0;
};
#endif
