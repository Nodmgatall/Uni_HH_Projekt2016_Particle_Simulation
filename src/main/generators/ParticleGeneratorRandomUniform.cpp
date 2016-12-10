/*
 * ParticleGeneratorRandomUniform.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "ParticleGeneratorRandomUniform.hpp"

ParticleGeneratorRandomUniform::ParticleGeneratorRandomUniform (s_options& p_options)
: ParticleGeneratorBase (p_options) {
    m_stucture_name = "ParticleGeneratorRandomUniform";
}

ParticleGeneratorRandomUniform::~ParticleGeneratorRandomUniform () {
}

void ParticleGeneratorRandomUniform::generate (DatastructureBase* p_particles) {
    (void) p_particles;
}
