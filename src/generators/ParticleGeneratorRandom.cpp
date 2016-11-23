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
                                        vec3f                          &p_bounds,
                                        unsigned long                  &p_particle_count) {
    Benchmark::begin ("ParticleGeneratorRandom");
    std::srand (m_options->m_seed);
    for (unsigned long id = 0; id < p_particle_count; id++) {
        p_particles->add_particle (vec3f (std::rand () / RAND_MAX, std::rand () / RAND_MAX, std::rand () / RAND_MAX) * p_bounds,
                                   vec3f (0, 0, 0));
    }
    Benchmark::end ();
}
