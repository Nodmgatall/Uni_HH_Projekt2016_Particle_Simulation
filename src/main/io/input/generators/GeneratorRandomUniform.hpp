/*
 * GeneratorRandomUniform.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_GENERATORS_GENERATORRANDOMUNIFORM_HPP_
#define SRC_MAIN_GENERATORS_GENERATORRANDOMUNIFORM_HPP_

#include "io/input/InputBase.hpp"

class GeneratorRandomUniform : public InputBase {
  public:
    /**
     * constructor
     */
    GeneratorRandomUniform (s_options& p_options, DatastructureBase& p_datastructure);
    /**
     * destructor
     */
    virtual ~GeneratorRandomUniform ();
    void initialize_datastructure () override;
};

#endif /* SRC_MAIN_GENERATORS_GENERATORRANDOMUNIFORM_HPP_ */
