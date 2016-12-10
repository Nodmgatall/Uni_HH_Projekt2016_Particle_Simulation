#include "ParticlesBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}

ParticlesBase::ParticlesBase (s_options&                p_options,
                              ParticleBoundsCorrection& p_particle_bounds_correction,
                              AlgorithmBase&            p_algorithm,
                              ParticleFileWriter&       p_particle_writer)
: m_options (p_options), m_particle_bounds_correction (p_particle_bounds_correction),
  m_algorithm (p_algorithm), m_particle_writer (p_particle_writer) {
}

void ParticlesBase::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
}

void ParticlesBase::add_particle (Vec3f p_position) {
    (void) p_position;
}

void ParticlesBase::add_particle (Vec3f p_position, Vec3f p_velocity) {
    (void) p_position;
    (void) p_velocity;
}

unsigned long ParticlesBase::get_particle_count () {
    return 0;
}

void ParticlesBase::serialize () {
}
