/*
 * Benchmark.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#include "Benchmark.hpp"

std::stack<std::string> Benchmark::m_section_names = std::stack<std::string> ();

void Benchmark::begin (std::string p_section_name) {
    m_section_names.push (p_section_name);
    DEBUG_BEGIN << p_section_name << " :: starting" << DEBUG_END;
    g_debug_stream.indent ();
}

void Benchmark::end () {
    std::string section_name = m_section_names.top ();
    m_section_names.pop ();
    g_debug_stream.unindent ();
    DEBUG_BEGIN << section_name << " :: finish" << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
}
