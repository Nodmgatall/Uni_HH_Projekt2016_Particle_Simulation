/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticleGeneratorFactory"
#include "../../main/generators/GeneratorFactory.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_CASE (testParticleGeneratorRandom) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode          = e_generator_type::RANDOM;
    GeneratorBase generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator.get_stucture_name (), "ParticleGeneratorRandom");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorSingleObjectMiddle) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode          = e_generator_type::SINGLE_OBJECT_MIDDLE;
    GeneratorBase generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator.get_stucture_name (), "ParticleGeneratorSingleObjectMiddle");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorGridDistribution) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode          = e_generator_type::GRID_DISTRIBUTION;
    GeneratorBase generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator.get_stucture_name (), "ParticleGeneratorGridDistribution");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorMulipleObjects) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode          = e_generator_type::MULTIPLE_OBJECTS;
    GeneratorBase generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator.get_stucture_name (), "ParticleGeneratorMultipleObjects");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorRandomUniform) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode          = e_generator_type::RANDOM_UNIFORM;
    GeneratorBase generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator.get_stucture_name (), "ParticleGeneratorRandomUniform");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorError) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode = static_cast<e_generator_type> (-1);
    BOOST_CHECK_THROW (GeneratorFactory::build (options), GeneratorTypeInvalidException);
}
