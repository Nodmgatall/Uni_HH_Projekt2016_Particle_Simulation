#include <iostream>
#define EXTERN
#define MAIN_CPP
#include "debug.hpp"
#include "definitions.hpp"
#include "particles.hpp"
int main () {
	particles = new Particles ();
	generatorMode = GENERATOR_MODE_UNIFORM_DISTRIBUTION;
	if (generatorMode != GENERATOR_MODE_FILE) {
		ParticleGenerator::generate (generatorMode);
	}

	std::cout << "Hello World" << std::endl;
}
