/*
 * ParticleGeneratorRandomUniform.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "GeneratorRandomUniform.hpp"

GeneratorRandomUniform::GeneratorRandomUniform (s_options& p_options) : InputBase (p_options) {
    m_stucture_name = "ParticleGeneratorRandomUniform";
}

GeneratorRandomUniform::~GeneratorRandomUniform () {
}

void GeneratorRandomUniform::generate (DatastructureBase* p_particles) {
    (void) p_particles;
}
