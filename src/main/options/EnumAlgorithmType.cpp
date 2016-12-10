/*
 * EnumAlgorithmType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumAlgorithmType.hpp"

const char* g_algorithm_names[] = { "UNDEFINED", "LENNARD_JONES", "SMOTHED_PARTICLE_HYDRODYNAMICS", "DISSIPATIVE_PARTICLE_DYNAMICS" };

std::ostream& operator<< (std::ostream& stream, const e_algorithm_type p_algorithm_type) {
    switch (p_algorithm_type) {
        case e_algorithm_type::LENNARD_JONES:
        case e_algorithm_type::SMOTHED_PARTICLE_HYDRODYNAMICS:
        case e_algorithm_type::DISSIPATIVE_PARTICLE_DYNAMICS:
            return stream << g_algorithm_names[static_cast<int> (p_algorithm_type) - 1];
        default:
            throw AlgorithmTypeInvalidException (p_algorithm_type);
    }
}
