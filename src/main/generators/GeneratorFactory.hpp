/*
 * Generator.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORFACTORY_HPP_
#define SRC_GENERATORFACTORY_HPP_

#include "../Definitions.hpp"
#include "../options/Options.hpp"
#include "GeneratorBase.hpp"
#include "GeneratorGridDistribution.hpp"
#include "GeneratorMultipleObjects.hpp"
#include "GeneratorRandom.hpp"
#include "GeneratorRandomUniform.hpp"
#include "GeneratorSingleObjectMiddle.hpp"
#include <cstdio>
#include <memory>
#include <unistd.h>

#include "../datastructures/DatastructureBase.hpp"

class GeneratorFactory {
  public:
    static GeneratorBase build (s_options& p_options);
};

#endif /* SRC_GENERATOR_HPP_ */
