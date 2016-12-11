/*
 * EnumOutputType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "../enums/EnumOutputType.hpp"

const char* g_output_names[] = { "UNDEFINED",
                                 "CSV",
                                 "LAMMPS",
                                 "ESPRESSO",
                                 "GROMACS",
                                 "VMD",
                                 "VT"
                                 "K" };

std::ostream& operator<< (std::ostream& stream, const e_output_type p_output_type) {
    switch (p_output_type) {
        case e_output_type::CSV:
        case e_output_type::LAMMPS:
        case e_output_type::ESPRESSO:
        case e_output_type::GROMACS:
        case e_output_type::VMD:
        case e_output_type::VTK:
            return stream << g_output_names[static_cast<int> (p_output_type)];
        default:
            throw OutputTypeInvalidException (p_output_type);
    }
}
