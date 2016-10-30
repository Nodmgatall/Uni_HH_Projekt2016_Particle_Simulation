#include <iostream>
#define EXTERN
#define MAIN_CPP
#include "ParticleGenerator.hpp"
#include "debug.hpp"
#include "definitions.hpp"
#include "particles.hpp"
int main () {
	particles = new Particles ();

	if (startParams.m_generatorMode != GENERATOR_MODE_FILE) {
		ParticleGenerator::generate ();
	}

	for (unsigned int i = 0; i < particles->m_position.size (); i++) {
		float x = particles->m_position[i].x;
		float y = particles->m_position[i].y;
		float z = particles->m_position[i].z;
		DEBUG_BEGIN << DEBUG_VAR (x) << DEBUG_VAR (y) << DEBUG_VAR (z) << DEBUG_END;
	}

	std::cout << "Hello World" << std::endl;
}
