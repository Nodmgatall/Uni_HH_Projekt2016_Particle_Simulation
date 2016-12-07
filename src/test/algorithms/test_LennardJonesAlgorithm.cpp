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
#include <cstring>
BOOST_AUTO_TEST_CASE (step1) {
    s_simulator_options options;
    memset (&options, 0, sizeof (s_simulator_options));
    options.m_timestep = 1;
    LennardJonesAlgorithm::init (options);
    float v[] = { 1, 2, 3, 4, 5, 6 };
    LennardJonesAlgorithm::step_1 (v[0], v[1], v[2], v[3], v[4], v[5]);
    for (int i = 0; i < 3; i++)
        BOOST_CHECK_EQUAL (v[i], 1 + i);
    for (int i = 0; i < 3; i++)
        BOOST_CHECK_EQUAL (v[3 + i], i - 2);
}
BOOST_AUTO_TEST_CASE (step2) {
    s_simulator_options options;
    memset (&options, 0, sizeof (s_simulator_options));
    options.m_timestep = 1;
    LennardJonesAlgorithm::init (options);
    float v[] = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6 };
    LennardJonesAlgorithm::step_2 (v[0], v[1], v[2], v[6], v[7], v[8], v[3], v[4], v[5], v[9], v[10], v[11]);
    for (int i = 0; i < 6; i++) {
        BOOST_CHECK_EQUAL (v[i], 1 + i);
    }
    for (int i = 0; i < 6; i++) {
        BOOST_CHECK_CLOSE (v[6 + i], i + 1, 0.1); // TODO this check is useless!!
    }
}
