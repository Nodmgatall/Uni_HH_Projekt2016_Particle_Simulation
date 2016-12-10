/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "InputFactory.hpp"

InputBase InputFactory::build (s_options& p_options, DatastructureBase& p_datastructure) {
    switch (p_options.m_input_type) {
        case e_input_type::RANDOM:
            return GeneratorRandom (p_options, p_datastructure);
        case e_input_type::SINGLE_OBJECT_MIDDLE:
            return GeneratorSingleObjectMiddle (p_options, p_datastructure);
        case e_input_type::GRID_DISTRIBUTION:
            return GeneratorGridDistribution (p_options, p_datastructure);
        case e_input_type::MULTIPLE_OBJECTS:
            return GeneratorMultipleObjects (p_options, p_datastructure);
        case e_input_type::RANDOM_UNIFORM:
            return GeneratorRandomUniform (p_options, p_datastructure);
        default:
            throw InputTypeInvalidException (p_options.m_input_type);
    }
}
