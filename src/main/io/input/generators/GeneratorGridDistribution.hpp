/*
 * GeneratorGridDistribution.h
 *
 *  Created on:  11.11.2016
 *      Author: benjamin
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
