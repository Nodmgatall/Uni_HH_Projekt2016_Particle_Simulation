/*
 * InputFactory.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "InputFactory.hpp"
InputBase* InputFactory::build (s_options& p_options, DatastructureBase& p_datastructure) {
    switch (p_options.m_input_type) {
        case e_input_type::FILE_CSV:
            return new FileReaderCSV (p_options, p_datastructure);
        case e_input_type::GENERATOR_RANDOM:
            return new GeneratorRandom (p_options, p_datastructure);
        case e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE:
            return new GeneratorSingleObjectMiddle (p_options, p_datastructure);
        case e_input_type::GENERATOR_GRID_DISTRIBUTION:
            return new GeneratorGridDistribution (p_options, p_datastructure);
        default:
            throw InputTypeInvalidException (p_options.m_input_type);
    }
}
