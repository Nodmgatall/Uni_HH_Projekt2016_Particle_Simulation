#include "ParticlesBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"

void ParticlesBase::print_structure_name () {
    std::cout << m_stucture_name << std::endl;
}

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

void ParticlesBase::set_algorithm (const std::function<bool(float &p_position_1x,
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
                                                            float &p_position_delta_2z)> &algorithm) {
    m_algorithm = algorithm;
}
ParticlesBase::ParticlesBase (s_simulator_options *p_options, vec3 *p_bounds)
: m_options (p_options), m_bounds (p_bounds) {
}
