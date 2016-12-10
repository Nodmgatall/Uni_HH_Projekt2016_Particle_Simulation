/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGeneratorFactory.hpp"

std::unique_ptr<ParticleGeneratorBase> ParticleGeneratorFactory::build (s_options& p_options) {
    std::unique_ptr<ParticleGeneratorBase> result = 0;
    switch (p_options.m_mode) {
        case e_generator_mode::RANDOM: {
            result = std::make_unique<ParticleGeneratorRandom> (p_options);
            break;
        }
        case e_generator_mode::SINGLE_OBJECT_MIDDLE: {
            result = std::make_unique<ParticleGeneratorSingleObjectMiddle> (p_options);
            break;
        }
        case e_generator_mode::GRID_DISTRIBUTION: {
            result = std::make_unique<ParticleGeneratorGridDistribution> (p_options);
            break;
        }
        case e_generator_mode::MULTIPLE_OBJECTS: {
            throw GeneratorNotImplementedException (p_options.m_mode);
        }
        case e_generator_mode::RANDOM_UNIFORM: {
            throw GeneratorNotImplementedException (p_options.m_mode);
        }
        default: { throw GeneratorInvalidException (p_options.m_mode); }
    }
    return result;
}
