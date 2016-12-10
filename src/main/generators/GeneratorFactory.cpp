/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "GeneratorFactory.hpp"

GeneratorBase* GeneratorFactory::build (s_options& p_options) {
    switch (p_options.m_mode) {
        case e_generator_mode::RANDOM: {
            return new GeneratorRandom (p_options);
            break;
        }
        case e_generator_mode::SINGLE_OBJECT_MIDDLE: {
            return new GeneratorSingleObjectMiddle (p_options);
            break;
        }
        case e_generator_mode::GRID_DISTRIBUTION: {
            return new GeneratorGridDistribution (p_options);
            break;
        }
        case e_generator_mode::MULTIPLE_OBJECTS: {
            return new GeneratorMultipleObjects (p_options);
            break;
        }
        case e_generator_mode::RANDOM_UNIFORM: {
            return new GeneratorRandomUniform (p_options);
            break;
        }
        default: { throw GeneratorInvalidException (p_options.m_mode); }
    }
}
