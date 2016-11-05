/*
 * ParticleGenerator.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEGENERATOR_HPP_
#define SRC_PARTICLEGENERATOR_HPP_

#include "../Definitions.hpp"
#include "../datastructures/ParticlesBase.hpp"

class ParticleGenerator {
	public:
	static void generate (std::shared_ptr<ParticlesBase> p_particles,
						  glm::vec3						 p_bounds,
						  e_generator_mode				 p_generator_mode,
						  unsigned long					 p_particle_count);
	static void generate_uniform_distribution (std::shared_ptr<ParticlesBase> p_particles,
											   glm::vec3					  p_bounds,
											   e_generator_mode				  p_generator_mode,
											   unsigned long				  p_particle_count);
	static void generate_random (std::shared_ptr<ParticlesBase> p_particles,
								 glm::vec3						p_bounds,
								 e_generator_mode				p_generator_mode,
								 unsigned long					p_particle_count);
};

#endif /* SRC_PARTICLEGENERATOR_HPP_ */
