/*
 * ParticleGeneratorGridDistribution.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "GeneratorGridDistribution.hpp"

GeneratorGridDistribution::GeneratorGridDistribution (s_options& p_options, DatastructureBase& p_datastructure)
: InputBase (p_options, p_datastructure) {
    m_stucture_name = "GeneratorGridDistribution";
}

GeneratorGridDistribution::~GeneratorGridDistribution () {
}

void GeneratorGridDistribution::initialize_datastructure () {
    Benchmark::begin ("ParticleGeneratorGridDistribution");
    data_type     temp  = pow (m_options.m_particle_count, 1.0f / 3.0f);
    Vec3f         delta = m_options.m_bounds / (temp - 1.0f);
    unsigned int  x, y, z;
    unsigned int  tempInt = temp;
    unsigned long count   = 0;
    for (x = 0; x < tempInt; x++) {
        for (y = 0; y < tempInt; y++) {
            for (z = 0; z < tempInt; z++) {
                m_datastructure.add_particle (Vec3f (x, y, z) * delta, Vec3f ());
                count++;
            }
        }
    }
    if (m_options.m_particle_count != tempInt) {
        for (x = 0; x < tempInt; x++) {
            for (y = 0; y < tempInt; y++) {
                for (z = 0; z < tempInt; z++) {
                    if (count++ < m_options.m_particle_count) {
                        m_datastructure.add_particle (Vec3f (temp / 2.0 + x, y, z) * delta, Vec3f ());
                    }
                }
            }
        }
    }
    Benchmark::end ();
}
