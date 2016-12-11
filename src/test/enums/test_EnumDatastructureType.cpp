/*
 * test_Vec3.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumDatastructureType"
#include "../../main/enums/EnumDatastructureType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE (testException1) {
    DatastructureTypeInvalidException exception (e_datastructure_type::GRID);
    BOOST_CHECK_EQUAL (exception.what (), "datastructure type ( GRID ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException2) {
    DatastructureTypeInvalidException exception (e_datastructure_type::LIST);
    BOOST_CHECK_EQUAL (exception.what (), "datastructure type ( LIST ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException3) {
    DatastructureTypeInvalidException exception (e_datastructure_type::LISTEDGIRD);
    BOOST_CHECK_EQUAL (exception.what (), "datastructure type ( LISTEDGIRD ) is invalid");
}
BOOST_AUTO_TEST_CASE (testString1) {
    std::stringstream s;
    s << e_datastructure_type::GRID;
    BOOST_CHECK_EQUAL (s.str (), "GRID");
}
BOOST_AUTO_TEST_CASE (testString2) {
    std::stringstream s;
    s << e_datastructure_type::LIST;
    BOOST_CHECK_EQUAL (s.str (), "LIST");
}
BOOST_AUTO_TEST_CASE (testString3) {
    std::stringstream s;
    s << e_datastructure_type::LISTEDGIRD;
    BOOST_CHECK_EQUAL (s.str (), "LISTEDGIRD");
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_datastructure_type> (0)), DatastructureTypeInvalidException);
}
