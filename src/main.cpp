#include <iostream>
#define EXTERN
#define MAIN_CPP

#include <iostream>

#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "generators/ParticleGenerator.hpp"
#include "tools/Debug.hpp"

#include <memory>
#include <string>

int main (int argc, char **argv) {

	std::unique_ptr<ParticleSimulator> particle_simulator (new ParticleSimulator (argc, argv));
	/*
	ParticleSimulator::init ();
	ParticleSimulator::parse_argv (argc, argv);
	ParticleSimulator::init_particle_data (filename, 10);
	ParticleSimulator::find_simulation_algorithm ();
	ParticleSimulator::simulate ();
	*/
}
