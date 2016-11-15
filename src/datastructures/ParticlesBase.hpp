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
    std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)> m_algorithm;
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
    void        set_algorithm (
        const std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)>
            &algorithm);
    virtual unsigned long get_particle_count () = 0;
    virtual void serialize (std::shared_ptr<ParticleFileWriter> p_writer) = 0;
};
#endif
