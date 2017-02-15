/*
 * EnumAlgorithmType.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "enums/EnumAlgorithmType.hpp"
std::vector<const char*> g_algorithm_names       = { "UNDEFINED", "LENNARD_JONES", "SMOTHED_PARTICLE_HYDRODYNAMICS", "DISSIPATIVE_PARTICLE_DYNAMICS" };
std::vector<bool>        g_algorithm_implemented = { false, true, false, false };
std::ostream& operator<< (std::ostream& stream, const e_algorithm_type& p_algorithm_type) {
    int index = static_cast<int> (p_algorithm_type);
    if ((index < (signed) g_algorithm_names.size ()) && (index > 0))
        return stream << g_algorithm_names[index];
    else
        throw AlgorithmTypeInvalidException (p_algorithm_type);
}
std::istream& operator>> (std::istream& stream, e_algorithm_type& p_algorithm_type) {
    std::string name;
    stream >> name;
    unsigned int index;
    for (index = 0; index < g_algorithm_names.size (); index++)
        if (0 == strcmp (g_algorithm_names[index], name.c_str ())) {
            p_algorithm_type = static_cast<e_algorithm_type> (index);
        }
    return stream;
}
