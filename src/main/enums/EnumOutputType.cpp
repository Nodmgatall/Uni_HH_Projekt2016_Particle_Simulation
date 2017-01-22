/*
 * EnumOutputType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */
#include "enums/EnumOutputType.hpp"
std::vector<const char*> g_output_names       = { "UNDEFINED", "FILE_CSV", "FILE_LAMMPS", "FILE_ESPRESSO", "FILE_GROMACS", "FILE_VMD", "FILE_VTK", "FILE_CSV+AVI" };
std::vector<bool>        g_output_implemented = { false, true, false, false, false, false, false, true };
std::ostream& operator<< (std::ostream& stream, const e_output_type& p_output_type) {
    int index = static_cast<int> (p_output_type);
    if ((index < (signed) g_output_names.size ()) && (index > 0))
        return stream << g_output_names[index];
    else
        throw OutputTypeInvalidException (p_output_type);
}
std::istream& operator>> (std::istream& stream, e_output_type& p_output_type) {
    std::string name;
    stream >> name;
    unsigned int index;
    for (index = 0; index < g_output_names.size (); index++)
        if (0 == strcmp (g_output_names[index], name.c_str ())) {
            p_output_type = static_cast<e_output_type> (index);
        }
    return stream;
}
