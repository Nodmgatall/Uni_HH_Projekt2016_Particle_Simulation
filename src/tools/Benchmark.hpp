/*
 * Benchmark.hpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_TOOLS_BENCHMARK_HPP_
#define SRC_TOOLS_BENCHMARK_HPP_
#include "Debug.hpp"
#include <iomanip>
#include <stack>
#include <string>
#include <sys/time.h>
#include <time.h>
class Benchmark {
    private:
    static std::stack<std::string>    m_section_names;
    static std::stack<struct timeval> m_section_starttimes;

    public:
    static void begin (std::string p_section_name);
    static void end ();
};

#endif /* SRC_TOOLS_BENCHMARK_HPP_ */
