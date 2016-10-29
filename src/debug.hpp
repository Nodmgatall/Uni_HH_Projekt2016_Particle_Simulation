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
std::ofstream debug_file ("log.txt");
#else
extern std::ofstream debug_file;
#endif
template <typename T>
void _debug (T v) {
	debug_file << v << std::endl;
}
template <typename T, typename... Args>
void _debug (T v, Args... args) {
	debug_file << v << ", ";
	_debug (args...);
}
template <typename... Args>
void debug (Args... args) {
	debug_file << __FILE__ << ":" << __LINE__ << " -> ";
	_debug (args...);
}
#endif /* DEBUG_HPP_ */
