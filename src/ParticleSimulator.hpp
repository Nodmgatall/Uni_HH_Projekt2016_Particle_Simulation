#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include <functional>
#include <iostream>
#include <memory>

#include "LennardJonesAlgorithm.hpp"
#include "Particles.hpp"
#include "definitions.hpp"

class ParticleSimulator {
	private:
	static std::shared_ptr<Particles> m_particles;
	// boundaries define box of particles
	static glm::vec3 m_bounds;

	static std::function<bool(std::shared_ptr<Particles>)> m_algorithm;

	public:
	static void parse_argv (std::string p_argv);
	static void simulate ();
	static void init_particle_data (std::string p_file_name,
									e_generator_mode p_generator_mode = GENERATOR_MODE_UNIFORM_DISTRIBUTION);
	static void find_simulation_algorithm ();
};

#endif
