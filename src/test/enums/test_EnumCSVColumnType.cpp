/*
 * test_Vec3.cpp
 *
 *  Created on: 07.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "EnumCSVColumnType"
#include "../../main/enums/EnumCSVColumnType.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE (testException1) {
    CSVColumnTypeInvalidException exception (e_csv_column_type::ID);
    BOOST_CHECK_EQUAL (exception.what (), "csv_column type ( ID ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException2) {
    CSVColumnTypeInvalidException exception (e_csv_column_type::VELOCITY);
    BOOST_CHECK_EQUAL (exception.what (), "csv_column type ( VELOCITY ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException3) {
    CSVColumnTypeInvalidException exception (e_csv_column_type::POSITION);
    BOOST_CHECK_EQUAL (exception.what (), "csv_column type ( POSITION ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException4) {
    CSVColumnTypeInvalidException exception (e_csv_column_type::ACCELERATION);
    BOOST_CHECK_EQUAL (exception.what (), "csv_column type ( ACCELERATION ) is invalid");
}
BOOST_AUTO_TEST_CASE (testException5) {
    CSVColumnTypeInvalidException exception (e_csv_column_type::PARTICLE_TYPE);
    BOOST_CHECK_EQUAL (exception.what (), "csv_column type ( PARTICLE_TYPE ) is invalid");
}
BOOST_AUTO_TEST_CASE (testString1) {
    std::stringstream s;
    s << e_csv_column_type::ID;
    BOOST_CHECK_EQUAL (s.str (), "ID");
}
BOOST_AUTO_TEST_CASE (testString2) {
    std::stringstream s;
    s << e_csv_column_type::VELOCITY;
    BOOST_CHECK_EQUAL (s.str (), "VELOCITY");
}
BOOST_AUTO_TEST_CASE (testString3) {
    std::stringstream s;
    s << e_csv_column_type::POSITION;
    BOOST_CHECK_EQUAL (s.str (), "POSITION");
}
BOOST_AUTO_TEST_CASE (testString4) {
    std::stringstream s;
    s << e_csv_column_type::ACCELERATION;
    BOOST_CHECK_EQUAL (s.str (), "ACCELERATION");
}
BOOST_AUTO_TEST_CASE (testString5) {
    std::stringstream s;
    s << e_csv_column_type::PARTICLE_TYPE;
    BOOST_CHECK_EQUAL (s.str (), "PARTICLE_TYPE");
}
BOOST_AUTO_TEST_CASE (testStringException) {
    std::stringstream s;
    BOOST_CHECK_THROW (s << (static_cast<e_csv_column_type> (0)), CSVColumnTypeInvalidException);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_1) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("ID");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::ID);
    BOOST_CHECK_EQUAL (val->second, 0);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_2) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("VelocityX");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::VELOCITY);
    BOOST_CHECK_EQUAL (val->second, 0);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_3) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("VelocityY");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::VELOCITY);
    BOOST_CHECK_EQUAL (val->second, 1);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_4) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("VelocityZ");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::VELOCITY);
    BOOST_CHECK_EQUAL (val->second, 2);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_5) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("PositionX");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::POSITION);
    BOOST_CHECK_EQUAL (val->second, 0);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_6) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("PositionY");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::POSITION);
    BOOST_CHECK_EQUAL (val->second, 1);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_7) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("PositionZ");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::POSITION);
    BOOST_CHECK_EQUAL (val->second, 2);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_8) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("AccelerationX");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::ACCELERATION);
    BOOST_CHECK_EQUAL (val->second, 0);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_9) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("AccelerationY");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::ACCELERATION);
    BOOST_CHECK_EQUAL (val->second, 1);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_10) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("AccelerationZ");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::ACCELERATION);
    BOOST_CHECK_EQUAL (val->second, 2);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_11) {
    std::pair<e_csv_column_type, int>* val = get_enum_for_printed_csv_column_name ("ParticleType");
    BOOST_CHECK_EQUAL (val->first, e_csv_column_type::PARTICLE_TYPE);
    BOOST_CHECK_EQUAL (val->second, 0);
}
BOOST_AUTO_TEST_CASE (test_get_enum_for_printed_csv_column_name_12) {
    std::pair<e_csv_column_type, int>* val =
        get_enum_for_printed_csv_column_name ("dieseZeileGibtEsNicht");
    BOOST_CHECK_EQUAL (val, (void*) 0);
}
