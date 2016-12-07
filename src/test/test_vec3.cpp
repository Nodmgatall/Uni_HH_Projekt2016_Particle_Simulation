#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "vec3f"
#include "vec3.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (constructors1) {
    vec3<int> obj = vec3<int> (3);
    BOOST_CHECK_EQUAL (obj.x, 3);
    BOOST_CHECK_EQUAL (obj.y, 3);
    BOOST_CHECK_EQUAL (obj.z, 3);
}
BOOST_AUTO_TEST_CASE (constructors2) {
    vec3<int> obj = vec3<int> (3, 4, 5);
    BOOST_CHECK_EQUAL (obj.x, 3);
    BOOST_CHECK_EQUAL (obj.y, 4);
    BOOST_CHECK_EQUAL (obj.z, 5);
}
BOOST_AUTO_TEST_CASE (constructors3) {
    vec3<int> obj = vec3<int> ();
    BOOST_CHECK_EQUAL (obj.x, 0);
    BOOST_CHECK_EQUAL (obj.y, 0);
    BOOST_CHECK_EQUAL (obj.z, 0);
}
BOOST_AUTO_TEST_CASE (constructors4) {
    vec3<float> objf = vec3<float> (3.5, 4.6, 5.5);
    vec3<int>   obj  = vec3<int> (objf);
    BOOST_CHECK_EQUAL (obj.x, 3);
    BOOST_CHECK_EQUAL (obj.y, 4);
    BOOST_CHECK_EQUAL (obj.z, 5);
}
BOOST_AUTO_TEST_CASE (operator_plus) {
    vec3<int> obja = vec3<int> (1, 2, 3);
    vec3<int> objb = vec3<int> (4, 5, 6);
    vec3<int> objc = obja + objb;
    BOOST_CHECK_EQUAL (objc.x, 5);
    BOOST_CHECK_EQUAL (objc.y, 7);
    BOOST_CHECK_EQUAL (objc.z, 9);
}
BOOST_AUTO_TEST_CASE (operator_plus_gleich1) {
    vec3<int> obja = vec3<int> (1, 2, 3);
    vec3<int> objb = vec3<int> (4, 5, 6);
    objb += obja;
    BOOST_CHECK_EQUAL (objb.x, 5);
    BOOST_CHECK_EQUAL (objb.y, 7);
    BOOST_CHECK_EQUAL (objb.z, 9);
}
BOOST_AUTO_TEST_CASE (operator_plus_gleich2) {
    vec3<int> obj = vec3<int> (4, 5, 6);
    obj += 5;
    BOOST_CHECK_EQUAL (obj.x, 9);
    BOOST_CHECK_EQUAL (obj.y, 10);
    BOOST_CHECK_EQUAL (obj.z, 11);
}
BOOST_AUTO_TEST_CASE (operator_minus1) {
    vec3<int> obja = vec3<int> (3, 2, 1);
    vec3<int> objb = vec3<int> (4, 5, 6);
    vec3<int> objc = objb - obja;
    BOOST_CHECK_EQUAL (objc.x, 1);
    BOOST_CHECK_EQUAL (objc.y, 3);
    BOOST_CHECK_EQUAL (objc.z, 5);
}
BOOST_AUTO_TEST_CASE (operator_minus2) {
    vec3<int> obja = vec3<int> (7, 8, 9);
    vec3<int> objc = obja - 5;
    BOOST_CHECK_EQUAL (objc.x, 2);
    BOOST_CHECK_EQUAL (objc.y, 3);
    BOOST_CHECK_EQUAL (objc.z, 4);
}
BOOST_AUTO_TEST_CASE (operator_multiplication1) {
    vec3<int> obja = vec3<int> (2, 3, 5);
    vec3<int> objb = vec3<int> (7, 11, 13);
    vec3<int> objc = objb * obja;
    BOOST_CHECK_EQUAL (objc.x, 14);
    BOOST_CHECK_EQUAL (objc.y, 33);
    BOOST_CHECK_EQUAL (objc.z, 65);
}
BOOST_AUTO_TEST_CASE (operator_division1) {
    vec3<int> obja = vec3<int> (4, 6, 8);
    vec3<int> objb = obja / 2;
    BOOST_CHECK_EQUAL (objb.x, 2);
    BOOST_CHECK_EQUAL (objb.y, 3);
    BOOST_CHECK_EQUAL (objb.z, 4);
}
BOOST_AUTO_TEST_CASE (operator_division2) {
    vec3<int> obja = vec3<int> (10, 18, 45);
    vec3<int> objb = vec3<int> (2, 3, 5);
    vec3<int> objc = objb / obja;
    BOOST_CHECK_EQUAL (objc.x, 5);
    BOOST_CHECK_EQUAL (objc.y, 6);
    BOOST_CHECK_EQUAL (objc.z, 9);
}
BOOST_AUTO_TEST_CASE (operator_gleich) {
    vec3<int> obja = vec3<int> (3, 2, 1);
    vec3<int> objb = vec3<int> (4, 5, 6);
    vec3<int> objc = vec3<int> (4, 5, 6);
    BOOST_CHECK_EQUAL (obja == objb, false);
    BOOST_CHECK_EQUAL (objb == objc, true);
}
BOOST_AUTO_TEST_CASE (operator_ungleich) {
    vec3<int> obja = vec3<int> (3, 2, 1);
    vec3<int> objb = vec3<int> (4, 5, 6);
    vec3<int> objc = vec3<int> (4, 5, 6);
    BOOST_CHECK_EQUAL (obja != objb, true);
    BOOST_CHECK_EQUAL (objb != objc, false);
}
BOOST_AUTO_TEST_CASE (operator_max) {
    vec3<int> obja = vec3<int> (10, 18, 45);
    vec3<int> objb = vec3<int> (2, 30, 5);
    vec3<int> objc = vec3<int>::max (obja, objb);
    BOOST_CHECK_EQUAL (objc.x, 10);
    BOOST_CHECK_EQUAL (objc.y, 30);
    BOOST_CHECK_EQUAL (objc.z, 45);
}
BOOST_AUTO_TEST_CASE (operator_min) {
    vec3<int> obja = vec3<int> (10, 18, 45);
    vec3<int> objb = vec3<int> (2, 30, 5);
    vec3<int> objc = vec3<int>::min (obja, objb);
    BOOST_CHECK_EQUAL (objc.x, 2);
    BOOST_CHECK_EQUAL (objc.y, 18);
    BOOST_CHECK_EQUAL (objc.z, 5);
}
