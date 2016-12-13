/*
 * Generator.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORFACTORY_HPP_
#define SRC_GENERATORFACTORY_HPP_

#include "Definitions.hpp"
#include "InputBase.hpp"
#include "datastructures/DatastructureBase.hpp"
#include "file/FileReaderCSV.hpp"
#include "generators/GeneratorGridDistribution.hpp"
#include "generators/GeneratorMultipleObjects.hpp"
#include "generators/GeneratorRandom.hpp"
#include "generators/GeneratorRandomUniform.hpp"
#include "generators/GeneratorSingleObjectMiddle.hpp"
#include "options/Options.hpp"

class InputFactory {
  public:
    /**
     * creates an input subclass based on the options.
     * @param p_options the options which specify which input to return
     * @param p_datastructure passed as parameter to the constructor for the input-base class
     * @return
     */
    static InputBase* build (s_options& p_options, DatastructureBase& p_datastructure);
};

#endif /* SRC_GENERATOR_HPP_ */
