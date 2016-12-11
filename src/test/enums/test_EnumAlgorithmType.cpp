/*
 * test_Vec3.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumAlgorithmType"
#include "../../main/enums/EnumAlgorithmType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <string>

BOOST_AUTO_TEST_CASE (test1) {
    AlgorithmTypeInvalidException exception (e_algorithm_type::LENNARD_JONES);
    BOOST_CHECK_EQUAL (exception.what (), "algorithm type ( LENNARD_JONES ) is invalid");
}
