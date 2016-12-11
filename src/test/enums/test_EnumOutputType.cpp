/*
 * test_Vec3.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamout
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumOutputType"
#include "../../main/enums/EnumOutputType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE (testException1) {
    OutputTypeInvalidException exception (e_output_type::CSV);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( CSV ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException2) {
    OutputTypeInvalidException exception (e_output_type::LAMMPS);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( LAMMPS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException3) {
    OutputTypeInvalidException exception (e_output_type::ESPRESSO);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( ESPRESSO ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException4) {
    OutputTypeInvalidException exception (e_output_type::GROMACS);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( GROMACS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException5) {
    OutputTypeInvalidException exception (e_output_type::VMD);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( VMD ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException6) {
    OutputTypeInvalidException exception (e_output_type::VTK);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( VTK ) is invalid");
}
BOOST_AUTO_TEST_CASE (testString1) {
    std::stringstream s;
    s << e_output_type::CSV;
    BOOST_CHECK_EQUAL (s.str (), "CSV");
}
BOOST_AUTO_TEST_CASE (testString2) {
    std::stringstream s;
    s << e_output_type::LAMMPS;
    BOOST_CHECK_EQUAL (s.str (), "LAMMPS");
}
BOOST_AUTO_TEST_CASE (testString3) {
    std::stringstream s;
    s << e_output_type::ESPRESSO;
    BOOST_CHECK_EQUAL (s.str (), "ESPRESSO");
}
BOOST_AUTO_TEST_CASE (testString4) {
    std::stringstream s;
    s << e_output_type::GROMACS;
    BOOST_CHECK_EQUAL (s.str (), "GROMACS");
}
BOOST_AUTO_TEST_CASE (testString5) {
    std::stringstream s;
    s << e_output_type::VMD;
    BOOST_CHECK_EQUAL (s.str (), "VMD");
}
BOOST_AUTO_TEST_CASE (testString6) {
    std::stringstream s;
    s << e_output_type::VTK;
    BOOST_CHECK_EQUAL (s.str (), "VTK");
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_output_type> (0)), OutputTypeInvalidException);
}
