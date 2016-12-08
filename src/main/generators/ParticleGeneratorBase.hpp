/*
 * ParticleGeneratorBase.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_

#include "../Definitions.hpp"
#include "../IO/Options.hpp"
#include "../datastructures/ParticlesBase.hpp"
class ParticleGeneratorBase {
    protected:
    s_options &m_options;

    public:
    virtual void generate (std::shared_ptr<ParticlesBase> p_particles) = 0;
    ParticleGeneratorBase (s_options &p_options);
    virtual ~ParticleGeneratorBase ();
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_ */
