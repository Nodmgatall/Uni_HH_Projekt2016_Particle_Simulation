/*
 * EnumOutputFormat.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUMOUTPUTFORMAT_HPP_
#define SRC_MAIN_OPTIONS_ENUMOUTPUTFORMAT_HPP_

#include <ostream>

enum e_output_format { CSV = 1, LAMMPS = 2, ESPRESSO = 3, GROMACS = 4, VMD = 5, VTK = 6 };

std::ostream& operator<< (std::ostream& stream, const e_output_format p_output_format);

extern const char* g_output_names[];

class OutputFormatInvalidException : public std::exception {
  private:
    e_output_format m_output_format;

  public:
    OutputFormatInvalidException () : m_output_format ((e_output_format) 0) {
    }
    OutputFormatInvalidException (e_output_format p_output_format)
    : m_output_format (p_output_format) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "algorithm type ( %s ) is invalid", g_output_names[m_output_format]);
        return text;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMOUTPUTFORMAT_HPP_ */
