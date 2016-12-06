/*
 * ParticleGeneratorBase.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorBase.hpp"

ParticleGeneratorBase::ParticleGeneratorBase (s_generator_options *p_gen_options)
: m_options (p_gen_options) {
}

ParticleGeneratorBase::~ParticleGeneratorBase () {
}

e_generator_mode ParticleGeneratorBase::get_generator_mode () {
    return m_options->m_mode;
}
