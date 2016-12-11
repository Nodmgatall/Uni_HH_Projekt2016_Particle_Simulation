/*
 * EnumInputType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "enums/EnumInputType.hpp"

std::vector<const char*> g_input_names =
    { "UNDEFINED",        "RANDOM", "RANDOM_UNIFORM", "SINGLE_OBJECT_MIDDLE", "GRID_DISTRIBUTION",
      "MULTIPLE_OBJECTS", "CSV" };

std::ostream& operator<< (std::ostream& stream, const e_input_type p_input_type) {
    int index = static_cast<int> (p_input_type);
    if ((index < (signed) g_input_names.size ()) && (index > 0))
        return stream << g_input_names[index];
    else
        throw InputTypeInvalidException (p_input_type);
}
