#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/ParticleFileWriter.hpp"
#include "datastructures/ParticlesBase.hpp"
#include <functional>
#include <iostream>
#include <memory>

class ParticleSimulator {
	private:
	static short											   m_verbose_option;
	static glm::vec3										   m_bounds;
	static std::function<bool(std::shared_ptr<ParticlesBase>)> m_algorithm;
	static void												   print_header ();

	public:
	static std::shared_ptr<ParticlesBase> m_particles;
	static void parse_argv (int argc, char **p_argv);
	static void simulate ();
	static void init_particle_data (std::string   p_file_name,
									unsigned long p_particle_cnt,
									e_generator_mode p_generator_mode = GENERATOR_MODE_UNIFORM_DISTRIBUTION);
	static void find_simulation_algorithm ();
	static void init ();
};

#endif
