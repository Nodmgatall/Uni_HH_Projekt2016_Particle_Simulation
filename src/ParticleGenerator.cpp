/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */
#include <memory>

#include "ParticleGenerator.hpp"
#include <iostream>

e_generator_mode ParticleGenerator::m_mode = GENERATOR_MODE_UNIFORM_DISTRIBUTION;

void ParticleGenerator::generate (std::shared_ptr<Particles> p_particles, glm::vec3 p_bounds) {

	// enums defined in definitions
	switch (m_mode) {
		case GENERATOR_MODE_MULTIPLE_SPHERES:
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
			std::cout << "Starting generation" << std::endl
					  << "    method: uniform distribution" << std::endl;
			generate_uniform_distribution (p_particles, p_bounds);
			break;
		default:
			DEBUG_BEGIN << DEBUG_VAR (m_mode) << DEBUG_END;
			exit (1);
	}
	std::cout << "Generation finished" << std::endl;
}
void ParticleGenerator::generate_uniform_distribution (std::shared_ptr<Particles> p_particles,
													   glm::vec3 p_bounds) {
	float	 temp	= pow (p_particles->get_particle_count (), 1.0f / 3.0f);
	glm::vec3 delta   = (glm::vec3 (0, 0, 0) - p_bounds) / (temp - 1);
	int		  tempInt = temp;
	for (int x = 0; x < tempInt; x++) {
		for (int y = 0; y < tempInt; y++) {
			for (int z = 0; z < tempInt; z++) {

				p_particles->add_particle (glm::vec3 (x * delta.x,
													  y * delta.y,
													  z * delta.z),
										   glm::vec3 (0, 0, 0),
										   glm::vec3 (0, 0, 0));
			}
		}
	}
	int p_patriclesGenerated = pow (tempInt, 3);
	DEBUG_BEGIN << DEBUG_VAR (p_patriclesGenerated) << DEBUG_END;
}

void ParticleGenerator::set_generator_mode (e_generator_mode p_mode) {
	m_mode = p_mode;
}
