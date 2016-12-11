/*
 * ParticleGeneratorMultipleObjects.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "GeneratorMultipleObjects.hpp"

GeneratorMultipleObjects::GeneratorMultipleObjects (s_options& p_options, DatastructureBase& p_datastructure)
: InputBase (p_options, p_datastructure) {
    m_stucture_name = "GeneratorMultipleObjects";
}

GeneratorMultipleObjects::~GeneratorMultipleObjects () {
}

void GeneratorMultipleObjects::initialize_datastructure () {
}
