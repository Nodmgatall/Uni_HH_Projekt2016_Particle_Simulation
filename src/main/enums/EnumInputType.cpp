/*
 * EnumInputType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "enums/EnumInputType.hpp"

std::vector<const char*> g_input_names = { "UNDEFINED",
                                           "GENERATOR_RANDOM",
                                           "GENERATOR_RANDOM_UNIFORM",
                                           "GENERATOR_SINGLE_OBJECT_MIDDLE",
                                           "GENERATOR_GRID_DISTRIBUTION",
                                           "GENERATOR_MULTIPLE_OBJECTS",
                                           "FILE_CSV" };

std::ostream& operator<< (std::ostream& stream, const e_input_type p_input_type) {
    int index = static_cast<int> (p_input_type);
    if ((index < (signed) g_input_names.size ()) && (index > 0))
        return stream << g_input_names[index];
    else
        throw InputTypeInvalidException (p_input_type);
}
