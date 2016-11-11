/*
 * Benchmark.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "Benchmark.hpp"

std::stack<std::string>    Benchmark::m_section_names      = std::stack<std::string> ();
std::stack<struct timeval> Benchmark::m_section_starttimes = std::stack<struct timeval> ();
std::stack<bool>           Benchmark::m_section_print      = std::stack<bool> ();

void Benchmark::begin (std::string p_section_name, bool p_print) {
    if (p_print) {
        DEBUG_BEGIN << ">>>" << p_section_name << " :: starting" << DEBUG_END;
        g_debug_stream.indent ();
    }
    struct timeval time_now;
    gettimeofday (&time_now, NULL);
    m_section_names.push (p_section_name);
    m_section_starttimes.push (time_now);
    m_section_print.push (p_print);
}

void Benchmark::end () {
    std::string    section_name;
    struct timeval time_begin, time_now;
    float          time_diff;
    bool           print;
    section_name = m_section_names.top ();
    time_begin   = m_section_starttimes.top ();
    print        = m_section_print.top ();
    m_section_names.pop ();
    m_section_starttimes.pop ();
    m_section_print.pop ();
    gettimeofday (&time_now, NULL);
    if (print)
        g_debug_stream.unindent ();
    time_diff = ((time_now.tv_sec - time_begin.tv_sec) * 1000000u + time_now.tv_usec - time_begin.tv_usec) / 1.e6;
    if (print) {
        DEBUG_BEGIN << "<<<" << section_name << " :: finished in " << std::fixed
                    << std::setprecision (6) << std::setfill ('0') << time_diff << "s" << DEBUG_END;
    } else {
        DEBUG_BEGIN << "---spend " << std::fixed << std::setprecision (6) << std::setfill ('0')
                    << time_diff << "s for " << section_name << DEBUG_END;
    }
}
