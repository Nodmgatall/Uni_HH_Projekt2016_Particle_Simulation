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
#include "debug.hpp"
#include "particles.hpp"
#include <fstream>
#include <glm/glm.hpp>
#include <vector>

typedef enum GeneratorMode {
	GENERATOR_MODE_FILE,			 // lädt partikel aus einer Datei
	GENERATOR_MODE_SPHERE,			 // eine Kugel in der Mitte des Volumens
	GENERATOR_MODE_MULTIPLE_SPHERES, // mehrere Kugeln gleichmäßig verteilt
	GENERATOR_MODE_UNIFORM_DISTRIBUTION, // komplett gleichmäßig
	GENERATOR_MODE_RANDOM,				 // komplett zufällig
	GENERATOR_MODE_RANDOM_UNIFORM,		 // zufällig ungefähr gleichmäßig
} GeneratorMode;

EXTERN GeneratorMode generatorMode;
EXTERN Particles *particles;

#endif /* DEFINITIONS_HPP_ */
