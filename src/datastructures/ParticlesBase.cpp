#include "ParticlesBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"

void ParticlesBase::print_structure_name () {
    std::cout << m_stucture_name << std::endl;
}

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

void ParticlesBase::set_algorithm (const std::function<bool(int &position1x,
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
                                                            int &acceleration2z)> &algorithm) {
    m_algorithm = algorithm;
}
ParticlesBase::ParticlesBase (s_simulator_options *p_options, glm::vec3 *p_bounds)
: m_options (p_options), m_bounds (p_bounds) {
}
