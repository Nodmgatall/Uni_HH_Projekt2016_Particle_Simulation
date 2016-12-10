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

BOOST_AUTO_TEST_CASE (testGeneratorNotImplementedException) {
    GeneratorNotImplementedException exception (e_generator_mode::GRID_DISTRIBUTION);
    BOOST_CHECK_EQUAL (std::string (exception.what ()),
                       "generator mode ( 4 ) is not (fully) implemented");
}
BOOST_AUTO_TEST_CASE (testGeneratorInvalidException) {
    GeneratorInvalidException exception (-1);
    BOOST_CHECK_EQUAL (std::string (exception.what ()), "generator mode ( -1 ) is undefined");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorRandom) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode           = e_generator_mode::RANDOM;
    GeneratorBase* generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorRandom");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorSingleObjectMiddle) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode           = e_generator_mode::SINGLE_OBJECT_MIDDLE;
    GeneratorBase* generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorSingleObjectMiddle");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorGridDistribution) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode           = e_generator_mode::GRID_DISTRIBUTION;
    GeneratorBase* generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorGridDistribution");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorMulipleObjects) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode           = e_generator_mode::MULTIPLE_OBJECTS;
    GeneratorBase* generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorMultipleObjects");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorRandomUniform) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode           = e_generator_mode::RANDOM_UNIFORM;
    GeneratorBase* generator = GeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorRandomUniform");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorError) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode = static_cast<e_generator_mode> (-1);
    BOOST_CHECK_THROW (GeneratorFactory::build (options), GeneratorInvalidException);
}
