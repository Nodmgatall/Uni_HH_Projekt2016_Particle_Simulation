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

ParticleSimulator::ParticleSimulator (int argc, char **argv)
: m_write_modes (
	  { { ID, true }, { VELOCITY, true }, { POSITION, true }, { ACCELERATION, true }, { PARTICLE_TYPE, true } }),
  m_verbose (false), m_seed (0), m_algorithm_type (NO_ALGORITHM), m_data_format (NO_FORMAT),
  m_particle_count (0), m_write_fequency (1000), m_run_time_limit (20), m_timestep (0),
  m_dynamic_algorithm_use (false), m_out_file_name (""), m_in_file_name (""),
  m_particle_generator (new ParticleGenerator ()), m_particles (std::make_shared<ParticlesGrid> ()),
  m_algorithm (dummy_algo)

{

	init ();
	parse_argv (argc, argv);
	init_particle_data ();
	find_simulation_algorithm ();
	simulate ();
}

void ParticleSimulator::parse_argv (int p_argc, char **p_argv) {
	std::cout << "Reading console input" << std::endl;

	int argv_index;

    int algorithm_set = 0;
    int data_format_set = 0;
    int generator_mode_set = 0;

	/*clang-format off */
	std::vector<option> options = { 
                                    //Variable write options
                                    { "write_velo", required_argument, 0, 0 },
									{ "write_pos", required_argument, 0, 1 },
									{ "write_accel", required_argument, 0, 2 },
									{ "write_type", required_argument, 0, 3 },

                                    //Generator modes
									{ "multiple_objects", no_argument, 0, 4 },
									{ "random", no_argument, 0, 5 },
									{ "random_uniform", no_argument, 0, 6 },
									{ "single_object_middle", no_argument, 0, 7 },
									{ "uniform_distibution", no_argument, 0, 8 },
                                    
                                    //Algorithms
                                    { "lennard",  no_argument , 0, 9},
                                    { "smothed", no_argument , 0, 10},
                                    { "dissipative", no_argument, 0, 11},

                                    //Verbose option
									{ "verbose", no_argument, 0, 'v' },
									
                                    //Simulation parameters
                                    { "seed", required_argument, 0, 's' },
									{ "particle_count", required_argument, 0, 'p' },
									{ "run_time_limit", required_argument, 0, 'l' },
									{ "timestep", required_argument, 0, 't' },

                                    //Help
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
                m_particle_generator->set_generator_mode(MULTIPLE_OBJECTS);
                generator_mode_set++;
				break;
			case 5:
                m_particle_generator->set_generator_mode(RANDOM);
                generator_mode_set++;
				break;
			case 6:
                m_particle_generator->set_generator_mode(RANDOM_UNIFORM);
                generator_mode_set++;
				break;
			case 7:
                m_particle_generator->set_generator_mode(SINGLE_OBJECT_MIDDLE);
                generator_mode_set++;
				break;
			case 8:
                m_particle_generator->set_generator_mode(UNIFORM_DISTRIBUTION);
                generator_mode_set++;
				break;

			case 'v':
				m_verbose = true;
				break;
			case 's':
				m_seed = std::stoi (optarg);
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
    if(generator_mode_set > 1)
    {
        std::cout << "Error: multiple generator modes set" << std::endl;
        exit(EXIT_SUCCESS);
    }
    if(algorithm_set > 1)
    {
        std::cout << "Error: multiple algorithms set" << std::endl;
        exit(EXIT_SUCCESS);
    }
    if(data_format_set > 1)
    {
        std::cout << "Error: multiple data formats set" << std::endl;
        exit(EXIT_SUCCESS);
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

void ParticleSimulator::init_particle_data () {
	std::cout << "Initializing paticle data" << std::endl;
	DEBUG_BEGIN << DEBUG_VAR (m_particle_count) << DEBUG_END;
	m_particles = std::make_shared<ParticlesGrid> ();
	if (m_out_file_name.length () > 0) {
		std::cout << "loading from file: " << m_out_file_name << std::endl;
	} else {
		m_particle_generator->generate (m_particles, m_bounds);
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
	m_particle_generator->print_generator_mode ();
}
