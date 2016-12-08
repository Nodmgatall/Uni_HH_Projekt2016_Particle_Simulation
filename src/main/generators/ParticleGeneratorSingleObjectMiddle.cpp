/*
 * ParticleGeneratorSingleObjectMiddle.cpp
 *
 *  Created on: 23.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorSingleObjectMiddle.hpp"

ParticleGeneratorSingleObjectMiddle::ParticleGeneratorSingleObjectMiddle (s_options &p_options)
: ParticleGeneratorBase (p_options) {
}

ParticleGeneratorSingleObjectMiddle::~ParticleGeneratorSingleObjectMiddle () {
}

void ParticleGeneratorSingleObjectMiddle::generate(
		std::shared_ptr<ParticlesBase> p_particles) {

    Benchmark::begin ("ParticleGeneratorSingleObjectMiddle");
    data_type    temp     = pow (m_options.m_particle_count, 1.0f / 3.0f);
	Vec3f delta = m_options.m_bounds / (temp - 1);
	Vec3f bounds_2 = m_options.m_bounds / 2;
    unsigned int tempInt  = temp;
    unsigned int x, y, z;
    for (x = 0; x <= tempInt; x++) {
        for (y = 0; y <= tempInt; y++) {
            for (z = 0; z <= tempInt; z++) {
                if (((x * tempInt) + y) * tempInt + z < m_options.m_particle_count) {
                    Vec3f direction = Vec3f (x, y, z) / Vec3f (tempInt * 0.5) - Vec3f (1);
                    direction       = direction * sqrt (direction.length ());
                    p_particles->add_particle ((bounds_2 + direction * bounds_2) * delta);
                }
            }
        }
    }
    Benchmark::end ();
}
