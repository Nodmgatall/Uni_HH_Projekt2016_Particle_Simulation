/*
 * GeneratorRandom2.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_GENERATORRANDOM_HPP_
#define SRC_GENERATORS_GENERATORRANDOM_HPP_

#include "../InputBase.hpp"

class GeneratorRandom : public InputBase {
  public:
    GeneratorRandom (s_options& p_options, DatastructureBase& p_datastructure);
    virtual ~GeneratorRandom ();
    void initialize_datastructure ();
};

#endif /* SRC_GENERATORS_GENERATORRANDOM_HPP_ */
