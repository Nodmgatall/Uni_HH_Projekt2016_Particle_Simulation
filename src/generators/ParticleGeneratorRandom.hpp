/*
 * ParticleGeneratorRandom2.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORRANDOM_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORRANDOM_HPP_

#include "ParticleGeneratorBase.hpp"

class ParticleGeneratorRandom : public ParticleGeneratorBase {
    public:
    ParticleGeneratorRandom (s_generator_options *p_gen_options);
    virtual ~ParticleGeneratorRandom ();
    void generate (std::shared_ptr<ParticlesBase> p_particles, vec3 p_bounds, unsigned long p_particle_count);
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORRANDOM_HPP_ */
