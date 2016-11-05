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

#include "datastructures/ParticlesBase.hpp"
#include "tools/Debug.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

enum e_generator_mode {
	NO_MODE,			  // for initalisation
	MULTIPLE_OBJECTS,	 // mehrere Kugeln gleichmäßig verteilt
	RANDOM,				  // komplett zufällig
	RANDOM_UNIFORM,		  // zufällig ungefähr gleichmäßig
	SINGLE_OBJECT_MIDDLE, // eine Kugel in der Mitte des Volumens
	UNIFORM_DISTRIBUTION, // komplett gleichmäßig
};
enum e_algorithm_type {
	NO_ALGORITHM, // for initalisation
	LENNARD_JONES,
	SMOTHED_PARTICLE_HYDRODYNAMICS,
	DISSIPATIVE_PARTICLE_DYNAMICS
};

enum e_data_format { NO_FORMAT, LAMMPS, ESPRESSO, GROMACS, VMD, VTK };

enum e_particle_variable { ID, VELOCITY, POSITION, ACCELERATION, PARTICLE_TYPE };

#endif /* DEFINITIONS_HPP_ */
