/*
 * AlgorithmFactory.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_ALGORITHMS_ALGORITHMFACTORY_HPP_
#define SRC_MAIN_ALGORITHMS_ALGORITHMFACTORY_HPP_

#include "../options/Options.hpp"
#include "AlgorithmBase.hpp"
#include "AlgorithmLennardJones.hpp"

class AlgorithmFactory {
  public:
    static AlgorithmBase* build (s_options& p_options);
};

#endif /* SRC_MAIN_ALGORITHMS_ALGORITHMFACTORY_HPP_ */
