/*
 * test_Vec3.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumInputType"
#include "enums/EnumInputType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE (testException1) {
    InputTypeInvalidException exception (e_input_type::GENERATOR_RANDOM);
    BOOST_CHECK_EQUAL (exception.what (), "input type ( GENERATOR_RANDOM ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException2) {
    InputTypeInvalidException exception (e_input_type::GENERATOR_RANDOM_UNIFORM);
    BOOST_CHECK_EQUAL (exception.what (), "input type ( GENERATOR_RANDOM_UNIFORM ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException3) {
    InputTypeInvalidException exception (e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE);
    BOOST_CHECK_EQUAL (exception.what (),
                       "input type ( GENERATOR_SINGLE_OBJECT_MIDDLE ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException4) {
    InputTypeInvalidException exception (e_input_type::GENERATOR_GRID_DISTRIBUTION);
    BOOST_CHECK_EQUAL (exception.what (), "input type ( GENERATOR_GRID_DISTRIBUTION ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException5) {
    InputTypeInvalidException exception (e_input_type::GENERATOR_MULTIPLE_OBJECTS);
    BOOST_CHECK_EQUAL (exception.what (), "input type ( GENERATOR_MULTIPLE_OBJECTS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException6) {
    InputTypeInvalidException exception (e_input_type::FILE_CSV);
    BOOST_CHECK_EQUAL (exception.what (), "input type ( FILE_CSV ) is invalid");
}
BOOST_AUTO_TEST_CASE (testString1) {
    std::stringstream s;
    s << e_input_type::GENERATOR_RANDOM;
    BOOST_CHECK_EQUAL (s.str (), "GENERATOR_RANDOM");
}
BOOST_AUTO_TEST_CASE (testString2) {
    std::stringstream s;
    s << e_input_type::GENERATOR_RANDOM_UNIFORM;
    BOOST_CHECK_EQUAL (s.str (), "GENERATOR_RANDOM_UNIFORM");
}
BOOST_AUTO_TEST_CASE (testString3) {
    std::stringstream s;
    s << e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE;
    BOOST_CHECK_EQUAL (s.str (), "GENERATOR_SINGLE_OBJECT_MIDDLE");
}
BOOST_AUTO_TEST_CASE (testString4) {
    std::stringstream s;
    s << e_input_type::GENERATOR_GRID_DISTRIBUTION;
    BOOST_CHECK_EQUAL (s.str (), "GENERATOR_GRID_DISTRIBUTION");
}
BOOST_AUTO_TEST_CASE (testString5) {
    std::stringstream s;
    s << e_input_type::GENERATOR_MULTIPLE_OBJECTS;
    BOOST_CHECK_EQUAL (s.str (), "GENERATOR_MULTIPLE_OBJECTS");
}
BOOST_AUTO_TEST_CASE (testString6) {
    std::stringstream s;
    s << e_input_type::FILE_CSV;
    BOOST_CHECK_EQUAL (s.str (), "FILE_CSV");
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_input_type> (0)), InputTypeInvalidException);
}
