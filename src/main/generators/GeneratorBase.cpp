/*
 * ParticleGeneratorBase.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "GeneratorBase.hpp"

GeneratorBase::GeneratorBase (s_options& p_options)
: m_options (p_options), m_stucture_name ("ParticleGeneratorBase") {
}

GeneratorBase::~GeneratorBase () {
}

const std::string& GeneratorBase::get_stucture_name () const {
    return m_stucture_name;
}
