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
	private:
	e_generator_mode m_generator_mode;

	public:
	void generate (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds, unsigned long p_particle_count);
	void generate_uniform_distribution (std::shared_ptr<ParticlesBase> p_particles,
										glm::vec3					   p_bounds,
										unsigned long				   p_particle_count);
	void generate_random (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds, unsigned long p_particle_count);
	void set_generator_mode (e_generator_mode p_generator_mode);
	ParticleGenerator () : m_generator_mode (e_generator_mode::UNIFORM_DISTRIBUTION) {
	}
};

#endif /* SRC_PARTICLEGENERATOR_HPP_ */
