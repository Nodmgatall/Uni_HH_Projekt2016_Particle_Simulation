/*
 * test_Vec3.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "AlgorithmFactory"
#include "../../main/enums/EnumAlgorithmType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE (testEnumAlgorithmType1) {
    AlgorithmTypeInvalidException exception (e_algorithm_type::LENNARD_JONES);
    BOOST_CHECK_EQUAL (exception.what (), "algorithm type ( LENNARD_JONES ) is invalid");
}
BOOST_AUTO_TEST_CASE (testEnumAlgorithmType2) {
    AlgorithmTypeInvalidException exception (e_algorithm_type::SMOTHED_PARTICLE_HYDRODYNAMICS);
    BOOST_CHECK_EQUAL (exception.what (),
                       "algorithm type ( SMOTHED_PARTICLE_HYDRODYNAMICS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testEnumAlgorithmType3) {
    AlgorithmTypeInvalidException exception (e_algorithm_type::DISSIPATIVE_PARTICLE_DYNAMICS);
    BOOST_CHECK_EQUAL (exception.what (),
                       "algorithm type ( DISSIPATIVE_PARTICLE_DYNAMICS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testEnumAlgorithmType4) {
    std::stringstream s;
    s << e_algorithm_type::LENNARD_JONES;
    BOOST_CHECK_EQUAL (s.str (), "LENNARD_JONES");
}
BOOST_AUTO_TEST_CASE (testEnumAlgorithmType5) {
    std::stringstream s;
    s << e_algorithm_type::SMOTHED_PARTICLE_HYDRODYNAMICS;
    BOOST_CHECK_EQUAL (s.str (), "SMOTHED_PARTICLE_HYDRODYNAMICS");
}
BOOST_AUTO_TEST_CASE (testEnumAlgorithmType6) {
    std::stringstream s;
    s << e_algorithm_type::DISSIPATIVE_PARTICLE_DYNAMICS;
    BOOST_CHECK_EQUAL (s.str (), "DISSIPATIVE_PARTICLE_DYNAMICS");
}
BOOST_AUTO_TEST_CASE (testEnumAlgorithmType7) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_algorithm_type> (0)), AlgorithmTypeInvalidException);
}