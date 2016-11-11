/*
 * ParticleGeneratorRandom2.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorRandom.hpp"

ParticleGeneratorRandom::ParticleGeneratorRandom (s_generator_options *p_gen_options)
: ParticleGeneratorBase (p_gen_options) {
}

ParticleGeneratorRandom::~ParticleGeneratorRandom () {
}

void ParticleGeneratorRandom::generate (std::shared_ptr<ParticlesBase> p_particles,
                                        glm::vec3                      p_bounds,
                                        unsigned long                  p_particle_count) {
    DEBUG_BEGIN << "ParticleGeneratorRandom :: starting" << DEBUG_END;
    g_debug_stream.indent ();
    long seed = std::time (0);
    std::srand (seed); // TODO parameter bei programmstart
    for (unsigned long id = 0; id < p_particle_count; id++) {
        p_particles->add_particle (glm::vec3 (std::rand () / RAND_MAX, std::rand () / RAND_MAX, std::rand () / RAND_MAX) * p_bounds,
                                   glm::vec3 (0, 0, 0),
                                   glm::vec3 (0, 0, 0));
    }
    g_debug_stream.unindent ();
    DEBUG_BEGIN << "ParticleGeneratorRandom :: finish" << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
}
