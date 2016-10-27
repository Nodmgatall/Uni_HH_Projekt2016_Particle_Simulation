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
void _debug_var (T v) {
	debug_file << v << std::endl;
}
template <typename T, typename... Args>
void _debug_var (T v, Args... args) {
	debug_file << v << ", ";
	_debug_var (args...);
}
template <typename... Args>
void debug_var (Args... args) {
	debug_file << __FILE__ << ":" << __LINE__ << " -> ";
	_debug_var (args...);
}
#endif /* DEBUG_HPP_ */
