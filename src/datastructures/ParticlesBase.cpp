#include "ParticlesBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"

void ParticlesBase::print_structure_name () {
    std::cout << m_stucture_name << std::endl;
}

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

void ParticlesBase::set_algorithm (const std::function<bool(float &position1x,
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
                                                            float &acceleration2z)> &algorithm) {
    m_algorithm = algorithm;
}
ParticlesBase::ParticlesBase (s_simulator_options *p_options, glm::vec3 *p_bounds)
: m_options (p_options), m_bounds (p_bounds) {
}
