/*
 * ParticleGeneratorMultipleObjects.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_
#define SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_

#include "../InputBase.hpp"

class GeneratorMultipleObjects : public InputBase {
  public:
    GeneratorMultipleObjects (s_options& p_options, DatastructureBase& p_datastructure);
    virtual ~GeneratorMultipleObjects ();
    void initialize ();
};

#endif /* SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_ */
