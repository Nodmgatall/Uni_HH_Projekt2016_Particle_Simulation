
/*
 * test_LennardJonesAlgorithm.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "AlgorithmLennardJones"
#include "../../main/algorithms/AlgorithmLennardJones.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
BOOST_AUTO_TEST_CASE (step1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_timestep = 1;
    AlgorithmLennardJones algorithm (options);
    data_type             v[] = { 1, 2, 3, 4, 5, 6 };
    algorithm.step_1 (v[0], v[1], v[2], v[3], v[4], v[5]);
    for (int i = 0; i < 3; i++)
        BOOST_CHECK_EQUAL (v[i], 1 + i);
    for (int i = 0; i < 3; i++)
        BOOST_CHECK_EQUAL (v[3 + i], i - 2);
}
BOOST_AUTO_TEST_CASE (step2_1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_timestep = 1;
    AlgorithmLennardJones algorithm (options);
    data_type             v[] = { 1, 2, 3, 2, 2, 3, 1, 2, 3, 2, 2, 3 };
    algorithm.step_2 (v[0], v[1], v[2], v[6], v[7], v[8], &v[3], &v[4], &v[5], &v[9], &v[10], &v[11], 0, 1);
    BOOST_CHECK_EQUAL (v[6] - v[0], 24);
    BOOST_CHECK_EQUAL (v[9] - v[3], -24);
}
BOOST_AUTO_TEST_CASE (step2_2) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_timestep = 1;
    AlgorithmLennardJones algorithm (options);
    data_type             v[] = { 1, 2, 3, 1, 3, 3, 1, 2, 3, 1, 3, 3 };
    algorithm.step_2 (v[0], v[1], v[2], v[6], v[7], v[8], &v[3], &v[4], &v[5], &v[9], &v[10], &v[11], 0, 1);
    BOOST_CHECK_EQUAL (v[7] - v[1], 24);
    BOOST_CHECK_EQUAL (v[10] - v[4], -24);
}
BOOST_AUTO_TEST_CASE (step2_3) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_timestep = 1;
    AlgorithmLennardJones algorithm (options);
    data_type             v[] = { 1, 2, 3, 1, 2, 4, 1, 2, 3, 1, 2, 4 };
    algorithm.step_2 (v[0], v[1], v[2], v[6], v[7], v[8], &v[3], &v[4], &v[5], &v[9], &v[10], &v[11], 0, 1);
    BOOST_CHECK_EQUAL (v[8] - v[2], 24);
    BOOST_CHECK_EQUAL (v[11] - v[5], -24);
}
