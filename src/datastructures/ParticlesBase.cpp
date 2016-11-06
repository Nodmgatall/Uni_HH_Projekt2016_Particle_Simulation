#include "ParticlesBase.hpp"

void ParticlesBase::print_structure_name () {
    std::cout << m_stucture_name << std::endl;
}

std::string ParticlesBase::get_structure_name () {
    return m_stucture_name;
}
