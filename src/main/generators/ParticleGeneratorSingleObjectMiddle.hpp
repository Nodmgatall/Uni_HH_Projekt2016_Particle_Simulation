/*
 * ParticleGeneratorSingleObjectMiddle.hpp
 *
 *  Created on: 23.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORSINGLEOBJECTMIDDLE_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORSINGLEOBJECTMIDDLE_HPP_

#include "ParticleGeneratorBase.hpp"
#include <math.h>

class ParticleGeneratorSingleObjectMiddle : public ParticleGeneratorBase {
    public:
    ParticleGeneratorSingleObjectMiddle (s_generator_options &p_gen_options);
    virtual ~ParticleGeneratorSingleObjectMiddle ();
    void generate (std::shared_ptr<ParticlesBase> p_particles, Vec3f &p_bounds, unsigned long &p_particle_count);
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORSINGLEOBJECTMIDDLE_HPP_ */
