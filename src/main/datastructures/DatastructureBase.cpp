#include "DatastructureBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleWriterBase.hpp"

std::string DatastructureBase::get_structure_name () {
    return m_stucture_name;
}

DatastructureBase::DatastructureBase (s_options&          p_options,
                                      BorderBase&         p_particle_bounds_correction,
                                      AlgorithmBase&      p_algorithm,
                                      ParticleWriterBase& p_particle_writer)
: m_options (p_options), m_border (p_particle_bounds_correction), m_algorithm (p_algorithm),
  m_particle_writer (p_particle_writer) {
}

void DatastructureBase::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
}

void DatastructureBase::add_particle (Vec3f p_position) {
    (void) p_position;
}

void DatastructureBase::add_particle (Vec3f p_position, Vec3f p_velocity) {
    (void) p_position;
    (void) p_velocity;
}

unsigned long DatastructureBase::get_particle_count () {
    return 0;
}

void DatastructureBase::serialize () {
}
