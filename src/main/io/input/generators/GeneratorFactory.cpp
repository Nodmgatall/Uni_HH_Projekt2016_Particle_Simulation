/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "GeneratorFactory.hpp"

GeneratorBase GeneratorFactory::build (s_options& p_options) {
    switch (p_options.m_mode) {
        case e_generator_type::RANDOM:
            return GeneratorRandom (p_options);
        case e_generator_type::SINGLE_OBJECT_MIDDLE:
            return GeneratorSingleObjectMiddle (p_options);
        case e_generator_type::GRID_DISTRIBUTION:
            return GeneratorGridDistribution (p_options);
        case e_generator_type::MULTIPLE_OBJECTS:
            return GeneratorMultipleObjects (p_options);
        case e_generator_type::RANDOM_UNIFORM:
            return GeneratorRandomUniform (p_options);
        default:
            throw GeneratorTypeInvalidException (p_options.m_mode);
    }
}
