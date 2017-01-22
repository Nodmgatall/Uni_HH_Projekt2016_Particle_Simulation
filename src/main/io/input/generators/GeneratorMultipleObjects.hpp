/*
 * ParticleGeneratorMultipleObjects.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_
#define SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_

#include "io/input/InputBase.hpp"

class GeneratorMultipleObjects : public InputBase {
  public:
    /**
     * constructor
     */
    GeneratorMultipleObjects (s_options& p_options, DatastructureBase& p_datastructure);
    /**
     * destructor
     */
    virtual ~GeneratorMultipleObjects ();
    void initialize_datastructure () override;
};

#endif /* SRC_MAIN_GENERATORS_PARTICLEGENERATORMULTIPLEOBJECTS_HPP_ */
