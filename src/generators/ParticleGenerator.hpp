/*
 * ParticleGenerator.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEGENERATOR_HPP_
#define SRC_PARTICLEGENERATOR_HPP_

#include "../Definitions.hpp"
#include "../IO/OptionsGenerator.hpp"
#include "../datastructures/ParticlesBase.hpp"

class ParticleGenerator {
	private:
	s_generator_options *m_options;

	public:
	ParticleGenerator (s_generator_options *p_gen_options);
	void generate (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds, unsigned long p_particle_count);
	void generate_uniform_distribution (std::shared_ptr<ParticlesBase> p_particles,
										glm::vec3					   p_bounds,
										unsigned long				   p_particle_count);
	void generate_random (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds, unsigned long p_particle_count);
	e_generator_mode get_generator_mode ();
};

#endif /* SRC_PARTICLEGENERATOR_HPP_ */
