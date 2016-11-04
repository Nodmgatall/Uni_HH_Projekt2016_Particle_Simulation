#include <iostream>
#define EXTERN
#define MAIN_CPP

#include <iostream>

#include "tools/Debug.hpp"
#include "Definitions.hpp"
#include "generators/ParticleGenerator.hpp"
#include "ParticleSimulator.hpp"

#include <memory>

void print_header () {
	std::cout << "========================================================" << std::endl;
	std::cout << "                 Particle Simulation" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "             Benjamin Wanke, Oliver Heidmann" << std::endl << std::endl;
	std::cout << "             Supervisior:" << std::endl;
	std::cout << "               Philipp Neumann" << std::endl;
	std::cout << "========================================================" << std::endl
			  << std::endl;
}
int main (int argc, char **argv) {

	print_header ();
	std::string filename = "";

	ParticleSimulator::parse_argv (argc, argv);
	ParticleSimulator::init_particle_data (filename, 10);
	ParticleSimulator::find_simulation_algorithm ();
	ParticleSimulator::simulate ();
	/*
	 for (unsigned int i = 0; i < particles->m_position.size (); i++) {
	 float x = particles->m_position[i].x;
	 float y = particles->m_position[i].y;
	 float z = particles->m_position[i].z;
	 DEBUG_BEGIN << DEBUG_VAR (x) << DEBUG_VAR (y) << DEBUG_VAR (z) << DEBUG_END;
	 }
	 */
}
