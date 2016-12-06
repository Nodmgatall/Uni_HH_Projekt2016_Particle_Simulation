// Link to Boost
#define BOOST_TEST_DYN_LINK

// Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "vec3f"

// VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "vec3.hpp"
// ------------- Tests Follow --------------
BOOST_AUTO_TEST_CASE (constructors) {
    vec3<int> obj (3);
    BOOST_CHECK_EQUAL (obj.x, 3);
    BOOST_CHECK_EQUAL (obj.y, 3);
    BOOST_CHECK_EQUAL (obj.z, 3);
    printf ("a");
}
