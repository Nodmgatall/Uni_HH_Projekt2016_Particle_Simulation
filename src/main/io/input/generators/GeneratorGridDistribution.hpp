/*
 * GeneratorGridDistribution.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_GENERATORS_GENERATORGRIDDISTRIBUTION_HPP_
#define SRC_GENERATORS_GENERATORGRIDDISTRIBUTION_HPP_
#include "io/input/InputBase.hpp"
class GeneratorGridDistribution : public InputBase {
  public:
    /**
     * constructor
     */
    GeneratorGridDistribution (s_options& p_options, DatastructureBase& p_datastructure);
    /**
     * destructor
     */
    virtual ~GeneratorGridDistribution ();
    void initialize_datastructure () override;
};
#endif /* SRC_GENERATORS_GENERATORGRIDDISTRIBUTION_HPP_ */
