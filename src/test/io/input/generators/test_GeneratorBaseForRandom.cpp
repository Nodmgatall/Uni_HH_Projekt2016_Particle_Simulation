/*
 * test_GeneratorBaseForRandom.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef BOOST_TEST_DYN_LINK
#include "io/input/generators/GeneratorRandom.hpp"
typedef GeneratorRandom GeneratorUnderTest;
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "GeneratorBaseRandom"
#include "io/input/generators/test_GeneratorBase.hpp"
#endif
