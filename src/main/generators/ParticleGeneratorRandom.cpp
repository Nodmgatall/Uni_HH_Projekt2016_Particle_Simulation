/*
 * ParticleGeneratorRandom2.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "ParticleGeneratorRandom.hpp"

ParticleGeneratorRandom::ParticleGeneratorRandom (s_options &p_options)
: ParticleGeneratorBase (p_options) {
}

ParticleGeneratorRandom::~ParticleGeneratorRandom () {
}

void ParticleGeneratorRandom::generate (std::shared_ptr<ParticlesBase> p_particles) {
    Benchmark::begin ("ParticleGeneratorRandom");
    std::srand (m_options.m_seed);
    for (unsigned long id = 0; id < m_options.m_particle_count; id++) {
        p_particles->add_particle (
            Vec3f ((data_type) std::rand (), (data_type) std::rand (), (data_type) std::rand ()) /
            (data_type) RAND_MAX * m_options.m_bounds);
    }
    Benchmark::end ();
}
