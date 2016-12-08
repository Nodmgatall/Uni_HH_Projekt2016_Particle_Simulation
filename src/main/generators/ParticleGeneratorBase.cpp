/*
 * ParticleGeneratorBase.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorBase.hpp"

ParticleGeneratorBase::ParticleGeneratorBase (s_options &p_options)
: m_options (p_options), m_stucture_name ("ParticleGeneratorBase") {
}

ParticleGeneratorBase::~ParticleGeneratorBase () {
}

const std::string &ParticleGeneratorBase::get_stucture_name () const {
    return m_stucture_name;
}
