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
                                                  vec3                           p_bounds,
                                                  unsigned long                  p_particle_count) {

    Benchmark::begin ("ParticleGeneratorGridDistribution");
    float temp    = pow (p_particle_count, 1.0f / 3.0f);
    vec3  delta   = p_bounds / (temp - 1);
    int   tempInt = temp;
    for (int x = 0; x < tempInt; x++) {
        for (int y = 0; y < tempInt; y++) {
            for (int z = 0; z < tempInt; z++) {
                p_particles->add_particle (vec3 (x, y, z) * delta, vec3 (0, 0, 0), vec3 (0, 0, 0));
            }
        }
    }
    Benchmark::end ();
}
