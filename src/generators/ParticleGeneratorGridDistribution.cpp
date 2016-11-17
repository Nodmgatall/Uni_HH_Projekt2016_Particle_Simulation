/*
 * ParticleGeneratorGridDistribution.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorGridDistribution.hpp"

ParticleGeneratorGridDistribution::ParticleGeneratorGridDistribution (s_generator_options *p_gen_options)
: ParticleGeneratorBase (p_gen_options) {
}

ParticleGeneratorGridDistribution::~ParticleGeneratorGridDistribution () {
}

void ParticleGeneratorGridDistribution::generate (std::shared_ptr<ParticlesBase> p_particles,
                                                  vec3f                          p_bounds,
                                                  unsigned long                  p_particle_count) {

    Benchmark::begin ("ParticleGeneratorGridDistribution");
    float        temp    = pow (p_particle_count, 1.0f / 3.0f);
    vec3f        delta   = p_bounds / (temp - 1);
    unsigned int tempInt = temp;
    unsigned int x, y, z;
    for (x = 0; x <= tempInt; x++) {
        for (y = 0; y <= tempInt; y++) {
            for (z = 0; z <= tempInt; z++) {
                if (((x * tempInt) + y) * tempInt + z < p_particle_count) {
                    p_particles->add_particle (vec3f (x, y, z) * delta, vec3f (0, 0, 0));
                }
            }
        }
    }
    Benchmark::end ();
}
