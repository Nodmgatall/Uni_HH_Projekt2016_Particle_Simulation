/*
 * ParticleGeneratorRandom2.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "GeneratorRandom.hpp"

GeneratorRandom::GeneratorRandom (s_options& p_options) : GeneratorBase (p_options) {
    m_stucture_name = "ParticleGeneratorRandom";
}

GeneratorRandom::~GeneratorRandom () {
}

void GeneratorRandom::generate (DatastructureBase* p_particles) {
    Benchmark::begin ("ParticleGeneratorRandom");
    std::srand (m_options.m_seed);
    for (unsigned long id = 0; id < m_options.m_particle_count; id++) {
        p_particles->add_particle (Vec3f ((data_type) std::rand (), (data_type) std::rand (), (data_type) std::rand ()) /
                                       (data_type) RAND_MAX * m_options.m_bounds,
                                   Vec3f ());
    }
    Benchmark::end ();
}
