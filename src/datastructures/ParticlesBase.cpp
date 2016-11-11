#include "ParticlesBase.hpp"

void ParticlesBase::print_structure_name () {
    std::cout << m_stucture_name << std::endl;
}

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

const std::vector<float *> &ParticlesBase::get_accelerations_x () const {
    return m_accelerations_x;
}

const std::vector<float *> &ParticlesBase::get_accelerations_y () const {
    return m_accelerations_y;
}

const std::vector<float *> &ParticlesBase::get_accelerations_z () const {
    return m_accelerations_z;
}

const std::vector<float *> &ParticlesBase::get_positions_x () const {
    return m_positions_x;
}

const std::vector<float *> &ParticlesBase::get_positions_y () const {
    return m_positions_y;
}

const std::vector<float *> &ParticlesBase::get_positions_z () const {
    return m_positions_z;
}

const std::vector<float *> &ParticlesBase::get_velocities_x () const {
    return m_velocities_x;
}

const std::vector<float *> &ParticlesBase::get_velocities_y () const {
    return m_velocities_y;
}

const std::vector<float *> &ParticlesBase::get_velocities_z () const {
    return m_velocities_z;
}
unsigned long ParticlesBase::get_particle_count () {
    return m_positions_x.size ();
}

void ParticlesBase::set_algorithm (
    const std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)>
        &algorithm) {
    m_algorithm = algorithm;
}
