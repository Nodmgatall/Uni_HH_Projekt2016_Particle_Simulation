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

std::function<bool(std::shared_ptr<ParticlesBase>)> ParticleSimulator::m_algorithm;

void ParticleSimulator::parse_argv (int p_argc, char **p_argv) {
	std::cout << "Reading console input" << std::endl;

	int argv_index;
	opterr = 0;

	while ((argv_index = getopt (p_argc, p_argv, "hvd:")) != -1) {
		switch (argv_index) {
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

void ParticleSimulator::init_particle_data (std::string		 p_file_name,
											unsigned long	p_particle_cnt,
											e_generator_mode p_generator_mode) {
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
