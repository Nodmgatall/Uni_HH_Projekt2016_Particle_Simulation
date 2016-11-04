/*
 * debug.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEBUG_HPP_
#define DEBUG_HPP_
<<<<<<< HEAD

#include "Definitions.hpp"

=======
#include <fstream>
>>>>>>> 34a35cb25751b5c3786d53c9b988cfa9f9f867fe
#ifdef MAIN_CPP
std::ofstream debug_file ("log.txt");
#else
extern std::ofstream debug_file;
#endif
#define DEBUG_BEGIN debug_file << __FILE__ << ":" << __LINE__ << " -> "
#define DEBUG_VAR(var) #var << " = " << var << ", "
#define DEBUG_END std::endl

#endif /* DEBUG_HPP_ */
