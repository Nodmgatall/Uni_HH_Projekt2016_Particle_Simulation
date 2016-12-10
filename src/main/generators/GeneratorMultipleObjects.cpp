/*
 * ParticleGeneratorMultipleObjects.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "GeneratorMultipleObjects.hpp"

GeneratorMultipleObjects::GeneratorMultipleObjects (s_options& p_options)
: GeneratorBase (p_options) {
    m_stucture_name = "ParticleGeneratorMultipleObjects";
}

GeneratorMultipleObjects::~GeneratorMultipleObjects () {
}

void GeneratorMultipleObjects::generate (DatastructureBase* p_particles) {
    (void) p_particles;
}
