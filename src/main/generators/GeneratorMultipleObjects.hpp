/*
 * ParticleGeneratorMultipleObjects.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_
#define SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_

#include "GeneratorBase.hpp"

class GeneratorMultipleObjects : public GeneratorBase {
  public:
    GeneratorMultipleObjects (s_options& p_options);
    virtual ~GeneratorMultipleObjects ();
    void generate (DatastructureBase* p_particles);
};

#endif /* SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_ */
