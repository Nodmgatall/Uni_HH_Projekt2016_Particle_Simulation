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

std::function<bool(std::shared_ptr<ParticlesBase>)> ParticleSimulator::m_algorithm;
std::shared_ptr<ParticlesBase>						ParticleSimulator::m_particles;
std::map<e_particle_variable, bool> ParticleSimulator::m_write_modes;
e_algorithm_type ParticleSimulator::m_algorithm_type = e_algorithm_type::LENNARD_JONES;
bool			 ParticleSimulator::m_autotuneing	= false;
glm::vec3		 ParticleSimulator::m_bounds		 = glm::vec3 (1, 1, 1);
e_data_format	ParticleSimulator::m_data_format	= e_data_format::CSV;
std::string		 ParticleSimulator::m_file_name		 = "";
e_generator_mode ParticleSimulator::m_generator_mode = e_generator_mode::UNIFORM_DISTRIBUTION;
unsigned long	ParticleSimulator::m_particle_count = 1;
float			 ParticleSimulator::m_run_time_limit = 1;
unsigned int	 ParticleSimulator::m_seed			 = std::time (0);
float			 ParticleSimulator::m_timestep		 = 1;
bool			 ParticleSimulator::m_verbose		 = false;
int				 ParticleSimulator::m_write_fequency = 1;

void ParticleSimulator::parse_argv (int p_argc, char **p_argv) {
	DEBUG_BEGIN << "ParameterParser :: starting" << DEBUG_END;
	++g_debug_stream;
	int argv_index;

	/*clang-format off */
	std::vector<option> options =
		{ { g_enum_particle_variable_to_string_map[VELOCITY], required_argument, 0, 0 },
		  { g_enum_particle_variable_to_string_map[POSITION], required_argument, 0, 0 },
		  { g_enum_particle_variable_to_string_map[ACCELERATION], required_argument, 0, 0 },
		  { g_enum_particle_variable_to_string_map[PARTICLE_TYPE], required_argument, 0, 0 },
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
		switch (argv_index) {
			case 0: {

				if (strcmp (options[long_options].name, g_enum_particle_variable_to_string_map[VELOCITY]) == 0) {
					m_write_modes[VELOCITY] = std::stoi (optarg) == 0;
				}
				if (strcmp (options[long_options].name, g_enum_particle_variable_to_string_map[POSITION]) == 0) {
					m_write_modes[POSITION] = std::stoi (optarg) == 0;
				}
				if (strcmp (options[long_options].name,
							g_enum_particle_variable_to_string_map[ACCELERATION]) == 0) {
					m_write_modes[ACCELERATION] = std::stoi (optarg) == 0;
				}
				if (strcmp (options[long_options].name,
							g_enum_particle_variable_to_string_map[PARTICLE_TYPE]) == 0) {
					m_write_modes[PARTICLE_TYPE] = std::stoi (optarg) == 0;
				}

				break;
			}
			case 'v': {
				m_verbose = true;
				break;
			}
			case 's': {
				m_seed = std::stoi (optarg);
				break;
			}
			case 'a': {
				// set algorithm
				break;
			}
			case 'F': {
				break;
			}
			case 'p': {
				m_particle_count = std::stoi (optarg);
				break;
			}
			case 'f': {
				m_write_fequency = std::stoi (optarg);
				break;
			}
			case 'l': {
				m_run_time_limit = std::stoi (optarg);
				break;
			}
			case 't': {
				m_timestep = std::stof (optarg);
				break;
			}
			case 'g': {
				bool found = false;
				for (auto iterator = g_enum_generator_mode_to_string_map.begin ();
					 iterator != g_enum_generator_mode_to_string_map.end ();
					 iterator++) {
					if (strcmp (iterator->second, optarg) == 0) {
						m_generator_mode = iterator->first;
						found			 = true;
						break;
					}
				}
				if (!found) {
					DEBUG_BEGIN << "ParameterParser :: error" << DEBUG_END;
					DEBUG_BEGIN << DEBUG_VAR (argv_index) << DEBUG_VAR (optarg) << DEBUG_END;
					exit (1);
				}
				break;
			}
			case 'd': {
				m_autotuneing = std::stoi (optarg) != 0;
				break;
			}
			case 'h': {
				print_usage_particle_sim ();
				exit (EXIT_SUCCESS);
				break;
			}

			case '?': {
				break;
			}
		}
	}
	--g_debug_stream;
	DEBUG_BEGIN << "ParameterParser :: finish" << DEBUG_END;

	print_choosen_options ();
}
void ParticleSimulator::print_header () {
	DEBUG_BEGIN << "=======================================================" << DEBUG_END;
	DEBUG_BEGIN << "                  Particle Simulation                  " << DEBUG_END;
	DEBUG_BEGIN << "=======================================================" << DEBUG_END;
	DEBUG_BEGIN << "            Benjamin Wanke, Oliver Heidmann            " << DEBUG_ENDL;
	DEBUG_BEGIN << "                      Supervisior                      " << DEBUG_END;
	DEBUG_BEGIN << "                    Philipp Neumann                    " << DEBUG_END;
	DEBUG_BEGIN << "=======================================================" << DEBUG_ENDL;
}
void ParticleSimulator::init (int argc, char **argv) {
	time_t	 current_time;
	struct tm *time_info;
	char	   timeString[29];
	time (&current_time);
	time_info = localtime (&current_time);
	strftime (timeString, sizeof (timeString), "logdata/%Y-%m-%d_%H-%M-%S", time_info);
	mkdir ("logdata", 0700);
	mkdir (timeString, 0700);
	g_debug_stream.open (std::string (timeString) + "/log.txt", std::fstream::out);
	print_header ();
	ParticleFileWriter::m_file_name_base = std::string (timeString) + "/data";
	parse_argv (argc, argv);
	init_particle_data ();
	find_simulation_algorithm ();
}
void ParticleSimulator::simulate () {
	DEBUG_BEGIN << "Starting simulation" << DEBUG_END;
	bool iteration_successfull = true;
	// TODO: set up simulation parameters according to later function parameters
	while (false && iteration_successfull == true) // TODO: fix while to end
												   // when simulation ended;
	{
		m_algorithm (m_particles);
	}
	ParticleFileWriter::saveData (m_particles);
	DEBUG_BEGIN << "Simulation finished" << DEBUG_END;
}

