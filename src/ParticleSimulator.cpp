#include <memory>

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "datastructures/ParticlesBase.hpp"
#include "datastructures/ParticlesGrid.hpp"
#include "generators/ParticleGenerator.hpp"
#include "tools/Usage.hpp"

// functions
#include "algorithms/DummyAlgorithm.hpp"

std::shared_ptr<ParticlesBase> ParticleSimulator::m_particles;
glm::vec3					   ParticleSimulator::m_bounds;
short						   ParticleSimulator::m_verbose_option = 0;
std::map<e_particle_variable, bool> ParticleSimulator::m_write_modes;
unsigned long ParticleSimulator::m_particle_count;

std::function<bool(std::shared_ptr<ParticlesBase>)> ParticleSimulator::m_algorithm;

void ParticleSimulator::parse_argv (int p_argc, char **p_argv) {
	std::cout << "Reading console input" << std::endl;

	int argv_index;

	/*clang-format off */
	std::vector<option> options =
		{ { g_enum_to_string_map[VELOCITY], required_argument, 0, 0 },
		  { g_enum_to_string_map[POSITION], required_argument, 0, 0 },
		  { g_enum_to_string_map[ACCELERATION], required_argument, 0, 0 },
		  { g_enum_to_string_map[PARTICLE_TYPE], required_argument, 0, 0 },
		  { "generator_mode", required_argument, 0, 'g' },
		  { "timestep", required_argument, 0, 't' },
		  { "algorithm", required_argument, 0, 'a' },
		  { "particle_count", required_argument, 0, 'p' },
		  { "verbose", no_argument, 0, 'v' },
		  { "help", no_argument, 0, 'h' } };
	/*clang-format on */

	opterr = 0;
	int long_options;
	while ((argv_index = getopt_long (p_argc, p_argv, "htvd:", &options[0], &long_options)) != -1) {
		switch (argv_index) {
			case 0:
				if (strcmp (options[long_options].name, g_enum_to_string_map[VELOCITY]) == 0) {
				}
				if (strcmp (options[long_options].name, g_enum_to_string_map[POSITION]) == 0) {
				}
				if (strcmp (options[long_options].name, g_enum_to_string_map[ACCELERATION]) == 0) {
				}
				if (strcmp (options[long_options].name, g_enum_to_string_map[PARTICLE_TYPE]) == 0) {
				}
				if (strcmp (options[long_options].name, "generator_mode") == 0) {
				}
				if (strcmp (options[long_options].name, "timestep") == 0) {
				}
				if (strcmp (options[long_options].name, "algorithm") == 0) {
				}
				if (strcmp (options[long_options].name, "particle_count") == 0) {
				}
				std::cout << "lol" << std::endl;
				break;
			case 'h':
				print_usage_particle_sim ();
				exit (EXIT_SUCCESS);
				break;
			case 'v':
				m_verbose_option = 1;
				break;
			case 'd':
				// set dynamic algorithm choosing
				break;
			case 'a':
				// set algorithm
				break;
			case 'g':
				ParticleGenerator::set_generator_mode (optarg);
				break;
			case '?':
				if (optopt == 'd') {
					std::cout << "Option -d requires an argument " << std::endl;
				}
				exit (EXIT_FAILURE);
				break;
		}
	}
}
void ParticleSimulator::simulate () {
	std::cout << "Starting simulation" << std::endl;
	bool iteration_successfull = true;
	// TODO: set up simulation parameters according to later function parameters
	while (false && iteration_successfull == true) // TODO: fix while to end
												   // when simulation ended;
	{
		m_algorithm (m_particles);
	}
	std::cout << "Simulation finished" << std::endl;
}

void ParticleSimulator::init_particle_data (std::string p_file_name, unsigned long p_particle_cnt) {
	std::cout << "Initializing paticle data" << std::endl;
	m_particles = std::make_shared<ParticlesGrid> (p_particle_cnt);
	if (p_file_name.length () > 0) {
		std::cout << "loading from file: " << p_file_name << std::endl;
	} else {
		ParticleGenerator::generate (m_particles, m_bounds);
	}
}

void ParticleSimulator::find_simulation_algorithm () {
	std::cout << "Setting simulation algorithm" << std::endl;
	m_algorithm = dummy_algo;
}
