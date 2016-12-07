/*
 * test_LennardJonesAlgorithm.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Vec3f"
#include "../../main/algorithms/LennardJonesAlgorithm.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (step1) {
    s_simulator_options options;
    options.m_timestep = 1;
    LennardJonesAlgorithm::init (options);
    float v[] = { 1, 2, 3, 4, 5, 6 };
    LennardJonesAlgorithm::step_1 (v[0], v[1], v[2], v[3], v[4], v[5]);
    for (int i = 1; i < 6; i++)
        BOOST_CHECK_EQUAL (v[i], i);
}
