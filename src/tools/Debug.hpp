/*
 * debug.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <fstream>
EXTERN std::ofstream debug_file;
#define DEBUG_BEGIN debug_file << __FILE__ << ":" << __LINE__ << " -> "
#define DEBUG_VAR(var) #var << " = " << var << ", "
#define DEBUG_END std::endl

#endif /* DEBUG_HPP_ */
