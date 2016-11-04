/*
 * debug.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <fstream>
#include <iostream>

struct OutputAndConsole : std::ofstream
{
};

template <typename T>
OutputAndConsole& operator<<(OutputAndConsole& strm, const T& var)
{
	std::cout << var;
    static_cast<std::ofstream&>(strm) << var;
    return strm;
}



EXTERN OutputAndConsole debug_file;

#ifdef RELEASE
#define DEBUG_BEGIN if (1) {} else debug_file
#else
#define DEBUG_BEGIN debug_file << __FILE__ << ":" << __LINE__ << " -> "
#endif
#define DEBUG_VAR(var) #var << " = " << var << ", "
#define DEBUG_END std::endl

#endif /* DEBUG_HPP_ */
