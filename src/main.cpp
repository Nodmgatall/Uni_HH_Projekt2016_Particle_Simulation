#include <iostream>
#define EXTERN
#define MAIN_CPP
#include "ParticleGenerator.hpp"
#include "ParticleSimulator.hpp"
#include "debug.hpp"
#include "definitions.hpp"
#include "Particles.hpp"

#include <memory>
int main () {

	std::string filename = "";
    ParticleSimulator::init_particle_data (filename);
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
