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
    /**
     * stack of current section-names
     */
    static std::stack<std::string> m_section_names;
    /**
     * times when the corresponding section started
     */
    static std::stack<struct timeval> m_section_starttimes;
    /**
     * if the section print its time only after the section finishes or if the print statements
     * between begin and end should be indented
     */
    static std::stack<bool> m_section_print;
  public:
    /**
     * beginns the next section of time-mesurement
     */
    static void begin (std::string p_section_name, bool p_print = true);
    /**
     * ends the current time mesurement section
     */
    static void end ();
};
#endif /* SRC_TOOLS_BENCHMARK_HPP_ */
