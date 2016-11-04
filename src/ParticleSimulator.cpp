#include <memory>

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "algorithms/DummyAlgorithm.hpp"
#include "datastructures/ParticlesBase.hpp"
#include "datastructures/ParticlesGrid.hpp"
#include "generators/ParticleGenerator.hpp"
#include "tools/Usage.hpp"
#include <memory>
#include <unistd.h>

std::shared_ptr<ParticlesBase> ParticleSimulator::m_particles;
glm::vec3					   ParticleSimulator::m_bounds;
std::map<e_particle_variable, bool> ParticleSimulator::m_write_modes;
unsigned long										ParticleSimulator::m_particle_count;
bool												ParticleSimulator::m_verbose;
unsigned int										ParticleSimulator::m_seed;
e_algorithm_type									ParticleSimulator::m_algorithm_type;
e_data_format										ParticleSimulator::m_data_format;
int													ParticleSimulator::m_write_fequency;
float												ParticleSimulator::m_run_time_limit;
float												ParticleSimulator::m_timestep;
bool												ParticleSimulator::m_dynamic_algorithm_use;
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
		  { "verbose", no_argument, 0, 'v' },
		  { "seed", required_argument, 0, 's' },
		  { "algorithm", required_argument, 0, 'a' },
		  { "format", required_argument, 0, 'F' },
		  { "particle_count", required_argument, 0, 'p' },
		  { "run_time_limit", required_argument, 0, 'l' },
		  { "timestep", required_argument, 0, 't' },

		  { "generator_mode", required_argument, 0, 'g' },

		  { "help", no_argument, 0, 'h' } };
	/*clang-format on */

	opterr = 0;
	int long_options;
	while ((argv_index = getopt_long (p_argc, p_argv, "vs:a:F:p:f:l:t:g:d:", &options[0], &long_options)) != -1) {
		/*
		if (strcmp (optarg, "-h") == 0 || strcmp (optarg, "--help") == 0) {
			// TODO:  Display help from option
		}
		*/
		std::cout << "lol" << std::endl;
		switch (argv_index) {
			case 0:

				if (strcmp (options[long_options].name, g_enum_to_string_map[VELOCITY]) == 0) {
					m_write_modes[VELOCITY] = std::stoi (optarg) == 0;
				}
				if (strcmp (options[long_options].name, g_enum_to_string_map[POSITION]) == 0) {
					m_write_modes[POSITION] = std::stoi (optarg) == 0;
				}
				if (strcmp (options[long_options].name, g_enum_to_string_map[ACCELERATION]) == 0) {
					m_write_modes[ACCELERATION] = std::stoi (optarg) == 0;
				}
				if (strcmp (options[long_options].name, g_enum_to_string_map[PARTICLE_TYPE]) == 0) {
					m_write_modes[PARTICLE_TYPE] = std::stoi (optarg) == 0;
				}

				break;
			case 'v':
				m_verbose = true;
				break;
			case 's':
				m_seed = std::stoi (optarg);
				break;
			case 'a':
				// set algorithm
				break;
			case 'F':
				break;

			case 'p':
				m_particle_count = std::stoi (optarg);
				break;
			case 'f':
				m_write_fequency = std::stoi (optarg);
				break;
			case 'l':
				m_run_time_limit = std::stoi (optarg);
				break;
			case 't':
				m_timestep = std::stof (optarg);
				break;

			case 'g':
				ParticleGenerator::set_generator_mode (optarg);
				break;
			case 'd':
				m_dynamic_algorithm_use = std::stoi (optarg) != 0;
				break;
			case 'h':
				print_usage_particle_sim ();
				exit (EXIT_SUCCESS);
				break;

			case '?':
				break;
		}
	}
	print_choosen_options ();
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
	char	   timeString[29];
	time (&current_time);
	time_info = localtime (&current_time);
	strftime (timeString, sizeof (timeString), "logdata/%Y-%m-%d_%H-%M-%S", time_info);
	mkdir ("logdata", 0700);
	mkdir (timeString, 0700);
	debug_file.open (std::string (timeString) + "/log.txt", std::fstream::out);
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

void ParticleSimulator::print_choosen_options () {
	std::cout << "Choosen Options:" << std::endl;
	std::cout << "verbose: " << m_verbose << std::endl;
	std::cout << "seed:    " << m_seed << std::endl;
	std::cout << "algorithm type: " << m_algorithm_type << std::endl;
	std::cout << "data fromat: " << m_data_format << std::endl;
	std::cout << "particle count " << m_particle_count << std::endl;
	std::cout << "write frequency: " << m_write_fequency << std::endl;
	std::cout << "run time limit: " << m_run_time_limit << std::endl;
	std::cout << "time step: " << m_timestep << std::endl;
	std::cout << "dynamic algo: " << m_dynamic_algorithm_use << std::endl;
	std::cout << "write mode ID: " << m_write_modes[ID] << std::endl;
	std::cout << "write mode POSITION: " << m_write_modes[POSITION] << std::endl;
	std::cout << "write mode VELOCITY: " << m_write_modes[VELOCITY] << std::endl;
	std::cout << "write mode ACCELERATION: " << m_write_modes[ACCELERATION] << std::endl;
	std::cout << "write mode PARTICLE_TYPE: " << m_write_modes[PARTICLE_TYPE] << std::endl;
}
