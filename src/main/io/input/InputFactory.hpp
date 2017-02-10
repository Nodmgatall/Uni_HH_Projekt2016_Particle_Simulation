/*
 * InputFactory.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_IO_INPUT_INPUTFACTORY_HPP_
#define SRC_MAIN_IO_INPUT_INPUTFACTORY_HPP_
#include "Definitions.hpp"
#include "InputBase.hpp"
#include "datastructures/DatastructureBase.hpp"
#include "generators/GeneratorGridDistribution.hpp"
#include "generators/GeneratorRandom.hpp"
#include "generators/GeneratorSingleObjectMiddle.hpp"
#include "options/Options.hpp"
#include <io/input/file/FileInputCSV.hpp>
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
