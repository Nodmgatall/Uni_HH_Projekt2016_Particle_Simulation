/*
 * ParticleGeneratorMultipleObjects.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "ParticleGeneratorMultipleObjects.hpp"

ParticleGeneratorMultipleObjects::ParticleGeneratorMultipleObjects (s_options& p_options)
: ParticleGeneratorBase (p_options) {
    m_stucture_name = "ParticleGeneratorMultipleObjects";
}

ParticleGeneratorMultipleObjects::~ParticleGeneratorMultipleObjects () {
}

void ParticleGeneratorMultipleObjects::generate (ParticlesBase* p_particles) {
    (void) p_particles;
}