void ParticleSimulator::init_particle_data () {
	m_particles = std::make_shared<ParticlesGrid> ();
	if (m_file_name.length () > 0) {
		DEBUG_BEGIN << "loading from file: " << m_file_name << DEBUG_END;
	} else {
		ParticleGenerator::generate (m_particles, m_bounds, m_generator_mode, m_particle_count);
	}
}

void ParticleSimulator::find_simulation_algorithm () {
	DEBUG_BEGIN << "Setting simulation algorithm" << DEBUG_END;
	m_algorithm = dummy_algo;
}

void ParticleSimulator::print_choosen_options () {
	DEBUG_BEGIN << "Print-Options :: starting" << DEBUG_END;
	++g_debug_stream;
	// DEBUG_BEGIN << "algorithm     :" << m_algorithm << DEBUG_END;
	// DEBUG_BEGIN << "particles:" << m_particles << DEBUG_END;
	DEBUG_BEGIN << "algorithm_type : " << m_algorithm_type << DEBUG_END;
	DEBUG_BEGIN << "autotuneing    : " << m_autotuneing << DEBUG_END;
	DEBUG_BEGIN << "bounds         : " << m_bounds << DEBUG_END;
	DEBUG_BEGIN << "data_format    : " << m_data_format << DEBUG_END;
	DEBUG_BEGIN << "file_name      : " << m_file_name << DEBUG_END;
	DEBUG_BEGIN << "generator_mode : " << m_generator_mode << DEBUG_END;
	DEBUG_BEGIN << "particle_count : " << m_particle_count << DEBUG_END;
	DEBUG_BEGIN << "run_time_limit : " << m_run_time_limit << DEBUG_END;
	DEBUG_BEGIN << "seed           : " << m_seed << DEBUG_END;
	DEBUG_BEGIN << "timestep       : " << m_timestep << DEBUG_END;
	DEBUG_BEGIN << "verbose        : " << m_verbose << DEBUG_END;
	DEBUG_BEGIN << "write_fequency : " << m_write_fequency << DEBUG_END;
	DEBUG_BEGIN << "write_modes    : [ID";
	if (m_write_modes[POSITION]) {
		g_debug_stream << ", POSITION";
	}
	if (m_write_modes[VELOCITY]) {
		g_debug_stream << ", VELOCITY";
	}
	if (m_write_modes[ACCELERATION]) {
		g_debug_stream << ", ACCELERATION";
	}
	if (m_write_modes[PARTICLE_TYPE]) {
		g_debug_stream << ", PARTICLE_TYPE";
	}
	g_debug_stream << "]" << DEBUG_END;
	--g_debug_stream;
	DEBUG_BEGIN << "Print-Options :: starting" << DEBUG_END;
}
