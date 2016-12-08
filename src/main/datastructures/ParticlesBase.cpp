#include "ParticlesBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"

void ParticlesBase::print_structure_name () {
    std::cout << m_stucture_name << std::endl;
}

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

ParticlesBase::ParticlesBase (s_options &p_options, Vec3f &p_bounds, ParticleBoundsCorrection &p_particle_bounds_correction)
: m_options (p_options), m_bounds (p_bounds), m_particle_bounds_correction (p_particle_bounds_correction) {
}
