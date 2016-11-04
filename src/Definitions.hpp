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
	GENERATOR_MODE_MULTIPLE_OBJECTS,	 // mehrere Kugeln gleichmäßig verteilt
	GENERATOR_MODE_RANDOM,				 // komplett zufällig
	GENERATOR_MODE_RANDOM_UNIFORM,		 // zufällig ungefähr gleichmäßig
	GENERATOR_MODE_SINGLE_OBJECT_MIDDLE, // eine Kugel in der Mitte des Volumens
	GENERATOR_MODE_UNIFORM_DISTRIBUTION, // komplett gleichmäßig
};

enum e_algorithm_type {
	LENNARD_JONES,
	SMOTHED_PARTICLE_HYDRODYNAMICS,
	DISSIPATIVE_PARTICLE_DYNAMICS
};

enum e_data_format { LAMMPS, ESPRESSO, GROMACS, VMD, VTK };

enum e_particle_variable { ID, VELOCITY, POSITION, ACCELERATION, PARTICLE_TYPE };

static std::map<e_particle_variable, const char *> g_enum_to_string_map = {
	std::pair<e_particle_variable, const char *> (VELOCITY, "write_velo"),
	std::pair<e_particle_variable, const char *> (POSITION, "write_pos"),
	std::pair<e_particle_variable, const char *> (ACCELERATION, "write_accel"),
	std::pair<e_particle_variable, const char *> (PARTICLE_TYPE, "write_type"),
};
#endif /* DEFINITIONS_HPP_ */
