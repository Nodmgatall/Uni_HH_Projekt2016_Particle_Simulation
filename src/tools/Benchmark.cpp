/*
 * Benchmark.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "Benchmark.hpp"

std::stack<std::string>    Benchmark::m_section_names      = std::stack<std::string> ();
std::stack<struct timeval> Benchmark::m_section_starttimes = std::stack<struct timeval> ();

void Benchmark::begin (std::string p_section_name) {
    struct timeval time_now;
    DEBUG_BEGIN << p_section_name << " :: starting" << DEBUG_END;
    g_debug_stream.indent ();
    gettimeofday (&time_now, NULL);
    m_section_names.push (p_section_name);
    m_section_starttimes.push (time_now);
}

void Benchmark::end () {
    std::string    section_name;
    struct timeval time_begin, time_now;
    float          time_diff;
    section_name = m_section_names.top ();
    time_begin   = m_section_starttimes.top ();
    m_section_names.pop ();
    m_section_starttimes.pop ();
    gettimeofday (&time_now, NULL);
    g_debug_stream.unindent ();
    time_diff = ((time_now.tv_sec - time_begin.tv_sec) * 1000000u + time_now.tv_usec - time_begin.tv_usec) / 1.e6;
    DEBUG_BEGIN << section_name << " :: finished in " << std::fixed << std::setprecision (6)
                << std::setfill ('0') << time_diff << "s" << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
}
