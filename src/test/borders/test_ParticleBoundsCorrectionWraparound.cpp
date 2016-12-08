/*
 * test_ParticleBoundsCorrectionWraparound.cpp
 *
 *  Created on: 08.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticleBoundsCorrectionWraparound"
#include "../../main/Vec3.hpp"
#include "../../main/borders/ParticleBoundsCorrectionWraparound.hpp"
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_CASE (test1) {
    Vec3f                              bounds (3, 4, 5);
    ParticleBoundsCorrectionWraparound particleBoundsCorrectionWraparound (bounds);
    data_type                          v[] = { 1, 2, 3, 101, 102, 103 };
    particleBoundsCorrectionWraparound.updatePosition (v[0], v[1], v[2], v[3], v[4], v[5]);

    // TODO !!!!!!!!!
}
