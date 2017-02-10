/*
 * test_EnumOutputType.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
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
BOOST_AUTO_TEST_CASE (testString1Out) {
    std::stringstream s;
    s << e_output_type::FILE_CSV;
    BOOST_CHECK_EQUAL (s.str (), "FILE_CSV");
}
BOOST_AUTO_TEST_CASE (testString2Out) {
    std::stringstream s;
    s << e_output_type::FILE_LAMMPS;
    BOOST_CHECK_EQUAL (s.str (), "FILE_LAMMPS");
}
BOOST_AUTO_TEST_CASE (testString3Out) {
    std::stringstream s;
    s << e_output_type::FILE_ESPRESSO;
    BOOST_CHECK_EQUAL (s.str (), "FILE_ESPRESSO");
}
BOOST_AUTO_TEST_CASE (testString4Out) {
    std::stringstream s;
    s << e_output_type::FILE_GROMACS;
    BOOST_CHECK_EQUAL (s.str (), "FILE_GROMACS");
}
BOOST_AUTO_TEST_CASE (testString5Out) {
    std::stringstream s;
    s << e_output_type::FILE_VMD;
    BOOST_CHECK_EQUAL (s.str (), "FILE_VMD");
}
BOOST_AUTO_TEST_CASE (testString6Out) {
    std::stringstream s;
    s << e_output_type::FILE_VTK;
    BOOST_CHECK_EQUAL (s.str (), "FILE_VTK");
}
BOOST_AUTO_TEST_CASE (testStringIn1) {
    std::stringstream s ("FILE_CSV");
    e_output_type     tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_output_type::FILE_CSV);
}
BOOST_AUTO_TEST_CASE (testStringIn2) {
    std::stringstream s ("FILE_LAMMPS");
    e_output_type     tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_output_type::FILE_LAMMPS);
}
BOOST_AUTO_TEST_CASE (testStringIn3) {
    std::stringstream s ("FILE_ESPRESSO");
    e_output_type     tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_output_type::FILE_ESPRESSO);
}
BOOST_AUTO_TEST_CASE (testStringIn4) {
    std::stringstream s ("FILE_GROMACS");
    e_output_type     tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_output_type::FILE_GROMACS);
}
BOOST_AUTO_TEST_CASE (testStringIn5) {
    std::stringstream s ("FILE_VMD");
    e_output_type     tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_output_type::FILE_VMD);
}
BOOST_AUTO_TEST_CASE (testStringIn6) {
    std::stringstream s ("FILE_VTK");
    e_output_type     tmp;
    s >> tmp;
    BOOST_CHECK_EQUAL (tmp, e_output_type::FILE_VTK);
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_output_type> (0)), OutputTypeInvalidException);
}
