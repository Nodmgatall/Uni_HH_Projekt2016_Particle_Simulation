/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGenerator.hpp"

void ParticleGenerator::generate (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds) {
	std::cout << "ParticleGenerator :: starting" << std::endl;
	std::cout << "    generating " << p_particles->get_particle_count () << " Particles" << std::endl;
	switch (m_mode) {
		case MULTIPLE_OBJECTS:
			break;
		case RANDOM:
			generate_random (p_particles, p_bounds);
			break;
		case RANDOM_UNIFORM:
			break;
		case SINGLE_OBJECT_MIDDLE:
			break;
		case UNIFORM_DISTRIBUTION:
			generate_uniform_distribution (p_particles, p_bounds);
			break;
		default:
			std::cout << "ParticleGenerator :: error: no mode selected" << std::endl;
			DEBUG_BEGIN << DEBUG_VAR (m_mode) << DEBUG_END;
			exit (1);
	}
	std::cout << "ParticleGenerator :: finish" << std::endl;
}
void ParticleGenerator::generate_uniform_distribution (std::shared_ptr<ParticlesBase> p_particles,
													   glm::vec3					  p_bounds) {
	std::cout << "    method :: uniform distribution" << std::endl;
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

void ParticleGenerator::generate_random (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds) {
	long seed = std::time (0);
	std::srand (seed); // TODO parameter bei programmstart
	for (unsigned long i = 0; i < p_particles->get_particle_count (); i++) {
		p_particles->add_particle (glm::vec3 (std::rand () / RAND_MAX, std::rand () / RAND_MAX, std::rand () / RAND_MAX) * p_bounds,
								   glm::vec3 (0, 0, 0),
								   glm::vec3 (0, 0, 0));
	}
}

void ParticleGenerator::set_generator_mode (e_generator_mode p_mode) {
	m_mode = p_mode;
}

void ParticleGenerator::print_generator_mode()
{
    std::cout <<"Generator mode: " <<m_mode << std::endl;
}
