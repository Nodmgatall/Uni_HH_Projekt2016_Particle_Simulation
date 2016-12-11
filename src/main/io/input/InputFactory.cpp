/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "InputFactory.hpp"

InputBase* InputFactory::build (s_options& p_options, DatastructureBase& p_datastructure) {
    switch (p_options.m_input_type) {
        case e_input_type::CSV:
            return new FileReaderCSV (p_options, p_datastructure);
        case e_input_type::RANDOM:
            return new GeneratorRandom (p_options, p_datastructure);
        case e_input_type::SINGLE_OBJECT_MIDDLE:
            return new GeneratorSingleObjectMiddle (p_options, p_datastructure);
        case e_input_type::GRID_DISTRIBUTION:
            return new GeneratorGridDistribution (p_options, p_datastructure);
        case e_input_type::MULTIPLE_OBJECTS:
            return new GeneratorMultipleObjects (p_options, p_datastructure);
        case e_input_type::RANDOM_UNIFORM:
            return new GeneratorRandomUniform (p_options, p_datastructure);
        default:
            throw InputTypeInvalidException (p_options.m_input_type);
    }
}
