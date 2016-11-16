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
    std::function<bool(int &position1x,
                       int &position1y,
                       int &position1z,
                       int &velocity1x,
                       int &velocity1y,
                       int &velocity1z,
                       int &acceleration1x,
                       int &acceleration1y,
                       int &acceleration1z,
                       int &position2x,
                       int &position2y,
                       int &position2z,
                       int &velocity2x,
                       int &velocity2y,
                       int &velocity2z,
                       int &acceleration2x,
                       int &acceleration2y,
                       int &acceleration2z)>
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
    void set_algorithm (const std::function<bool(int &position1x,
                                                 int &position1y,
                                                 int &position1z,
                                                 int &velocity1x,
                                                 int &velocity1y,
                                                 int &velocity1z,
                                                 int &acceleration1x,
                                                 int &acceleration1y,
                                                 int &acceleration1z,
                                                 int &position2x,
                                                 int &position2y,
                                                 int &position2z,
                                                 int &velocity2x,
                                                 int &velocity2y,
                                                 int &velocity2z,
                                                 int &acceleration2x,
                                                 int &acceleration2y,
                                                 int &acceleration2z)> &algorithm);
    virtual unsigned long get_particle_count ()                           = 0;
    virtual void serialize (std::shared_ptr<ParticleFileWriter> p_writer) = 0;
};
#endif
