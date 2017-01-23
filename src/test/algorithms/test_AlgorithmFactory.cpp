/*
 * test_LennardJonesAlgorithm.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "AlgorithmFactory"
#include "algorithms/AlgorithmFactory.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
BOOST_AUTO_TEST_CASE (test1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_algorithm_type = e_algorithm_type::LENNARD_JONES;
    BOOST_CHECK_EQUAL (AlgorithmFactory::build (options)->get_structure_name (), "AlgorithmStoermerVerletLennardJones");
}
BOOST_AUTO_TEST_CASE (test2) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    BOOST_CHECK_THROW (AlgorithmFactory::build (options), AlgorithmTypeInvalidException);
}
