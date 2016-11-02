#include <memory>

#include "Particles.hpp"
#include "ParticleSimulator.hpp"
#include "ParticleGenerator.hpp"
#include "definitions.hpp"

// functions
#include "DummyAlgorithm.hpp"

std::shared_ptr<Particles> ParticleSimulator::m_particles;
glm::vec3 ParticleSimulator::m_bounds;
std::function<bool(std::shared_ptr<Particles>)> ParticleSimulator::m_algorithm;

void ParticleSimulator::parse_argv (std::string p_argv) {
	std::cout << "Reading console input" << std::endl;
}
void ParticleSimulator::simulate () {
	bool iteration_successfull = true;
	// TODO: set up simulation parameters according to later function parameters
	while (false && iteration_successfull == true) // TODO: fix while to end
												   // when simulation ended;
	{
		m_algorithm (m_particles);
	}
}

void ParticleSimulator::init_particle_data (std::string p_file_name,
											e_generator_mode p_generator_mode ) {
	if (p_file_name.length () > 0) {
		std::cout << "loading from file: " << p_file_name << std::endl;
	} else {
		switch (p_generator_mode) {
			case 0:
				std::cout << "generating files throgh "
							 "method: " <<std::endl;
                ParticleGenerator::generate (m_particles, m_bounds);
				break;
			default:
				std::cout << "Error: file generation method not found" << std::endl;
		}
	}
}

void ParticleSimulator::find_simulation_algorithm () {
	std::cout << "Setting simulation algorithm" << std::endl;
	m_algorithm = dummy_algo;
}
