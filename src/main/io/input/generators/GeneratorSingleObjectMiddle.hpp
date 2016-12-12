/*
 * GeneratorSingleObjectMiddle.hpp
 *
 *  Created on: 23.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_
#define SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_

#include "io/input/InputBase.hpp"
#include <math.h>

class GeneratorSingleObjectMiddle : public InputBase {
  public:
    GeneratorSingleObjectMiddle (s_options& p_options, DatastructureBase& p_datastructure);
    virtual ~GeneratorSingleObjectMiddle ();
    void initialize_datastructure ();
};

#endif /* SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_ */
