#include <memory>

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "ParticleSimulator.hpp"
#include "Definitions.hpp"
#include "algorithms/DummyAlgorithm.hpp"
#include "datastructures/ParticlesBase.hpp"
#include "datastructures/ParticlesGrid.hpp"
#include "generators/ParticleGenerator.hpp"
#include "tools/Usage.hpp"
#include <memory>
#include <unistd.h>

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
void ParticleSimulator::print_header () {
	std::cout << "========================================================" << std::endl;
	std::cout << "                 Particle Simulation" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "             Benjamin Wanke, Oliver Heidmann" << std::endl << std::endl;
	std::cout << "             Supervisior:" << std::endl;
	std::cout << "               Philipp Neumann" << std::endl;
	std::cout << "========================================================" << std::endl
			  << std::endl;
}
void ParticleSimulator::init () {
	time_t	 current_time;
	struct tm *time_info;
	char	   timeString[26];
	time (&current_time);
	time_info = localtime (&current_time);
	strftime (timeString, sizeof (timeString), "logdata/%Y-%m-%d_%H%M%S", time_info);
	mkdir ("logdata", 0700);
	mkdir (timeString, 0700);
	debug_file.open (std::string (timeString) + "/log.txt", std::fstream::out);
	std::cout.rdbuf (debug_file.rdbuf ());
	ParticleFileWriter::m_file_name_base = std::string (timeString) + "/data";
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
	ParticleFileWriter::saveData (m_particles);
	std::cout << "Simulation finished" << std::endl;
}

void ParticleSimulator::init_particle_data (std::string p_file_name, unsigned long p_particle_cnt) {
	std::cout << "Initializing paticle data" << std::endl;
	DEBUG_BEGIN << DEBUG_VAR (p_particle_cnt) << DEBUG_END;
	m_particles = std::make_shared<ParticlesGrid> ();
	if (p_file_name.length () > 0) {
		std::cout << "loading from file: " << p_file_name << std::endl;
	} else {
		ParticleGenerator::generate (m_particles, m_bounds, p_particle_cnt);
	}
}

void ParticleSimulator::find_simulation_algorithm () {
	std::cout << "Setting simulation algorithm" << std::endl;
	m_algorithm = dummy_algo;
}
