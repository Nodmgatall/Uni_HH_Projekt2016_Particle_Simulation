/*
 * test_ParticleBoundsCorrectionWraparound.cpp
 *
 *  Created on: 08.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "BorderWrapparound"
#include "Vec3.hpp"
#include "borders/BorderWrapparound.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (test1) {
    Vec3f             bounds (3, 4, 5);
    BorderWrapparound particleBoundsCorrectionWraparound (bounds);
    data_type         v[] = { 1, 2, 3, 101, 102, 103 };
    BOOST_CHECK_EQUAL (particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]), false);
    BOOST_CHECK_EQUAL (v[0], 1);
    BOOST_CHECK_EQUAL (v[1], 2);
    BOOST_CHECK_EQUAL (v[2], 3);
    BOOST_CHECK_EQUAL (v[3], 101);
    BOOST_CHECK_EQUAL (v[4], 102);
    BOOST_CHECK_EQUAL (v[5], 103);
}
BOOST_AUTO_TEST_CASE (test2) {
    Vec3f             bounds (3, 4, 5);
    BorderWrapparound particleBoundsCorrectionWraparound (bounds);
    data_type         v[] = { 7, 2, 3, 101, 102, 103 };
    BOOST_CHECK_EQUAL (particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]), true);
    BOOST_CHECK_EQUAL (v[0], 1);
    BOOST_CHECK_EQUAL (v[1], 2);
    BOOST_CHECK_EQUAL (v[2], 3);
    BOOST_CHECK_EQUAL (v[3], 95);
    BOOST_CHECK_EQUAL (v[4], 102);
    BOOST_CHECK_EQUAL (v[5], 103);
}
BOOST_AUTO_TEST_CASE (test3) {
    Vec3f             bounds (3, 4, 5);
    BorderWrapparound particleBoundsCorrectionWraparound (bounds);
    data_type         v[] = { 1, 13, 3, 101, 102, 103 };
    BOOST_CHECK_EQUAL (particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]), true);
    BOOST_CHECK_EQUAL (v[0], 1);
    BOOST_CHECK_EQUAL (v[1], 1);
    BOOST_CHECK_EQUAL (v[2], 3);
    BOOST_CHECK_EQUAL (v[3], 101);
    BOOST_CHECK_EQUAL (v[4], 90);
    BOOST_CHECK_EQUAL (v[5], 103);
}
BOOST_AUTO_TEST_CASE (test4) {
    Vec3f             bounds (3, 4, 5);
    BorderWrapparound particleBoundsCorrectionWraparound (bounds);
    data_type         v[] = { 1, 2, 13, 101, 102, 103 };
    BOOST_CHECK_EQUAL (particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]), true);
    BOOST_CHECK_EQUAL (v[0], 1);
    BOOST_CHECK_EQUAL (v[1], 2);
    BOOST_CHECK_EQUAL (v[2], 3);
    BOOST_CHECK_EQUAL (v[3], 101);
    BOOST_CHECK_EQUAL (v[4], 102);
    BOOST_CHECK_EQUAL (v[5], 93);
}
BOOST_AUTO_TEST_CASE (test5) {
    Vec3f             bounds (3, 4, 5);
    BorderWrapparound particleBoundsCorrectionWraparound (bounds);
    data_type         v[] = { -10, 2, 3, 101, 102, 103 };
    BOOST_CHECK_EQUAL (particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]), true);
    BOOST_CHECK_EQUAL (v[0], 2);
    BOOST_CHECK_EQUAL (v[1], 2);
    BOOST_CHECK_EQUAL (v[2], 3);
    BOOST_CHECK_EQUAL (v[3], 113);
    BOOST_CHECK_EQUAL (v[4], 102);
    BOOST_CHECK_EQUAL (v[5], 103);
}
BOOST_AUTO_TEST_CASE (test6) {
    Vec3f             bounds (3, 4, 5);
    BorderWrapparound particleBoundsCorrectionWraparound (bounds);
    data_type         v[] = { 1, -11, 3, 101, 102, 103 };
    BOOST_CHECK_EQUAL (particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]), true);
    BOOST_CHECK_EQUAL (v[0], 1);
    BOOST_CHECK_EQUAL (v[1], 1);
    BOOST_CHECK_EQUAL (v[2], 3);
    BOOST_CHECK_EQUAL (v[3], 101);
    BOOST_CHECK_EQUAL (v[4], 114);
    BOOST_CHECK_EQUAL (v[5], 103);
}
BOOST_AUTO_TEST_CASE (test7) {
    Vec3f             bounds (3, 4, 5);
    BorderWrapparound particleBoundsCorrectionWraparound (bounds);
    data_type         v[] = { 1, 2, -33, 101, 102, 103 };
    BOOST_CHECK_EQUAL (particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]), true);
    BOOST_CHECK_EQUAL (v[0], 1);
    BOOST_CHECK_EQUAL (v[1], 2);
    BOOST_CHECK_EQUAL (v[2], 2);
    BOOST_CHECK_EQUAL (v[3], 101);
    BOOST_CHECK_EQUAL (v[4], 102);
    BOOST_CHECK_EQUAL (v[5], 138);
}
