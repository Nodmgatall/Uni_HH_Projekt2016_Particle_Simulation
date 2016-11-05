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
	std::map<e_particle_variable, bool> m_write_modes;
	bool			 m_verbose;
	unsigned int	 m_seed;
	e_algorithm_type m_algorithm_type;
	e_data_format	 m_data_format;
	unsigned long	 m_particle_count;
	int				 m_write_fequency;
	float			 m_run_time_limit;
	float			 m_timestep;
	bool			 m_dynamic_algorithm_use;
	std::string		 m_out_file_name;
	std::string		 m_in_file_name;

	std::unique_ptr<ParticleGenerator> m_particle_generator;

	std::shared_ptr<ParticlesBase> m_particles;
	// boundaries define box of particles
	glm::vec3 m_bounds;

	std::function<bool(std::shared_ptr<ParticlesBase>)> m_algorithm;
	void print_header ();

	float m_delta_t;

	public:
	ParticleSimulator (int argc, char **argv);
	void parse_argv (int argc, char **p_argv);
	void simulate ();
	void init_particle_data ();
	void find_simulation_algorithm ();
	void init ();
	void print_choosen_options ();
};

#endif
