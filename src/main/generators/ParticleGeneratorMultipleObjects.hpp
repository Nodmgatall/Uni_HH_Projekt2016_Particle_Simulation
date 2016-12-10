/*
 * ParticleGeneratorMultipleObjects.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_
#define SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_

#include "ParticleGeneratorBase.hpp"

class ParticleGeneratorMultipleObjects : public ParticleGeneratorBase {
  public:
    ParticleGeneratorMultipleObjects (s_options& p_options);
    virtual ~ParticleGeneratorMultipleObjects ();
    void generate (DatastructureBase* p_particles);
};

#endif /* SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_ */
