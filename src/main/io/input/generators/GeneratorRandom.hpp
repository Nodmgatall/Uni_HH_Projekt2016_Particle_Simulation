/*
 * GeneratorRandom2.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */
#ifndef SRC_GENERATORS_GENERATORRANDOM_HPP_
#define SRC_GENERATORS_GENERATORRANDOM_HPP_
#include "io/input/InputBase.hpp"
class GeneratorRandom : public InputBase {
  public:
    /**
     *constructor
     */
    GeneratorRandom (s_options& p_options, DatastructureBase& p_datastructure);
    /**
     * destructor
     */
    virtual ~GeneratorRandom ();
    void initialize_datastructure () override;
};
#endif /* SRC_GENERATORS_GENERATORRANDOM_HPP_ */
