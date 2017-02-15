/*
 * test_EnumAlgorithmType.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumAlgorithmType"
#include "enums/EnumAlgorithmType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>
BOOST_AUTO_TEST_CASE (testException1) {
    AlgorithmTypeInvalidException exception (e_algorithm_type::LENNARD_JONES);
    BOOST_CHECK_EQUAL (exception.what (), "algorithm type ( LENNARD_JONES ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException2) {
    AlgorithmTypeInvalidException exception (e_algorithm_type::SMOTHED_PARTICLE_HYDRODYNAMICS);
    BOOST_CHECK_EQUAL (exception.what (), "algorithm type ( SMOTHED_PARTICLE_HYDRODYNAMICS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException3) {
    AlgorithmTypeInvalidException exception (e_algorithm_type::DISSIPATIVE_PARTICLE_DYNAMICS);
    BOOST_CHECK_EQUAL (exception.what (), "algorithm type ( DISSIPATIVE_PARTICLE_DYNAMICS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testStringOut1) {
    std::stringstream s;
    s << e_algorithm_type::LENNARD_JONES;
    BOOST_CHECK_EQUAL (s.str (), "LENNARD_JONES");
}
BOOST_AUTO_TEST_CASE (testStringOut2) {
    std::stringstream s;
    s << e_algorithm_type::SMOTHED_PARTICLE_HYDRODYNAMICS;
    BOOST_CHECK_EQUAL (s.str (), "SMOTHED_PARTICLE_HYDRODYNAMICS");
}
BOOST_AUTO_TEST_CASE (testStringOut3) {
    std::stringstream s;
    s << e_algorithm_type::DISSIPATIVE_PARTICLE_DYNAMICS;
    BOOST_CHECK_EQUAL (s.str (), "DISSIPATIVE_PARTICLE_DYNAMICS");
}
BOOST_AUTO_TEST_CASE (testStringIn1) {
    std::stringstream s ("LENNARD_JONES");
    e_algorithm_type  tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_algorithm_type::LENNARD_JONES);
}
BOOST_AUTO_TEST_CASE (testStringIn2) {
    std::stringstream s ("SMOTHED_PARTICLE_HYDRODYNAMICS");
    e_algorithm_type  tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_algorithm_type::SMOTHED_PARTICLE_HYDRODYNAMICS);
}
BOOST_AUTO_TEST_CASE (testStringIn3) {
    std::stringstream s ("DISSIPATIVE_PARTICLE_DYNAMICS");
    e_algorithm_type  tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_algorithm_type::DISSIPATIVE_PARTICLE_DYNAMICS);
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_algorithm_type> (0)), AlgorithmTypeInvalidException);
}
