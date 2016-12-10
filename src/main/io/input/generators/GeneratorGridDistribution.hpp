/*
 * GeneratorGridDistribution.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_GENERATORGRIDDISTRIBUTION_HPP_
#define SRC_GENERATORS_GENERATORGRIDDISTRIBUTION_HPP_

#include "GeneratorBase.hpp"

class GeneratorGridDistribution : public GeneratorBase {
  public:
    GeneratorGridDistribution (s_options& p_options);
    virtual ~GeneratorGridDistribution ();
    void generate (DatastructureBase* p_s);
};

#endif /* SRC_GENERATORS_GENERATORGRIDDISTRIBUTION_HPP_ */
