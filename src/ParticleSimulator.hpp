#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/ParticleFileWriter.hpp"
#include "datastructures/ParticlesBase.hpp"
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

class ParticleSimulator {
	private:
	static short			m_verbose_option;
	static unsigned int		m_seed;
	static e_algorithm_type m_algorithm_type;
	static e_data_format	m_data_format;
	static unsigned long	m_particle_count;
	static std::map<e_particle_variable, bool> m_write_modes;

	static std::shared_ptr<ParticlesBase> m_particles;
	// boundaries define box of particles
	static glm::vec3 m_bounds;

	static std::function<bool(std::shared_ptr<ParticlesBase>)> m_algorithm;
	static void												   print_header ();

	public:
	static void parse_argv (int argc, char **p_argv);
	static void simulate ();
	static void init_particle_data (std::string p_file_name, unsigned long p_particle_cnt);
	static void find_simulation_algorithm ();
	static void init ();
};

#endif
