/*
 * ParticleGeneratorRandomUniform.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_GENERATORS_PARTICLEGENERATORRANDOMUNIFORM_HPP_
#define SRC_MAIN_GENERATORS_PARTICLEGENERATORRANDOMUNIFORM_HPP_

#include "ParticleGeneratorBase.hpp"

class ParticleGeneratorRandomUniform : public ParticleGeneratorBase {
  public:
    ParticleGeneratorRandomUniform (s_options& p_options);
    virtual ~ParticleGeneratorRandomUniform ();
    void generate (ParticlesBase* p_particles);
};

#endif /* SRC_MAIN_GENERATORS_PARTICLEGENERATORRANDOMUNIFORM_HPP_ */
