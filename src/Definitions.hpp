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

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "Debug.hpp"
#include "ParticlesBase.hpp"


enum e_generator_mode {
	GENERATOR_MODE_MULTIPLE_OBJECTS,	 // mehrere Kugeln gleichmäßig verteilt
	GENERATOR_MODE_RANDOM,				 // komplett zufällig
	GENERATOR_MODE_RANDOM_UNIFORM,		 // zufällig ungefähr gleichmäßig
	GENERATOR_MODE_SINGLE_OBJECT_MIDDLE, // eine Kugel in der Mitte des Volumens
	GENERATOR_MODE_UNIFORM_DISTRIBUTION, // komplett gleichmäßig
};
#endif /* DEFINITIONS_HPP_ */
