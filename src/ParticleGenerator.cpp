/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGenerator.hpp"

void ParticleGenerator::generate () {
    

    //enums defined in definitions
	switch (startParams.m_generatorMode) {
		case GENERATOR_MODE_FILE: {
			DEBUG_BEGIN << DEBUG_VAR (startParams.m_generatorMode) << DEBUG_END;
			exit (1);
		}
		case GENERATOR_MODE_MULTIPLE_SPHERES: {
			break;
		}
		case GENERATOR_MODE_RANDOM: {
			break;
		}
		case GENERATOR_MODE_RANDOM_UNIFORM: {
			break;
		}
		case GENERATOR_MODE_SPHERE: {
			break;
		}
		case GENERATOR_MODE_UNIFORM_DISTRIBUTION: {
			float temp = pow (startParams.m_particleCount, 1.0f / 3.0f);
			ParticleBounds bounds  = startParams.m_particleBounds;
			glm::vec3		   delta   = (bounds.m_p1 - bounds.m_p0) / (temp - 1);
			int			   tempInt = temp;
			for (int x = 0; x < tempInt; x++) {
				for (int y = 0; y < tempInt; y++) {
					for (int z = 0; z < tempInt; z++) {
						particles->m_position.push_back (
							glm::vec3 (x * delta.x, y * delta.y, z * delta.z));
						particles->m_velocities.push_back (glm::vec3 (0, 0, 0));
						particles->m_acceleration.push_back (glm::vec3 (0, 0, 0));
					}
				}
			}
			int particlesGenerated = pow (tempInt, 3);
			DEBUG_BEGIN << DEBUG_VAR (particlesGenerated) << DEBUG_END;
			break;
		}
		default:
			DEBUG_BEGIN << DEBUG_VAR (startParams.m_generatorMode) << DEBUG_END;
			exit (1);
	}
}
