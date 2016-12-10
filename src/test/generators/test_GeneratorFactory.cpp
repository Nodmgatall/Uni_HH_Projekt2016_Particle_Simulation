/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticleGeneratorFactory"
#include "../../main/io/input/InputFactory.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_CASE (testParticleGeneratorRandom) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::RANDOM;
    InputBase input      = InputFactory::build (options);
    BOOST_CHECK_EQUAL (input.get_stucture_name (), "ParticleGeneratorRandom");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorSingleObjectMiddle) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::SINGLE_OBJECT_MIDDLE;
    InputBase input      = InputFactory::build (options);
    BOOST_CHECK_EQUAL (input.get_stucture_name (), "ParticleGeneratorSingleObjectMiddle");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorGridDistribution) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::GRID_DISTRIBUTION;
    InputBase input      = InputFactory::build (options);
    BOOST_CHECK_EQUAL (input.get_stucture_name (), "ParticleGeneratorGridDistribution");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorMulipleObjects) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::MULTIPLE_OBJECTS;
    InputBase input      = InputFactory::build (options);
    BOOST_CHECK_EQUAL (input.get_stucture_name (), "ParticleGeneratorMultipleObjects");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorRandomUniform) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::RANDOM_UNIFORM;
    InputBase input      = InputFactory::build (options);
    BOOST_CHECK_EQUAL (input.get_stucture_name (), "ParticleGeneratorRandomUniform");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorError) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = static_cast<e_input_type> (-1);
    BOOST_CHECK_THROW (InputFactory::build (options), InputTypeInvalidException);
}
