#include <memory>

#include <unistd.h>

#include "ParticleGenerator.hpp"
#include "ParticleSimulator.hpp"
#include "Particles.hpp"
#include "definitions.hpp"
#include "Usage.hpp"

// functions
#include "DummyAlgorithm.hpp"

std::shared_ptr<Particles> ParticleSimulator::m_particles;
glm::vec3				   ParticleSimulator::m_bounds;
short					   ParticleSimulator::m_verbose_option = 0;

std::function<bool(std::shared_ptr<Particles>)> ParticleSimulator::m_algorithm;

void ParticleSimulator::parse_argv (int p_argc, char **p_argv) {
	std::cout << "Reading console input" << std::endl;

	int argv_index;
	opterr = 0;

	while ((argv_index = getopt (p_argc, p_argv, "hvd:")) != -1) {
		switch (argv_index) {
            case 'h':
                print_usage_particle_sim();
                exit(EXIT_SUCCESS);
			case 'v':
				m_verbose_option = 1;
            case 'd':
                //set dynamic algorithm choosing
                break;
            case 'a':
                //set algorithm
                break;
			case 'g':
				ParticleGenerator::set_generator_mode (optarg);
                break;
			case '?':
				if (optopt == 'd') {
					std::cout << "Option -c requires an argument " << std::endl;
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

void ParticleSimulator::init_particle_data (std::string		 p_file_name,
											unsigned long	p_particle_cnt,
											e_generator_mode p_generator_mode) {
	std::cout << "Initializing paticle data" << std::endl;
	m_particles = std::make_shared<Particles> (p_particle_cnt);
	if (p_file_name.length () > 0) {
		std::cout << "loading from file: " << p_file_name << std::endl;
	} else {
		switch (p_generator_mode) {
			case GENERATOR_MODE_UNIFORM_DISTRIBUTION:
				std::cout << "Starting generation" << std::endl;
				ParticleGenerator::generate (m_particles, m_bounds);
				break;
			default:
				std::cout << "  Error: file generation method not found" << std::endl;
		}
	}
}

void ParticleSimulator::find_simulation_algorithm () {
	std::cout << "Setting simulation algorithm" << std::endl;
	m_algorithm = dummy_algo;
}
