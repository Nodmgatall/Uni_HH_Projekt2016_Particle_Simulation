#include "DatastructureBase.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleWriterBase.hpp"

std::string DatastructureBase::get_structure_name () {
    return m_stucture_name;
}

DatastructureBase::DatastructureBase (s_options&          p_options,
                                      BorderBase&         p_border,
                                      AlgorithmBase&      p_algorithm,
                                      ParticleWriterBase& p_particle_writer)
: m_options (p_options), m_border (p_border), m_algorithm (p_algorithm),
  m_particle_writer (p_particle_writer) {
}
