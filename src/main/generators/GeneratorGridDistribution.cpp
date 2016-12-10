/*
 * ParticleGeneratorGridDistribution.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "GeneratorGridDistribution.hpp"
#include "../tools/Debug.hpp"

GeneratorGridDistribution::GeneratorGridDistribution (s_options& p_options)
: GeneratorBase (p_options) {
    m_stucture_name = "ParticleGeneratorGridDistribution";
}

GeneratorGridDistribution::~GeneratorGridDistribution () {
}

void GeneratorGridDistribution::generate (DatastructureBase* p_particles) {
    Benchmark::begin ("ParticleGeneratorGridDistribution");
    data_type     temp  = pow (m_options.m_particle_count, 1.0f / 3.0f);
    Vec3f         delta = m_options.m_bounds / (temp - 1.0f);
    unsigned int  x, y, z;
    unsigned int  tempInt = temp;
    unsigned long count   = 0;
    for (x = 0; x < tempInt; x++) {
        for (y = 0; y < tempInt; y++) {
            for (z = 0; z < tempInt; z++) {
                p_particles->add_particle (Vec3f (x, y, z) * delta, Vec3f ());
                count++;
            }
        }
    }
    if (m_options.m_particle_count != tempInt) {
        for (x = 0; x < tempInt; x++) {
            for (y = 0; y < tempInt; y++) {
                for (z = 0; z < tempInt; z++) {
                    if (count++ < m_options.m_particle_count) {
                        p_particles->add_particle (Vec3f (temp / 2.0 + x, y, z) * delta, Vec3f ());
                    }
                }
            }
        }
    }
    Benchmark::end ();
}
