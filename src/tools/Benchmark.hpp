/*
 * Benchmark.hpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_TOOLS_BENCHMARK_HPP_
#define SRC_TOOLS_BENCHMARK_HPP_
#include "Debug.hpp"
#include <stack>
#include <string>
class Benchmark {
    private:
    static std::stack<std::string> m_section_names;

    public:
    static void begin (std::string p_section_name);
    static void end ();
};

#endif /* SRC_TOOLS_BENCHMARK_HPP_ */
