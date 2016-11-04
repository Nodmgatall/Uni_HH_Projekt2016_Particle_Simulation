/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */
#include <iostream>
#include <memory>
#include <string.h>

#include "ParticleGenerator.hpp"
e_generator_mode ParticleGenerator::m_mode = GENERATOR_MODE_UNIFORM_DISTRIBUTION;

void ParticleGenerator::generate (std::shared_ptr<Particles> p_particles, glm::vec3 p_bounds) {

	// enums defined in definitions
	std::cout << "ParticleGenerator :: starting" << std::endl;
	switch (m_mode) {
		case GENERATOR_MODE_MULTIPLE_OBJECTS:
			std::cout << "    method:" << std::endl;
			break;
		case GENERATOR_MODE_RANDOM:
			std::cout << "    method:" << std::endl;
			break;
		case GENERATOR_MODE_RANDOM_UNIFORM:
			std::cout << "    method:" << std::endl;
			break;
		case GENERATOR_MODE_SINGLE_OBJECT_MIDDLE:
			std::cout << "    method:" << std::endl;
			break;
		case GENERATOR_MODE_UNIFORM_DISTRIBUTION:
			std::cout << "    method: uniform distribution" << std::endl;
			generate_uniform_distribution (p_particles, p_bounds);
			break;
		default:
			DEBUG_BEGIN << DEBUG_VAR (m_mode) << DEBUG_END;
			exit (1);
	}
	std::cout << "ParticleGenerator :: finish" << std::endl;
}
void ParticleGenerator::generate_uniform_distribution (std::shared_ptr<Particles> p_particles, glm::vec3 p_bounds) {
	float	 temp	= pow (p_particles->get_particle_count (), 1.0f / 3.0f);
	glm::vec3 delta   = (glm::vec3 (0, 0, 0) - p_bounds) / (temp - 1);
	int		  tempInt = temp;
	for (int x = 0; x < tempInt; x++) {
		for (int y = 0; y < tempInt; y++) {
			for (int z = 0; z < tempInt; z++) {
				p_particles->add_particle (glm::vec3 (x * delta.x, y * delta.y, z * delta.z),
										   glm::vec3 (0, 0, 0),
										   glm::vec3 (0, 0, 0));
			}
		}
	}
	int p_patriclesGenerated = pow (tempInt, 3);
	DEBUG_BEGIN << DEBUG_VAR (p_patriclesGenerated) << DEBUG_END;
}

void ParticleGenerator::generate_random (std::shared_ptr<Particles> p_particles, glm::vec3 p_bounds) {
	long seed = std::time (0);
	std::srand (seed);
	for (unsigned long i = 0; i < p_particles->get_particle_count (); i++) {
		p_particles->add_particle (glm::vec3 (std::rand () / RAND_MAX, std::rand () / RAND_MAX, std::rand () / RAND_MAX) * p_bounds,
								   glm::vec3 (0, 0, 0),
								   glm::vec3 (0, 0, 0));
	}
}

void ParticleGenerator::set_generator_mode (char *p_argument_mode) {
	if (strcmp (p_argument_mode, "GMUD") == 0) {
		m_mode = GENERATOR_MODE_UNIFORM_DISTRIBUTION;
	}
}
