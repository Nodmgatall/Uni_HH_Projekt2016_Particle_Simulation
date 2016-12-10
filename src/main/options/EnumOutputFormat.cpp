/*
 * EnumOutputFormat.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumOutputFormat.hpp"

const char* g_output_names[] = { "CSV", "LAMMPS", "ESPRESSO", "GROMACS", "VMD", "VTK" };

std::ostream& operator<< (std::ostream& stream, const e_output_format p_output_format) {
    switch (p_output_format) {
        case e_output_format::CSV:
        case e_output_format::LAMMPS:
        case e_output_format::ESPRESSO:
        case e_output_format::GROMACS:
        case e_output_format::VMD:
        case e_output_format::VTK:
            return stream << g_output_names[p_output_format];
        default:
            throw OutputFormatInvalidException (p_output_format);
    }
}
