/*
 * ParticleGeneratorGridDistribution.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorGridDistribution.hpp"
#include "../tools/Debug.hpp"

ParticleGeneratorGridDistribution::ParticleGeneratorGridDistribution (s_options &p_options)
: ParticleGeneratorBase (p_options) {
}

ParticleGeneratorGridDistribution::~ParticleGeneratorGridDistribution () {
}

void ParticleGeneratorGridDistribution::generate (std::shared_ptr<ParticlesBase> p_particles) {
    Benchmark::begin ("ParticleGeneratorGridDistribution");
    data_type    temp    = pow (m_options.m_particle_count, 1.0f / 3.0f);
    Vec3f        delta   = m_options.m_bounds / (temp - 1.0f);
    unsigned int tempInt = temp;
    unsigned int x, y, z;
    if (m_options.m_particle_count != tempInt) {
        DEBUG_BEGIN << "Warning: generated only " << tempInt * tempInt * tempInt << " particles." << DEBUG_END;
        DEBUG_BEGIN << "3rd root of " << m_options.m_particle_count << " is not a Natural number" << DEBUG_END;
    }
    for (x = 0; x < tempInt; x++) {
        for (y = 0; y < tempInt; y++) {
            for (z = 0; z < tempInt; z++) {
                if (((x * tempInt) + y) * tempInt + z < m_options.m_particle_count) {
                    p_particles->add_particle (Vec3f (x, y, z) * delta);
                }
            }
        }
    }
    Benchmark::end ();
}
