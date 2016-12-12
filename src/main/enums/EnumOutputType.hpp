/*
 * EnumOutputType.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUM_OUTPUT_TYPE_HPP_
#define SRC_MAIN_OPTIONS_ENUM_OUTPUT_TYPE_HPP_

#include <cstring>
#include <exception>
#include <ostream>
#include <vector>

enum class e_output_type {
    FILE_CSV      = 1,
    FILE_LAMMPS   = 2,
    FILE_ESPRESSO = 3,
    FILE_GROMACS  = 4,
    FILE_VMD      = 5,
    FILE_VTK      = 6
};

std::ostream& operator<< (std::ostream& stream, const e_output_type& p_output_type);
std::istream& operator>> (std::istream& stream, e_output_type& p_output_type);

extern std::vector<const char*> g_output_names;

class OutputTypeInvalidException : public std::exception {
  private:
    e_output_type m_output_type;

  public:
    OutputTypeInvalidException () : m_output_type ((e_output_type) 0) {
    }
    OutputTypeInvalidException (e_output_type p_output_type) : m_output_type (p_output_type) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "output type ( %s ) is invalid", g_output_names[static_cast<int> (m_output_type)]);
        return text;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMOUTPUTFORMAT_HPP_ */
