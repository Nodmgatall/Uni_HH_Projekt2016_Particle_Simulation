/*
 * ParticleGeneratorBase.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_

#include "../Definitions.hpp"
#include "../IO/OptionsGenerator.hpp"
#include "../datastructures/ParticlesBase.hpp"
class ParticleGeneratorBase {
    protected:
    s_generator_options *m_options;

    public:
    virtual void generate (std::shared_ptr<ParticlesBase> p_particles,
                           vec3f                          &p_bounds,
                           unsigned long                  &p_particle_count) = 0;
    e_generator_mode get_generator_mode ();
    ParticleGeneratorBase (s_generator_options *p_gen_options);
    virtual ~ParticleGeneratorBase ();
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_ */
