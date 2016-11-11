/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGeneratorFactoryFactory.hpp"

std::unique_ptr<ParticleGeneratorBase> ParticleGeneratorFactory::build (s_generator_options *p_options) {
    std::unique_ptr<ParticleGeneratorBase> result = 0;
    DEBUG_BEGIN << "ParticleGeneratorFactory :: starting" << DEBUG_END;
    g_debug_stream.indent ();
    DEBUG_BEGIN << "method :: " << p_options->m_mode << DEBUG_END;
    switch (p_options->m_mode) {
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
    g_debug_stream.unindent ();
    DEBUG_BEGIN << "ParticleGeneratorFactory :: finish" << DEBUG_END;
    return result;
}
