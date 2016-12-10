/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGeneratorFactory.hpp"

ParticleGeneratorBase* ParticleGeneratorFactory::build (s_options& p_options) {
    switch (p_options.m_mode) {
        case e_generator_mode::RANDOM: {
            return new ParticleGeneratorRandom (p_options);
            break;
        }
        case e_generator_mode::SINGLE_OBJECT_MIDDLE: {
            return new ParticleGeneratorSingleObjectMiddle (p_options);
            break;
        }
        case e_generator_mode::GRID_DISTRIBUTION: {
            return new ParticleGeneratorGridDistribution (p_options);
            break;
        }
        case e_generator_mode::MULTIPLE_OBJECTS: {
            return new ParticleGeneratorMultipleObjects (p_options);
            break;
        }
        case e_generator_mode::RANDOM_UNIFORM: {
            return new ParticleGeneratorRandomUniform (p_options);
            break;
        }
        default: { throw GeneratorInvalidException (p_options.m_mode); }
    }
}
