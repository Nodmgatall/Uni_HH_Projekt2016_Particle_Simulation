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
	static e_generator_mode m_mode;
static int m_count;

public:
	static void generate(std::shared_ptr<ParticlesBase> p_particles,
			glm::vec3 p_bounds, int p_count);
	static void set_generator_mode(char *p_argument_mode);
	static void set_generator_count(char *p_argument_count);
	static void generate_uniform_distribution(
			std::shared_ptr<ParticlesBase> p_particles, glm::vec3 p_bounds, int p_count);
	static void generate_random(std::shared_ptr<ParticlesBase> p_particles,
			glm::vec3 p_bounds, int p_count);

};

#endif /* SRC_PARTICLEGENERATOR_HPP_ */
