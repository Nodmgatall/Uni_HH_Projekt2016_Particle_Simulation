/*
 * EnumOutputType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumOutputType.hpp"

const char* g_output_names[] = { "CSV", "LAMMPS", "ESPRESSO", "GROMACS", "VMD", "VTK" };

std::ostream& operator<< (std::ostream& stream, const e_output_type p_output_type) {
    switch (p_output_type) {
        case e_output_type::CSV:
        case e_output_type::LAMMPS:
        case e_output_type::ESPRESSO:
        case e_output_type::GROMACS:
        case e_output_type::VMD:
        case e_output_type::VTK:
            return stream << g_output_names[p_output_type - 1];
        default:
            throw OutputTypeInvalidException (p_output_type);
    }
}
