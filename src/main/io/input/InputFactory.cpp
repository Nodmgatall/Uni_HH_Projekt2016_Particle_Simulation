/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
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
        case e_input_type::GENERATOR_MULTIPLE_OBJECTS:
            return new GeneratorMultipleObjects (p_options, p_datastructure);
        case e_input_type::GENERATOR_RANDOM_UNIFORM:
            return new GeneratorRandomUniform (p_options, p_datastructure);
        default:
            throw InputTypeInvalidException (p_options.m_input_type);
    }
}
