#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class ParticlesBase {
    protected:
    std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)> m_algorithm;
    std::string          m_stucture_name;
    std::vector<float *> m_positions_x;
    std::vector<float *> m_positions_y;
    std::vector<float *> m_positions_z;
    std::vector<float *> m_velocities_x;
    std::vector<float *> m_velocities_y;
    std::vector<float *> m_velocities_z;
    std::vector<float *> m_accelerations_x;
    std::vector<float *> m_accelerations_y;
    std::vector<float *> m_accelerations_z;

    public:
    virtual ~ParticlesBase () {
    }
    virtual void run_simulation_iteration () = 0;
    virtual void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) = 0;
    void        print_structure_name ();
    std::string get_structure_name ();
    void        set_algorithm (
        const std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)>
            &algorithm);
    const std::vector<float *> &get_accelerations_x () const;
    const std::vector<float *> &get_accelerations_y () const;
    const std::vector<float *> &get_accelerations_z () const;
    const std::vector<float *> &get_positions_x () const;
    const std::vector<float *> &get_positions_y () const;
    const std::vector<float *> &get_positions_z () const;
    const std::vector<float *> &get_velocities_x () const;
    const std::vector<float *> &get_velocities_y () const;
    const std::vector<float *> &get_velocities_z () const;
    unsigned long               get_particle_count ();
};
#endif
