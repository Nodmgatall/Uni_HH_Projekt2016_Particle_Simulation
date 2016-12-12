/*
 * debug.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include "Definitions.hpp"
#include "Vec3.hpp"
#include <fstream>
#include <iostream>

struct s_file_and_console_stream : std::ofstream {
    int         m_indent_count;
    bool        m_last_char_was_std_endl;
    std::string m_file_and_line;
    s_file_and_console_stream ()
    : m_indent_count (0), m_last_char_was_std_endl (true),
      m_file_and_line (std::string (__FILE__) + ":" + std::to_string (__LINE__) + " -> ") {
    }
    s_file_and_console_stream& operator<< (std::ostream& (*manipulator) (std::ostream&) ) {
        manipulator (std::cout);
        manipulator (static_cast<std::ofstream&> (*this));
        m_last_char_was_std_endl = true;
        return *this;
    }

    template <typename T>
    void print (const T& var) {
        if (m_last_char_was_std_endl) {
            std::cout << std::string (m_indent_count * 4, ' ');
            static_cast<std::ofstream&> (*this) << m_file_and_line << std::string (m_indent_count * 4, ' ');
        }
        std::cout << var;
        static_cast<std::ofstream&> (*this) << var;
        m_last_char_was_std_endl = false;
    }
    //////////////////////////////////////////////////////////////////////
    // veränderter output --->>>>
    //////////////////////////////////////////////////////////////////////
    s_file_and_console_stream& operator<< (const bool& var) {
        print (var ? "ON" : "OFF");
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    //<<<<--- veränderter output
    //////////////////////////////////////////////////////////////////////
    template <typename T>
    s_file_and_console_stream& operator<< (const T& var) {
        print (var);
        return *this;
    }
    template <typename T>
    s_file_and_console_stream& operator>> (const T& var) {
        static_cast<std::ofstream&> (*this) << var;
        return *this;
    }
    void indent () {
        if (m_indent_count < 20)
            m_indent_count++;
    }
    void unindent () {
        if (m_indent_count > 0)
            m_indent_count--;
    }

    s_file_and_console_stream& set_file_and_line (const char* p_file, long p_line) {
        m_file_and_line = std::string (p_file) + ":" + std::to_string (p_line) + " -> ";
        ;
        return *this;
    }
};

extern char                      log_folder[29];
extern s_file_and_console_stream g_debug_stream;

#if !defined(RELEASE)
#define DEBUG_ELIMINATOR if (0)
#elif defined(DEBUG)
#define DEBUG_ELIMINATOR if (0)
#else
#define DEBUG_ELIMINATOR if (1)
#endif

#define m_debug_stream DEBUG_ELIMINATOR g_debug_stream.set_file_and_line (__FILE__, __LINE__)
#define m_verbose_stream g_debug_stream.set_file_and_line (__FILE__, __LINE__)
#define m_standard_stream g_debug_stream.set_file_and_line (__FILE__, __LINE__)
#define m_error_stream g_debug_stream.set_file_and_line (__FILE__, __LINE__)

#ifndef RELEASE
#define macro_debug_1(x) g_debug_stream.set_file_and_line (__FILE__, __LINE__) << x << std::endl;
#define macro_debug(x, y) \
    g_debug_stream.set_file_and_line (__FILE__, __LINE__) << " : " << x << " = " << y << std::endl;

#else

#define macro_debug(x, y)
#define macro_debug_2(x, y)

#endif

#define DEBUG_VAR(var) #var << " = " << var
#endif /* DEBUG_HPP_ */
