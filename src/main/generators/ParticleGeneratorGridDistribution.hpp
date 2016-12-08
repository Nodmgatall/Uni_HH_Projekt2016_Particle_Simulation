/*
 * ParticleGeneratorGridDistribution.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORGRIDDISTRIBUTION_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORGRIDDISTRIBUTION_HPP_

#include "ParticleGeneratorBase.hpp"

class ParticleGeneratorGridDistribution : public ParticleGeneratorBase {
    public:
    ParticleGeneratorGridDistribution (s_generator_options *p_gen_options);
    virtual ~ParticleGeneratorGridDistribution ();
    void generate (std::shared_ptr<ParticlesBase> p_particles, Vec3f &p_bounds, unsigned long &p_particle_count);
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORGRIDDISTRIBUTION_HPP_ */
