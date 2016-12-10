/*
 * GeneratorSingleObjectMiddle.hpp
 *
 *  Created on: 23.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_
#define SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_

#include "GeneratorBase.hpp"
#include <math.h>

class GeneratorSingleObjectMiddle : public GeneratorBase {
  public:
    GeneratorSingleObjectMiddle (s_options& p_options);
    virtual ~GeneratorSingleObjectMiddle ();
    void generate (DatastructureBase* p_s);
};

#endif /* SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_ */
