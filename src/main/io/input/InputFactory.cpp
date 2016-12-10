/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "InputFactory.hpp"

InputBase InputFactory::build (s_options& p_options) {
    switch (p_options.m_input_type) {
        case e_input_type::RANDOM:
            return GeneratorRandom (p_options);
        case e_input_type::SINGLE_OBJECT_MIDDLE:
            return GeneratorSingleObjectMiddle (p_options);
        case e_input_type::GRID_DISTRIBUTION:
            return GeneratorGridDistribution (p_options);
        case e_input_type::MULTIPLE_OBJECTS:
            return GeneratorMultipleObjects (p_options);
        case e_input_type::RANDOM_UNIFORM:
            return GeneratorRandomUniform (p_options);
        default:
            throw InputTypeInvalidException (p_options.m_input_type);
    }
}
