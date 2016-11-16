#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../Definitions.hpp"
#include "../IO/OptionsSimulation.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class ParticlesBase {
    protected:
    std::function<bool(float &position1x,
                       float &position1y,
                       float &position1z,
                       float &velocity1x,
                       float &velocity1y,
                       float &velocity1z,
                       float &acceleration1x,
                       float &acceleration1y,
                       float &acceleration1z,
                       float &position2x,
                       float &position2y,
                       float &position2z,
                       float &velocity2x,
                       float &velocity2y,
                       float &velocity2z,
                       float &acceleration2x,
                       float &acceleration2y,
                       float &acceleration2z)>
                         m_algorithm;
    std::string          m_stucture_name;
    s_simulator_options *m_options;
    glm::vec3 *          m_bounds;

    public:
    virtual ~ParticlesBase () {
    }
    ParticlesBase (s_simulator_options *p_options, glm::vec3 *p_bounds);
    virtual void run_simulation_iteration () = 0;
    virtual void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) = 0;
    void        print_structure_name ();
    std::string get_structure_name ();
    void set_algorithm (const std::function<bool(float &position1x,
                                                 float &position1y,
                                                 float &position1z,
                                                 float &velocity1x,
                                                 float &velocity1y,
                                                 float &velocity1z,
                                                 float &acceleration1x,
                                                 float &acceleration1y,
                                                 float &acceleration1z,
                                                 float &position2x,
                                                 float &position2y,
                                                 float &position2z,
                                                 float &velocity2x,
                                                 float &velocity2y,
                                                 float &velocity2z,
                                                 float &acceleration2x,
                                                 float &acceleration2y,
                                                 float &acceleration2z)> &algorithm);
    virtual unsigned long get_particle_count ()                           = 0;
    virtual void serialize (std::shared_ptr<ParticleFileWriter> p_writer) = 0;
};
#endif
