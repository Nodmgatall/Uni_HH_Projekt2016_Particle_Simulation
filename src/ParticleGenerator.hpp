/*
 * ParticleGenerator.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEGENERATOR_HPP_
#define SRC_PARTICLEGENERATOR_HPP_

#include "Definitions.hpp"
#include "ParticlesBase.hpp"

class ParticleGenerator {
	private:
	static e_generator_mode m_mode;

	public:
	static void generate (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds);
	static void set_generator_mode (char *p_argument_mode);
	static void generate_uniform_distribution (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds);
	static void generate_random (std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds);
};

#endif /* SRC_PARTICLEGENERATOR_HPP_ */
