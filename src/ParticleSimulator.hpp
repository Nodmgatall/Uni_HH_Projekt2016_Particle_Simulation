#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/ParticleFileWriter.hpp"
#include "datastructures/ParticlesBase.hpp"
#include "generators/ParticleGenerator.hpp"
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

class ParticleSimulator {
	private:

	std::function<bool(std::shared_ptr<ParticlesBase>)> m_algorithm;
	e_algorithm_type									m_algorithm_type;
	bool												m_autotuneing;
	glm::vec3											m_bounds;
	e_data_format										m_data_format;
	float												m_delta_t;
	std::string											m_in_file_name;
	std::string											m_out_file_name;
	unsigned long										m_particle_count;
	std::unique_ptr<ParticleGenerator>					m_particle_generator;
	std::shared_ptr<ParticlesBase>						m_particles;
	float												m_run_time_limit;
	unsigned int										m_seed;
	float												m_timestep;
	bool												m_verbose;
	int													m_write_fequency;
	std::map<e_particle_variable, bool> m_write_modes;
	void print_header ();

	public:
	void parse_argv (int argc, char **p_argv);
	void simulate ();
	void init_particle_data ();
	void find_simulation_algorithm ();
	ParticleSimulator (int argc, char **argv);
	void print_choosen_options ();
};

#endif
