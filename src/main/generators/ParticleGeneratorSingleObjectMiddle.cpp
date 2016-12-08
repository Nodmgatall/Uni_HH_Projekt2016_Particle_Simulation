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

void ParticleGeneratorSingleObjectMiddle::generate (std::shared_ptr<ParticlesBase> p_particles) {
    Benchmark::begin ("ParticleGeneratorSingleObjectMiddle");
    data_type     temp     = pow (m_options.m_particle_count, 1.0f / 3.0f);
    Vec3f         delta    = m_options.m_bounds / (temp - 1);
    Vec3f         bounds_2 = m_options.m_bounds / 2;
    unsigned int  tempInt  = temp;
    unsigned int  x, y, z;
    unsigned long count = 0;
    data_type     smallest_dimension =
        MIN (m_options.m_bounds.x, MIN (m_options.m_bounds.z, m_options.m_bounds.y));
    for (x = 0; x < tempInt; x++) {
        for (y = 0; y < tempInt; y++) {
            for (z = 0; z < tempInt; z++) {
                Vec3f direction = Vec3f (x, y, z) - bounds_2;
                if (direction.length () > smallest_dimension)
                    direction = direction / sqrt (direction.length ()) * (direction.length () - smallest_dimension);
                p_particles->add_particle ((bounds_2 + direction) * delta);
                count++;
            }
        }
    }
    if (m_options.m_particle_count != tempInt) {
        for (x = 0; x < tempInt; x++) {
            for (y = 0; y < tempInt; y++) {
                for (z = 0; z < tempInt; z++) {
                    if (count++ < m_options.m_particle_count) {
                        Vec3f direction = Vec3f (x, y, z) - bounds_2;
                        if (direction.length () > smallest_dimension)
                            direction = direction / sqrt (direction.length ()) *
                                        (direction.length () - smallest_dimension);
                        p_particles->add_particle ((bounds_2 + direction) * delta);
                    }
                }
            }
        }
    }
    Benchmark::end ();
}
