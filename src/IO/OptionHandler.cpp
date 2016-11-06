#include "OptionHandler.hpp"
#include "ConfigLoader.hpp"
#include "OptionsGenerator.hpp"
#include "OptionsSimulation.hpp"
#include <getopt.h>
#include <map>
#include <vector>
void OptionHandler::handle_options (int					 p_argc,
									char **				 p_argv,
									s_simulator_options *p_sim_options,
									s_generator_options *p_gen_options) {
	DEBUG_BEGIN << "ParameterParser :: starting" << DEBUG_END;
	g_debug_stream.indent ();
	int argv_index;

	bool		save_config  = false;
	bool		list_configs = false;
	std::string config_name  = "";

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

									// data structure
									{ "grid", no_argument, 0, 12 },
									{ "list", no_argument, 0, 13 },

									// Verbose option
									{ "verbose", no_argument, 0, 'v' },

									// Simulation parameters
									{ "seed", required_argument, 0, 's' },
									{ "particle_count", required_argument, 0, 'p' },
									{ "run_time_limit", required_argument, 0, 'l' },
									{ "timestep", required_argument, 0, 't' },

									// Misc
									{ "help", no_argument, 0, 'h' },
									{ "save_config", required_argument, 0, 31 },
									{ "list_configs", no_argument, 0, 30 }
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
			// Write modes
			case 0:
				p_sim_options->m_write_modes[VELOCITY] = !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;
			case 1:
				p_sim_options->m_write_modes[POSITION] = !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;
			case 2:
				p_sim_options->m_write_modes[ACCELERATION] =
					!(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;
			case 3:
				p_sim_options->m_write_modes[PARTICLE_TYPE] =
					!(isdigit (optarg[0]) && std::stoi (optarg) == 0);
				break;

			// Generator modes
			case 4:
				p_gen_options->m_mode = MULTIPLE_OBJECTS;
				generator_mode_set++;
				break;
			case 5:
				p_gen_options->m_mode = RANDOM;
				generator_mode_set++;
				break;
			case 6:
				p_gen_options->m_mode = RANDOM_UNIFORM;
				generator_mode_set++;
				break;
			case 7:
				p_gen_options->m_mode = SINGLE_OBJECT_MIDDLE;
				generator_mode_set++;
				break;
			case 8:
				p_gen_options->m_mode = UNIFORM_DISTRIBUTION;
				generator_mode_set++;
				break;

			// Algorithm types
			case 9:
				p_sim_options->m_algorithm_type = LENNARD_JONES;
				break;
			case 10:
				p_sim_options->m_algorithm_type = SMOTHED_PARTICLE_HYDRODYNAMICS;
				break;
			case 11:
				p_sim_options->m_algorithm_type = DISSIPATIVE_PARTICLE_DYNAMICS;
				break;

			// Data structures
			case 12:
				p_sim_options->m_data_structure = GRID;
				break;
			case 13:
				p_sim_options->m_data_structure = LIST;
			// config options
			case 30:
				list_configs = true;
				break;
			case 31:
				save_config = true;
				config_name = std::string (optarg);
			case 'v': {
				p_sim_options->m_verbose = true;
				break;
			}
			case 's': {
				p_sim_options->m_seed = std::stoi (optarg);
				break;
			}
			case 'p': {
				p_sim_options->m_particle_count = std::stoi (optarg);
				break;
			}
			case 'f': {
				p_sim_options->m_write_fequency = std::stoi (optarg);
				break;
			}
			case 'l': {
				p_sim_options->m_run_time_limit = std::stoi (optarg);
				break;
			}
			case 't': {
				p_sim_options->m_timestep = std::stof (optarg);
				break;
			}
			case 'd': {
				p_sim_options->m_autotuneing = true;

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
	if (list_configs == true) {
		ConfigLoader config_loader;
		config_loader.list_configs ();
		exit (EXIT_SUCCESS);
	}
	if (save_config == true) {
		ConfigLoader config_loader;
		config_loader.save_config (config_name, p_sim_options, p_gen_options);
	}
	g_debug_stream.unindent ();
	DEBUG_BEGIN << "ParameterParser :: finish" << DEBUG_END;

	print_choosen_options (p_sim_options, p_gen_options);
}
void OptionHandler::print_choosen_options (s_simulator_options *p_sim_options, s_generator_options *p_gen_options) {
	DEBUG_BEGIN << "Print-Options :: starting" << DEBUG_END;
	(void) p_gen_options;
	g_debug_stream.indent ();
	// DEBUG_BEGIN << "algorithm     :" << m_algorithm << DEBUG_END;
	// DEBUG_BEGIN << "particles:" << m_particles << DEBUG_END;
	macro_debug ("algorithp_sim_options->type : ", p_sim_options->m_algorithm_type);
	macro_debug ("autotuneing    : ", p_sim_options->m_autotuneing);
	DEBUG_BEGIN << "data_format    : " << p_sim_options->m_data_format << DEBUG_END;
	DEBUG_BEGIN << "file_in_name   : " << p_sim_options->m_in_file_name << DEBUG_END;
	DEBUG_BEGIN << "file_out_name  : " << p_sim_options->m_out_file_name << DEBUG_END;
	DEBUG_BEGIN << "particle_count : " << p_sim_options->m_particle_count << DEBUG_END;
	DEBUG_BEGIN << "run_time_limit : " << p_sim_options->m_run_time_limit << DEBUG_END;
	DEBUG_BEGIN << "seed           : " << p_sim_options->m_seed << DEBUG_END;
	DEBUG_BEGIN << "timestep       : " << p_sim_options->m_timestep << DEBUG_END;
	DEBUG_BEGIN << "verbose        : " << p_sim_options->m_verbose << DEBUG_END;
	DEBUG_BEGIN << "write_fequency : " << p_sim_options->m_write_fequency << DEBUG_END;
	DEBUG_BEGIN << "write_modes    : [ID";
	if (p_sim_options->m_write_modes[POSITION]) {
		g_debug_stream << ", POSITION";
	}
	if (p_sim_options->m_write_modes[VELOCITY]) {
		g_debug_stream << ", VELOCITY";
	}
	if (p_sim_options->m_write_modes[ACCELERATION]) {
		g_debug_stream << ", ACCELERATION";
	}
	if (p_sim_options->m_write_modes[PARTICLE_TYPE]) {
		g_debug_stream << ", PARTICLE_TYPE";
	}
	g_debug_stream << "]" << DEBUG_END;
	/*
	macro_debug("generator_mode :" , p_sim_options->particle_generator->get_generator_mode());
	macro_debug("data_structure :" , p_sim_options->particles->get_structure_name());
	*/
	g_debug_stream.unindent ();
	DEBUG_BEGIN << "Print-Options :: finish" << DEBUG_END;
}

void OptionHandler::print_usage_generation_mode () {
	std::cout << "Usage:" << std::endl;
	std::cout << "-g [generation_mode]" << std::endl;
}

void OptionHandler::print_usage_particle_sim () {
	std::cout << "Usage:" << std::endl;
	std::cout << "-g        set generation mode" << std::endl;
	std::cout << "-d        choose simulation algortihm dynamicly" << std::endl;
	std::cout << "-v        verbose " << std::endl;
	std::cout << "-a        set algorithm" << std::endl;
	std::cout << "-d        set dynamic algorithm" << std::endl;
}
