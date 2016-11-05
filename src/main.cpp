#define EXTERN
#define MAIN_CPP
#include "Definitions.hpp"
#include "ParticleSimulator.hpp"

int main (int argc, char **argv) {
	std::unique_ptr<ParticleSimulator> particle_simulator (new ParticleSimulator (argc, argv));
}
