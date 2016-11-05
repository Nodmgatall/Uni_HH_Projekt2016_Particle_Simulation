#define EXTERN
#define MAIN_CPP
#include "Definitions.hpp"
#include "ParticleSimulator.hpp"

int main (int argc, char **argv) {
	ParticleSimulator::init (argc, argv);
	ParticleSimulator::simulate ();
}
