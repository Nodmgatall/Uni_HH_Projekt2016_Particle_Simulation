/*
 * EnumAlgorithmType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "enums/EnumAlgorithmType.hpp"

std::vector<const char*> g_algorithm_names = { "UNDEFINED",
                                               "LENNARD_JONES",
                                               "SMOTHED_PARTICLE_HYDRODYNAMICS",
                                               "DISSIPATIVE_PARTICLE_DYNAMICS" };

std::ostream& operator<< (std::ostream& stream, const e_algorithm_type p_algorithm_type) {
    int index = static_cast<int> (p_algorithm_type);
    if ((index < (signed) g_algorithm_names.size ()) && (index > 0))
        return stream << g_algorithm_names[index];
    else
        throw AlgorithmTypeInvalidException (p_algorithm_type);
}
