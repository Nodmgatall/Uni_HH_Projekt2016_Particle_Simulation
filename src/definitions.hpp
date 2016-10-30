/*
 * definitions.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_
#ifndef EXTERN
#define EXTERN extern
#endif
#include <fstream>
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

#include "debug.hpp"
#include "particles.hpp"

typedef enum {
	GENERATOR_MODE_FILE,			 // lädt partikel aus einer Datei
	GENERATOR_MODE_SPHERE,			 // eine Kugel in der Mitte des Volumens
	GENERATOR_MODE_MULTIPLE_SPHERES, // mehrere Kugeln gleichmäßig verteilt
	GENERATOR_MODE_UNIFORM_DISTRIBUTION, // komplett gleichmäßig
	GENERATOR_MODE_RANDOM,				 // komplett zufällig
	GENERATOR_MODE_RANDOM_UNIFORM,		 // zufällig ungefähr gleichmäßig
} GeneratorMode;

class ParticleBounds {
	public:
	vec3 m_p0, m_p1;
	ParticleBounds () {
		m_p0 = vec3 (0, 0, 0);
		m_p1 = vec3 (1, 1, 1);
	}
};

class StartParams {
	public:
	int			   m_particleCount;
	ParticleBounds m_particleBounds;
	GeneratorMode  m_generatorMode;
	StartParams () {
		m_particleCount = 27;
		m_generatorMode = GENERATOR_MODE_UNIFORM_DISTRIBUTION;
	}
};

EXTERN StartParams startParams;
EXTERN Particles *particles;

#endif /* DEFINITIONS_HPP_ */
