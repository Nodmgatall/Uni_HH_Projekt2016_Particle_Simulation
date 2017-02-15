/*
 * AlgorithmFactory.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
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
