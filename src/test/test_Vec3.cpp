/*
 * test_Vec3.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Vec3"
#include "Vec3.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <string>
BOOST_AUTO_TEST_CASE (constructors1) {
    Vec3<int> obj = Vec3<int> (3);
    BOOST_CHECK_EQUAL (obj.x, 3);
    BOOST_CHECK_EQUAL (obj.y, 3);
    BOOST_CHECK_EQUAL (obj.z, 3);
}
BOOST_AUTO_TEST_CASE (constructors2) {
    Vec3<int> obj = Vec3<int> (3, 4, 5);
    BOOST_CHECK_EQUAL (obj.x, 3);
    BOOST_CHECK_EQUAL (obj.y, 4);
    BOOST_CHECK_EQUAL (obj.z, 5);
}
BOOST_AUTO_TEST_CASE (constructors3) {
    Vec3<int> obj = Vec3<int> ();
    BOOST_CHECK_EQUAL (obj.x, 0);
    BOOST_CHECK_EQUAL (obj.y, 0);
    BOOST_CHECK_EQUAL (obj.z, 0);
}
BOOST_AUTO_TEST_CASE (constructors4) {
    Vec3<data_type> objf = Vec3<data_type> (3.5, 4.6, 5.5);
    Vec3<int>       obj  = Vec3<int> (objf);
    BOOST_CHECK_EQUAL (obj.x, 3);
    BOOST_CHECK_EQUAL (obj.y, 4);
    BOOST_CHECK_EQUAL (obj.z, 5);
}
BOOST_AUTO_TEST_CASE (operator_plus) {
    Vec3<int> obja = Vec3<int> (1, 2, 3);
    Vec3<int> objb = Vec3<int> (4, 5, 6);
    Vec3<int> objc = obja + objb;
    BOOST_CHECK_EQUAL (objc.x, 5);
    BOOST_CHECK_EQUAL (objc.y, 7);
    BOOST_CHECK_EQUAL (objc.z, 9);
}
BOOST_AUTO_TEST_CASE (operator_plus_gleich1) {
    Vec3<int> obja = Vec3<int> (1, 2, 3);
    Vec3<int> objb = Vec3<int> (4, 5, 6);
    objb += obja;
    BOOST_CHECK_EQUAL (objb.x, 5);
    BOOST_CHECK_EQUAL (objb.y, 7);
    BOOST_CHECK_EQUAL (objb.z, 9);
}
BOOST_AUTO_TEST_CASE (operator_plus_gleich2) {
    Vec3<int> obj = Vec3<int> (4, 5, 6);
    obj += 5;
    BOOST_CHECK_EQUAL (obj.x, 9);
    BOOST_CHECK_EQUAL (obj.y, 10);
    BOOST_CHECK_EQUAL (obj.z, 11);
}
BOOST_AUTO_TEST_CASE (operator_minus1) {
    Vec3<int> obja = Vec3<int> (3, 2, 1);
    Vec3<int> objb = Vec3<int> (4, 5, 6);
    Vec3<int> objc = objb - obja;
    BOOST_CHECK_EQUAL (objc.x, 1);
    BOOST_CHECK_EQUAL (objc.y, 3);
    BOOST_CHECK_EQUAL (objc.z, 5);
}
BOOST_AUTO_TEST_CASE (operator_minus2) {
    Vec3<int> obja = Vec3<int> (7, 8, 9);
    Vec3<int> objc = obja - 5;
    BOOST_CHECK_EQUAL (objc.x, 2);
    BOOST_CHECK_EQUAL (objc.y, 3);
    BOOST_CHECK_EQUAL (objc.z, 4);
}
BOOST_AUTO_TEST_CASE (operator_multiplication1) {
    Vec3<int> obja = Vec3<int> (2, 3, 5);
    Vec3<int> objb = Vec3<int> (7, 11, 13);
    Vec3<int> objc = objb * obja;
    BOOST_CHECK_EQUAL (objc.x, 14);
    BOOST_CHECK_EQUAL (objc.y, 33);
    BOOST_CHECK_EQUAL (objc.z, 65);
}
BOOST_AUTO_TEST_CASE (operator_division1) {
    Vec3<int> obja = Vec3<int> (4, 6, 8);
    Vec3<int> objb = obja / 2;
    BOOST_CHECK_EQUAL (objb.x, 2);
    BOOST_CHECK_EQUAL (objb.y, 3);
    BOOST_CHECK_EQUAL (objb.z, 4);
}
BOOST_AUTO_TEST_CASE (operator_division2) {
    Vec3<int> obja = Vec3<int> (10, 18, 45);
    Vec3<int> objb = Vec3<int> (2, 3, 5);
    Vec3<int> objc = obja / objb;
    BOOST_CHECK_EQUAL (objc.x, 5);
    BOOST_CHECK_EQUAL (objc.y, 6);
    BOOST_CHECK_EQUAL (objc.z, 9);
}
BOOST_AUTO_TEST_CASE (operator_gleich) {
    Vec3<int> obja = Vec3<int> (3, 2, 1);
    Vec3<int> objb = Vec3<int> (4, 5, 6);
    Vec3<int> objc = Vec3<int> (4, 5, 6);
    BOOST_CHECK_EQUAL (obja == objb, false);
    BOOST_CHECK_EQUAL (objb == objc, true);
}
BOOST_AUTO_TEST_CASE (operator_ungleich) {
    Vec3<int> obja = Vec3<int> (3, 2, 1);
    Vec3<int> objb = Vec3<int> (4, 5, 6);
    Vec3<int> objc = Vec3<int> (4, 5, 6);
    BOOST_CHECK_EQUAL (obja != objb, true);
    BOOST_CHECK_EQUAL (objb != objc, false);
}
BOOST_AUTO_TEST_CASE (operator_max) {
    Vec3<int> obja = Vec3<int> (10, 18, 45);
    Vec3<int> objb = Vec3<int> (2, 30, 5);
    Vec3<int> objc = Vec3<int>::max (obja, objb);
    BOOST_CHECK_EQUAL (objc.x, 10);
    BOOST_CHECK_EQUAL (objc.y, 30);
    BOOST_CHECK_EQUAL (objc.z, 45);
}
BOOST_AUTO_TEST_CASE (operator_min) {
    Vec3<int> obja = Vec3<int> (10, 18, 45);
    Vec3<int> objb = Vec3<int> (2, 30, 5);
    Vec3<int> objc = Vec3<int>::min (obja, objb);
    BOOST_CHECK_EQUAL (objc.x, 2);
    BOOST_CHECK_EQUAL (objc.y, 18);
    BOOST_CHECK_EQUAL (objc.z, 5);
}
BOOST_AUTO_TEST_CASE (length) {
    BOOST_CHECK_EQUAL (Vec3<data_type> (3, 4, 0).length (), 5);
    BOOST_CHECK_EQUAL (Vec3<data_type> (0, 3, 4).length (), 5);
    BOOST_CHECK_EQUAL (Vec3<data_type> (4, 0, 3).length (), 5);
}
BOOST_AUTO_TEST_CASE (print) {
    Vec3<data_type>   obja = Vec3<data_type> (2, 3, 4);
    std::stringstream stream;
    stream << obja;
    std::string string = stream.str ();
    BOOST_CHECK_EQUAL (string, std::string ("Vec(2,3,4)"));
}
BOOST_AUTO_TEST_CASE (test_read1) {
    Vec3<data_type>   vec;
    std::stringstream stream ("Vec(2,3,4)");
    stream >> vec;
    BOOST_CHECK_EQUAL (vec, Vec3<data_type> (2, 3, 4));
}
BOOST_AUTO_TEST_CASE (test_read2) {
    Vec3<data_type>   vec;
    std::stringstream stream ("Vec(25,36,47)");
    stream >> vec;
    BOOST_CHECK_EQUAL (vec, Vec3<data_type> (25, 36, 47));
}
