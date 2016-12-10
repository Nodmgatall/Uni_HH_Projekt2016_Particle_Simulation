/*
 * GeneratorRandom2.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_GENERATORRANDOM_HPP_
#define SRC_GENERATORS_GENERATORRANDOM_HPP_

#include "GeneratorBase.hpp"

class GeneratorRandom : public GeneratorBase {
  public:
    GeneratorRandom (s_options& p_options);
    virtual ~GeneratorRandom ();
    void generate (DatastructureBase* p_s);
};

#endif /* SRC_GENERATORS_GENERATORRANDOM_HPP_ */
