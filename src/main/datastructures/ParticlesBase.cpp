#include "ParticlesBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"

void ParticlesBase::print_structure_name () {
    std::cout << m_stucture_name << std::endl;
}

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

void ParticlesBase::set_algorithm (const std::function<bool(data_type &p_position_1x,
                                                            data_type &p_position_1y,
                                                            data_type &p_position_1z,
                                                            data_type &p_position_delta_1x,
                                                            data_type &p_position_delta_1y,
                                                            data_type &p_position_delta_1z,
                                                            data_type &p_position_2x,
                                                            data_type &p_position_2y,
                                                            data_type &p_position_2z,
                                                            data_type &p_position_delta_2x,
                                                            data_type &p_position_delta_2y,
                                                            data_type &p_position_delta_2z)> &algorithm) {
    m_algorithm = algorithm;
}
ParticlesBase::ParticlesBase (s_simulator_options &p_options, Vec3f &p_bounds, ParticleBoundsCorrection &p_particle_bounds_correction)
: m_options (p_options), m_bounds (p_bounds), m_particle_bounds_correction (p_particle_bounds_correction) {
}
