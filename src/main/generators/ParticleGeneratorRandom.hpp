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
    ParticleGeneratorRandom (s_options& p_options);
    virtual ~ParticleGeneratorRandom ();
    void generate (DatastructureBase* p_particles);
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORRANDOM_HPP_ */
