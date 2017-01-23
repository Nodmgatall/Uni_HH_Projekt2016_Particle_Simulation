/*
 * AlgorithmFactory.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */
#ifndef SRC_MAIN_ALGORITHMS_ALGORITHMFACTORY_HPP_
#define SRC_MAIN_ALGORITHMS_ALGORITHMFACTORY_HPP_
#include "AlgorithmBase.hpp"
#include "options/Options.hpp"
#include <algorithms/AlgorithmStoermerVerletLennardJones.hpp>
class AlgorithmFactory {
  public:
    /**
     * creates an Algorithm based on the options given as parameter
     * @param p_options the options which define toe resulting algorithm
     * @return an instance of the algorithm
     */
    static AlgorithmBase* build (s_options& p_options);
};
#endif /* SRC_MAIN_ALGORITHMS_ALGORITHMFACTORY_HPP_ */
