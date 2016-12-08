/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGeneratorFactory.hpp"

std::unique_ptr<ParticleGeneratorBase> ParticleGeneratorFactory::build (s_generator_options &p_options) {
    std::unique_ptr<ParticleGeneratorBase> result = 0;
    switch (p_options.m_mode) {
        case MULTIPLE_OBJECTS:
            break;
        case RANDOM:
            result = std::make_unique<ParticleGeneratorRandom> (p_options);
            break;
        case RANDOM_UNIFORM:
            break;
        case SINGLE_OBJECT_MIDDLE:
            break;
        case GRID_DISTRIBUTION:
            result = std::make_unique<ParticleGeneratorGridDistribution> (p_options);
            break;
        default:
            DEBUG_BEGIN << "ParticleGenerator :: error" << DEBUG_END;
            exit (1);
    }
    return (result);
}
