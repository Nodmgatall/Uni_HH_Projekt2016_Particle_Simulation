#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include <functional>
#include <iostream>
#include <memory>

#include "LennardJonesAlgorithm.hpp"
#include "Particles.hpp"
#include "Definitions.hpp"

class ParticleSimulator {
	private:
	static short m_verbose_option;

	static std::shared_ptr<Particles> m_particles;
	// boundaries define box of particles
	static glm::vec3 m_bounds;

	static std::function<bool(std::shared_ptr<Particles>)> m_algorithm;

	public:
	static void parse_argv (int argc, char **p_argv);
	static void simulate ();
	static void init_particle_data (std::string   p_file_name,
									unsigned long p_particle_cnt,
									e_generator_mode p_generator_mode = GENERATOR_MODE_UNIFORM_DISTRIBUTION);
	static void find_simulation_algorithm ();
};

#endif
