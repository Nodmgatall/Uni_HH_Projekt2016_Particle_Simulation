/*
 * debug.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEBUG_HPP_
#define DEBUG_HPP_
#include "../Definitions.hpp"
#include "../Vec3.hpp"
#include <fstream>
#include <iostream>
template <typename T>
std::ostream& operator<< (std::ostream& stream, const std::vector<T>& array) {
    stream << "[";
    for (unsigned int i = 0; i < array.size (); i++) {
        stream << array[i] << ",";
    }
    stream << "]";
    return stream;
}
template <typename T>
std::ostream& operator<< (std::ostream& stream, const std::vector<T> array[2]) {
    stream << "[" << array[0] << "," << array[1] << "]";
    return stream;
}
extern char log_folder[29];
extern bool g_verbose;
#if !defined(RELEASE)
#define DEBUG_ELIMINATOR if (0)
#elif defined(DEBUG)
#define DEBUG_ELIMINATOR if (0)
#else
#define DEBUG_ELIMINATOR if (1)
#endif
#define VERBOSE_ELIMINATOR if (g_verbose)
#define m_standard_stream std::cout
#define m_error_stream std::cerr
#define m_debug_stream DEBUG_ELIMINATOR     std::cout
#define m_verbose_stream VERBOSE_ELIMINATOR std::cout
#define macro_debug_1(x) m_debug_stream << x << std::endl;
#define macro_debug(x, y) m_debug_stream << x << " = " << y << std::endl;
#define DEBUG_VAR(var) #var << " = " << var
#endif /* DEBUG_HPP_ */
