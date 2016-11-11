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
                                                  glm::vec3                      p_bounds,
                                                  unsigned long                  p_particle_count) {

    DEBUG_BEGIN << "ParticleGeneratorGridDistribution :: starting" << DEBUG_END;
    g_debug_stream.indent ();
    float     temp    = pow (p_particle_count, 1.0f / 3.0f);
    glm::vec3 delta   = (glm::vec3 (0, 0, 0) - p_bounds) / (temp - 1);
    int       tempInt = temp;
    for (int x = 0; x < tempInt; x++) {
        for (int y = 0; y < tempInt; y++) {
            for (int z = 0; z < tempInt; z++) {
                p_particles->add_particle (glm::vec3 (x, y, z) * delta, glm::vec3 (0, 0, 0), glm::vec3 (0, 0, 0));
            }
        }
    }
    g_debug_stream.unindent ();
    DEBUG_BEGIN << "ParticleGeneratorGridDistribution :: finish" << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
}
