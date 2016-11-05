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

/*clang-format off */
ParticleSimulator::ParticleSimulator (int argc, char **argv)
: m_algorithm (dummy_algo), m_algorithm_type (LENNARD_JONES), m_autotuneing (false),
  m_bounds (glm::vec3 (0, 0, 0)), m_data_format (CSV), m_delta_t (1), m_in_file_name (""),
  m_out_file_name (""), m_particle_count (0), m_particle_generator (new ParticleGenerator ()),
  m_particles (std::make_shared<ParticlesGrid> ()), m_run_time_limit (20), m_seed (0),
  m_timestep (0), m_verbose (false), m_write_fequency (1000),
  m_write_modes (
	  { { ID, true }, { VELOCITY, true }, { POSITION, true }, { ACCELERATION, true }, { PARTICLE_TYPE, true } }) {
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
/*clang-format off */

void ParticleSimulator::parse_argv (int p_argc, char **p_argv) {
	DEBUG_BEGIN << "ParameterParser :: starting" << DEBUG_END;
	++g_debug_stream;
	int argv_index;

	int algorithm_set	  = 0;
	int data_format_set	= 0;
	int generator_mode_set = 0;

	/*clang-format off */
	std::vector<option> options = { // Variable write options
									{ "write_velo", required_argument, 0, 0 },
									{ "write_pos", required_argument, 0, 1 },
									{ "write_accel", required_argument, 0, 2 },
									{ "write_type", required_argument, 0, 3 },

									// Generator modes
									{ "multiple_objects", no_argument, 0, 4 },
									{ "random", no_argument, 0, 5 },
									{ "random_uniform", no_argument, 0, 6 },
									{ "single_object_middle", no_argument, 0, 7 },
									{ "uniform_dist", no_argument, 0, 8 },


									// Algorithms
									{ "lennard", no_argument, 0, 9 },
									{ "smothed", no_argument, 0, 10 },
									{ "dissipative", no_argument, 0, 11 },

									// Verbose option
									{ "verbose", no_argument, 0, 'v' },

									// Simulation parameters
									{ "seed", required_argument, 0, 's' },
									{ "particle_count", required_argument, 0, 'p' },
									{ "run_time_limit", required_argument, 0, 'l' },
									{ "timestep", required_argument, 0, 't' },

									// Help
									{ "help", no_argument, 0, 'h' }
	};
	/*clang-format on */
	opterr = 0;
	int long_options;
	while ((argv_index = getopt_long (p_argc, p_argv, "vs:p:l:t:d", &options[0], &long_options)) != -1) {
		/*
		 if (strcmp (optarg, "-h") == 0 || strcmp (optarg, "--help") == 0) {
		 // TODO:  Display help from option
		 }
		 */
		switch (argv_index) {
			case 0:
				m_write_modes[VELOCITY] = !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;
			case 1:
				m_write_modes[POSITION] = !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;
			case 2:
				m_write_modes[ACCELERATION] = !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;
			case 3:
				m_write_modes[PARTICLE_TYPE] = !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;

			case 4:
				m_particle_generator->set_generator_mode (MULTIPLE_OBJECTS);
				generator_mode_set++;

				break;
			case 5:
				m_particle_generator->set_generator_mode (RANDOM);
				generator_mode_set++;
				break;
			case 6:
				m_particle_generator->set_generator_mode (RANDOM_UNIFORM);
				generator_mode_set++;
				break;
			case 7:
				m_particle_generator->set_generator_mode (SINGLE_OBJECT_MIDDLE);
				generator_mode_set++;
				break;
			case 8:
				m_particle_generator->set_generator_mode (UNIFORM_DISTRIBUTION);
				generator_mode_set++;
				break;
			case 'v': {
				m_verbose = true;
				break;
			}
			case 's': {
				m_seed = std::stoi (optarg);
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
			case 'd': {
				m_autotuneing = true;

				break;
			}
			case 'h': {
				print_usage_particle_sim ();
				exit (EXIT_SUCCESS);
				break;
			}
				{
					case '?':
						std::cout << "Error: unkown option: " << p_argv[optind - 1] << std::endl;
						exit (EXIT_SUCCESS);
						break;
				}
		}
	}
	if (generator_mode_set > 1) {
		std::cout << "Error: multiple generator modes set" << std::endl;
		exit (EXIT_SUCCESS);
	}
	if (algorithm_set > 1) {
		std::cout << "Error: multiple algorithms set" << std::endl;
		exit (EXIT_SUCCESS);
	}
	if (data_format_set > 1) {
		std::cout << "Error: multiple data formats set" << std::endl;
		exit (EXIT_SUCCESS);
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
	if (m_in_file_name.length () > 0) {
		DEBUG_BEGIN << "loading from file: " << m_in_file_name << DEBUG_END;
	} else {
		m_particle_generator->generate (m_particles, m_bounds, m_particle_count);
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
	DEBUG_BEGIN << "file_in_name   : " << m_in_file_name << DEBUG_END;
	DEBUG_BEGIN << "file_out_name  : " << m_out_file_name << DEBUG_END;
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
