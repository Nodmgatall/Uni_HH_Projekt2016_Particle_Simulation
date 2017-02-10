/*
 * OutputFactory.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_IO_OUTPUT_OUTPUTFACTORY_HPP_
#define SRC_MAIN_IO_OUTPUT_OUTPUTFACTORY_HPP_
#include "Definitions.hpp"
#include "OutputBase.hpp"
#include "io/output/VoidWriter.hpp"
#include "io/output/file/FileOutputCSV.hpp"
#include "options/Options.hpp"
class OutputFactory {
  public:
    /**
     * creates an Output subclass based on the options.
     * @param p_options the options which specify which Output to return
     * @return
     */
    static OutputBase* build (s_options& p_options);
};
#endif /* SRC_GENERATOR_HPP_ */
