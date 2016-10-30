/*
 * debug.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEBUG_HPP_
#define DEBUG_HPP_
#include "definitions.hpp"
#ifdef MAIN_CPP
ofstream debug_file ("log.txt");
#else
extern ofstream debug_file;
#endif
#define DEBUG_BEGIN debug_file << __FILE__ << ":" << __LINE__ << " -> "
#define DEBUG_VAR(var) #var << " = " << var << ", "
#define DEBUG_END std::endl

#endif /* DEBUG_HPP_ */
