/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGenerator.hpp"
e_generator_mode ParticleGenerator::m_mode = GENERATOR_MODE_UNIFORM_DISTRIBUTION;

void ParticleGenerator::generate (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds, int p_count) {
	std::cout << "ParticleGenerator :: starting" << std::endl;
	std::cout<< "    generating "<<p_particles->get_particle_count ()<<" Particles"<<std::endl;
	switch (m_mode) {
		case GENERATOR_MODE_MULTIPLE_OBJECTS:
			break;
		case GENERATOR_MODE_RANDOM:generate_random (p_particles, p_bounds,p_count);
			break;
		case GENERATOR_MODE_RANDOM_UNIFORM:
			break;
		case GENERATOR_MODE_SINGLE_OBJECT_MIDDLE:
			break;
		case GENERATOR_MODE_UNIFORM_DISTRIBUTION:
			generate_uniform_distribution (p_particles, p_bounds,p_count);
			break;
		default:
			std::cout << "ParticleGenerator :: error" << std::endl;
			DEBUG_BEGIN << DEBUG_VAR (m_mode) << DEBUG_END;
			exit (1);
	}
	std::cout << "ParticleGenerator :: finish" << std::endl;
}
void ParticleGenerator::generate_uniform_distribution (std::shared_ptr<ParticlesBase> p_particles,
													   glm::vec3					  p_bounds, int p_count) {
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

void ParticleGenerator::generate_random (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds, int p_count) {
	long seed = std::time (0);
	std::srand (seed); // TODO parameter bei programmstart
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

void ParticleGenerator::set_generator_count(char* p_argument_count) {


}
