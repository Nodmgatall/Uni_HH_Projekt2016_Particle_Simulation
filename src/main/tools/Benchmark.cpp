/*
 * Benchmark.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "Benchmark.hpp"
std::stack<std::string> Benchmark::m_section_names      = std::stack<std::string> ();
std::stack<data_type>   Benchmark::m_section_starttimes = std::stack<data_type> ();
std::stack<bool>        Benchmark::m_section_print      = std::stack<bool> ();
void Benchmark::begin (std::string p_section_name, bool p_print) {
    if (p_print) {
        m_verbose_stream << ">>>" << p_section_name << " :: starting" << std::endl;
    }
    m_section_names.push (p_section_name);
    m_section_starttimes.push (omp_get_wtime ());
    m_section_print.push (p_print);
}
void Benchmark::end () {
    std::string section_name;
    data_type   time_diff;
    bool        print;
    time_diff    = omp_get_wtime () - m_section_starttimes.top ();
    section_name = m_section_names.top ();
    print        = m_section_print.top ();
    m_section_names.pop ();
    m_section_starttimes.pop ();
    m_section_print.pop ();
    if (print) {
        m_verbose_stream << "<<<" << section_name << " :: finished in " << time_diff << "s" << std::endl;
    } else {
        m_verbose_stream << "---spend " << time_diff << "s for " << section_name << std::endl;
    }
}
