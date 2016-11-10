#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class ParticlesBase {
    public:
    unsigned long              m_max_used_id;
    std::vector<unsigned long> m_ids;
    std::string                m_stucture_name;
    std::vector<glm::vec3>     m_positions;
    std::vector<glm::vec3>     m_velocities;
    std::vector<glm::vec3>     m_accelerations;
    std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)> m_algorithm;

    virtual std::vector<glm::vec3> *    get_velocities ()    = 0;
    virtual std::vector<glm::vec3> *    get_positions ()     = 0;
    virtual std::vector<glm::vec3> *    get_accelerations () = 0;
    virtual std::vector<unsigned long> *get_ids ()           = 0;
    virtual void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) = 0;
    virtual unsigned long get_particle_count ()       = 0;
    virtual void          run_simulation_iteration () = 0;
    void                  print_structure_name ();
    std::string           get_structure_name ();
    void                  set_algorithm (
        const std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)>
            &algorithm);
};
#endif
