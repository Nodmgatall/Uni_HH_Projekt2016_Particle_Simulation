/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGenerator.hpp"

void ParticleGenerator::generate (GeneratorMode generatorMode) {
	switch (generatorMode) {
	GENERATOR_MODE_FILE : {
		debug ("ParticleGenerator::generate", "falscher Parameter", generatorMode);
		break;
	}
	GENERATOR_MODE_MULTIPLE_SPHERES : { break; }
	GENERATOR_MODE_RANDOM : { break; }
	GENERATOR_MODE_RANDOM_UNIFORM : { break; }
	GENERATOR_MODE_SPHERE : { break; }
	GENERATOR_MODE_UNIFORM_DISTRIBUTION : { break; }
		default:
			debug ("ParticleGenerator::generate", generatorMode);
	}
}
