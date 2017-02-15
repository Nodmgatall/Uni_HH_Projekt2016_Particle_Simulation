/*
 * test_EnumDatastructureType.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumDatastructureType"
#include "enums/EnumDatastructureType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>
BOOST_AUTO_TEST_CASE (testException1) {
    DatastructureTypeInvalidException exception (e_datastructure_type::LINKED_CELLS);
    BOOST_CHECK_EQUAL (exception.what (), "datastructure type ( LINKED_CELLS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException2) {
    DatastructureTypeInvalidException exception (e_datastructure_type::LINKED_CELLS_NEIGHBOR_LIST);
    BOOST_CHECK_EQUAL (exception.what (), "datastructure type ( LINKED_CELLS+NEIGHBOR_LIST ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException3) {
    DatastructureTypeInvalidException exception (e_datastructure_type::NEIGHBOR_LIST);
    BOOST_CHECK_EQUAL (exception.what (), "datastructure type ( NEIGHBOR_LIST ) is invalid");
}
BOOST_AUTO_TEST_CASE (testString1Out) {
    std::stringstream s;
    s << e_datastructure_type::LINKED_CELLS;
    BOOST_CHECK_EQUAL (s.str (), "LINKED_CELLS");
}
BOOST_AUTO_TEST_CASE (testString2Out) {
    std::stringstream s;
    s << e_datastructure_type::LINKED_CELLS_NEIGHBOR_LIST;
    BOOST_CHECK_EQUAL (s.str (), "LINKED_CELLS+NEIGHBOR_LIST");
}
BOOST_AUTO_TEST_CASE (testString3Out) {
    std::stringstream s;
    s << e_datastructure_type::NEIGHBOR_LIST;
    BOOST_CHECK_EQUAL (s.str (), "NEIGHBOR_LIST");
}

BOOST_AUTO_TEST_CASE (testStringIn1) {
    std::stringstream    s ("LINKED_CELLS");
    e_datastructure_type tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_datastructure_type::LINKED_CELLS);
}
BOOST_AUTO_TEST_CASE (testStringIn2) {
    std::stringstream    s ("LINKED_CELLS+NEIGHBOR_LIST");
    e_datastructure_type tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_datastructure_type::LINKED_CELLS_NEIGHBOR_LIST);
}
BOOST_AUTO_TEST_CASE (testStringIn3) {
    std::stringstream    s ("NEIGHBOR_LIST");
    e_datastructure_type tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_datastructure_type::NEIGHBOR_LIST);
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_datastructure_type> (0)), DatastructureTypeInvalidException);
}
