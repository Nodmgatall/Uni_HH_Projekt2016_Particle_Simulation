/*
 * EnumInputType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "../enums/EnumInputType.hpp"

const char* g_input_names[] =
    { "UNDEFINED",        "RANDOM", "RANDOM_UNIFORM", "SINGLE_OBJECT_MIDDLE", "GRID_DISTRIBUTION",
      "MULTIPLE_OBJECTS", "CSV" };

std::ostream& operator<< (std::ostream& stream, const e_input_type p_input_type) {
    switch (p_input_type) {
        case e_input_type::RANDOM:
        case e_input_type::RANDOM_UNIFORM:
        case e_input_type::SINGLE_OBJECT_MIDDLE:
        case e_input_type::GRID_DISTRIBUTION:
        case e_input_type::MULTIPLE_OBJECTS:
        case e_input_type::CSV:
            return stream << g_input_names[static_cast<int> (p_input_type)];
        default:
            throw InputTypeInvalidException (p_input_type);
    }
}
