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
	static std::function<bool(std::shared_ptr<ParticlesBase>)> m_algorithm;
	static e_algorithm_type									   m_algorithm_type;
	static bool												   m_autotuneing;
	static glm::vec3										   m_bounds;
	static e_data_format									   m_data_format;
	static float											   m_delta_t;
	static std::string										   m_file_name;
	static e_generator_mode									   m_generator_mode;
	static unsigned long									   m_particle_count;
	static std::shared_ptr<ParticlesBase>					   m_particles;
	static float											   m_run_time_limit;
	static unsigned int										   m_seed;
	static float											   m_timestep;
	static bool												   m_verbose;
	static int												   m_write_fequency;
	static std::map<e_particle_variable, bool> m_write_modes;

	static void print_header ();

	public:
	static void parse_argv (int argc, char **p_argv);
	static void simulate ();
	static void init_particle_data ();
	static void find_simulation_algorithm ();
	static void init (int argc, char **argv);
	static void print_choosen_options ();
};

#endif
