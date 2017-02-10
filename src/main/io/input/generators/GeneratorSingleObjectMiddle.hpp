/*
 * GeneratorSingleObjectMiddle.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_
#define SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_
#include "io/input/InputBase.hpp"
#include <math.h>
class GeneratorSingleObjectMiddle : public InputBase {
  public:
    /**
     * constructor
     */
    GeneratorSingleObjectMiddle (s_options& p_options, DatastructureBase& p_datastructure);
    /**
     * destructor
     */
    virtual ~GeneratorSingleObjectMiddle ();
    void initialize_datastructure () override;
};
#endif /* SRC_GENERATORS_GENERATORSINGLEOBJECTMIDDLE_HPP_ */
