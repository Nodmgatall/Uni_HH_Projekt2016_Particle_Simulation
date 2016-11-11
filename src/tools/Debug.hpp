/*
 * debug.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include "../Definitions.hpp"
#include <fstream>
#include <iostream>

struct s_debug_stream : std::ofstream {
    int  m_indent_count;
    bool m_last_char_was_std_endl;
    s_debug_stream () : m_indent_count (0), m_last_char_was_std_endl (true) {
    }
    s_debug_stream &operator<< (std::ostream &(*manipulator) (std::ostream &) ) {
        manipulator (std::cout);
        manipulator (static_cast<std::ofstream &> (*this));
        m_last_char_was_std_endl = true;
        return *this;
    }

    template <typename T>
    void print (const T &var) {
        if (m_last_char_was_std_endl) {
            std::cout << std::string (m_indent_count * 4, ' ');
            static_cast<std::ofstream &> (*this) << std::string (m_indent_count * 4, ' ');
        }
        std::cout << var;
        static_cast<std::ofstream &> (*this) << var;
        m_last_char_was_std_endl = false;
    }
    //////////////////////////////////////////////////////////////////////
    // veränderter output --->>>>
    //////////////////////////////////////////////////////////////////////
    s_debug_stream &operator<< (const bool &var) {
        print (var ? "ON" : "OFF");
        return *this;
    }
    s_debug_stream &operator<< (const glm::vec3 &var) {
        print ("(");
        print (var.x);
        print (",");
        print (var.y);
        print (",");
        print (var.z);
        print (")");
        return *this;
    }
    s_debug_stream &operator<< (const e_generator_mode &var) {
        print (g_enum_generator_mode_to_string_map[var]);
        return *this;
    }
    s_debug_stream &operator<< (const e_algorithm_type &var) {
        print (g_enum_algorithm_type_to_string_map[var]);
        return *this;
    }
    s_debug_stream &operator<< (const e_data_format &var) {
        print (g_enum_data_format_to_string_map[var]);
        return *this;
    }
    s_debug_stream &operator<< (const e_particle_variable &var) {
        print (g_enum_particle_variable_to_string_map[var]);
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    //<<<<--- veränderter output
    //////////////////////////////////////////////////////////////////////
    template <typename T>
    s_debug_stream &operator<< (const T &var) {
        print (var);
        return *this;
    }
    template <typename T>
    s_debug_stream &operator>> (const T &var) {
        static_cast<std::ofstream &> (*this) << var;
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
};
EXTERN char log_folder[29];
EXTERN s_debug_stream g_debug_stream;

#ifndef RELEASE
#define macro_debug_1(x) g_debug_stream >> __FILE__ >> ":" >> __LINE__ >> " : " << x << std::endl;
#define macro_debug(x, y) \
    g_debug_stream >> __FILE__ >> ":" >> __LINE__ >> " : " << x << " = " << y << std::endl

#define DEBUG_BEGIN g_debug_stream >> __FILE__ >> ":" >> __LINE__ >> " -> "

#else

#define macro_debug(x, y)
#define macro_debug_2(x, y)
#define DEBUG_BEGIN \
    if (0)          \
    g_debug_stream >> __FILE__ >> ":" >> __LINE__ >> " -> "

#endif

#define DEBUG_VAR(var) #var << " = " << var
#define DEBUG_END std::endl
#define DEBUG_ENDL std::endl << std::endl
#endif /* DEBUG_HPP_ */
