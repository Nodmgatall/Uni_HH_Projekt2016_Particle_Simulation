#include "ParticlesBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

ParticlesBase::ParticlesBase (s_options &               p_options,
                              ParticleBoundsCorrection &p_particle_bounds_correction,
                              AlgorithmBase &           p_algorithm)
: m_options (p_options), m_particle_bounds_correction (p_particle_bounds_correction),
  m_algorithm (p_algorithm) {
}
