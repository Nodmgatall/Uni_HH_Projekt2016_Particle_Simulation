/*
 * ParticleGeneratorSingleObjectMiddle.cpp
 *
 *  Created on: 23.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorSingleObjectMiddle.hpp"

ParticleGeneratorSingleObjectMiddle::ParticleGeneratorSingleObjectMiddle (s_options& p_options)
: ParticleGeneratorBase (p_options) {
    m_stucture_name = "ParticleGeneratorSingleObjectMiddle";
}

ParticleGeneratorSingleObjectMiddle::~ParticleGeneratorSingleObjectMiddle () {
}

void ParticleGeneratorSingleObjectMiddle::generate (ParticlesBase* p_particles) {
    Benchmark::begin ("ParticleGeneratorSingleObjectMiddle");
    data_type     temp     = pow (m_options.m_particle_count, 1.0f / 3.0f);
    Vec3f         bounds_2 = m_options.m_bounds / 2;
    unsigned int  tempInt  = temp;
    unsigned int  x, y, z;
    unsigned long count = 0;
    data_type     smallest_dimension_2 =
        MIN (m_options.m_bounds.x, MIN (m_options.m_bounds.z, m_options.m_bounds.y)) / 2.0;
    for (x = 0; x < tempInt; x++) {
        for (y = 0; y < tempInt; y++) {
            for (z = 0; z < tempInt; z++) {
                Vec3f     direction = Vec3f (x, y, z) - bounds_2;
                data_type length    = direction.length ();
                if (length > smallest_dimension_2) {
                    direction = direction / length * (length - smallest_dimension_2);
                }
                p_particles->add_particle (bounds_2 + direction);
                count++;
            }
        }
    }
    if (m_options.m_particle_count != tempInt) {
        for (x = 0; x < tempInt; x++) {
            for (y = 0; y < tempInt; y++) {
                for (z = 0; z < tempInt; z++) {
                    if (count++ < m_options.m_particle_count) {
                        Vec3f     direction = Vec3f (x, y, z) - bounds_2;
                        data_type length    = direction.length ();
                        if (length > smallest_dimension_2) {
                            direction = direction / length * (length - smallest_dimension_2);
                        }
                        p_particles->add_particle (bounds_2 + direction);
                    }
                }
            }
        }
    }
    Benchmark::end ();
}
