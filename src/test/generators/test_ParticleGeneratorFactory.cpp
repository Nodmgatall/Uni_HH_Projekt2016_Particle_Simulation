/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticleGeneratorFactory"
#include "../../main/generators/ParticleGeneratorFactory.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_CASE (testParticleGeneratorRandom) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode                                   = e_generator_mode::RANDOM;
    std::unique_ptr<ParticleGeneratorBase> generator = ParticleGeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorRandom");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorSingleObjectMiddle) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode                                   = e_generator_mode::SINGLE_OBJECT_MIDDLE;
    std::unique_ptr<ParticleGeneratorBase> generator = ParticleGeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorSingleObjectMiddle");
}
BOOST_AUTO_TEST_CASE (testParticleGeneratorGridDistribution) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_mode                                   = e_generator_mode::GRID_DISTRIBUTION;
    std::unique_ptr<ParticleGeneratorBase> generator = ParticleGeneratorFactory::build (options);
    BOOST_CHECK_EQUAL (generator->get_stucture_name (), "ParticleGeneratorGridDistribution");
}
