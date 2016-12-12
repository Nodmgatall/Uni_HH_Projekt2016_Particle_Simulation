/*
 * test_Vec3.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamout
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumOutputType"
#include "enums/EnumOutputType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE (testException1) {
    OutputTypeInvalidException exception (e_output_type::FILE_CSV);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( FILE_CSV ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException2) {
    OutputTypeInvalidException exception (e_output_type::FILE_LAMMPS);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( FILE_LAMMPS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException3) {
    OutputTypeInvalidException exception (e_output_type::FILE_ESPRESSO);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( FILE_ESPRESSO ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException4) {
    OutputTypeInvalidException exception (e_output_type::FILE_GROMACS);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( FILE_GROMACS ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException5) {
    OutputTypeInvalidException exception (e_output_type::FILE_VMD);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( FILE_VMD ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException6) {
    OutputTypeInvalidException exception (e_output_type::FILE_VTK);
    BOOST_CHECK_EQUAL (exception.what (), "output type ( FILE_VTK ) is invalid");
}
BOOST_AUTO_TEST_CASE (testString1) {
    std::stringstream s;
    s << e_output_type::FILE_CSV;
    BOOST_CHECK_EQUAL (s.str (), "FILE_CSV");
}
BOOST_AUTO_TEST_CASE (testString2) {
    std::stringstream s;
    s << e_output_type::FILE_LAMMPS;
    BOOST_CHECK_EQUAL (s.str (), "FILE_LAMMPS");
}
BOOST_AUTO_TEST_CASE (testString3) {
    std::stringstream s;
    s << e_output_type::FILE_ESPRESSO;
    BOOST_CHECK_EQUAL (s.str (), "FILE_ESPRESSO");
}
BOOST_AUTO_TEST_CASE (testString4) {
    std::stringstream s;
    s << e_output_type::FILE_GROMACS;
    BOOST_CHECK_EQUAL (s.str (), "FILE_GROMACS");
}
BOOST_AUTO_TEST_CASE (testString5) {
    std::stringstream s;
    s << e_output_type::FILE_VMD;
    BOOST_CHECK_EQUAL (s.str (), "FILE_VMD");
}
BOOST_AUTO_TEST_CASE (testString6) {
    std::stringstream s;
    s << e_output_type::FILE_VTK;
    BOOST_CHECK_EQUAL (s.str (), "FILE_VTK");
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_output_type> (0)), OutputTypeInvalidException);
}
