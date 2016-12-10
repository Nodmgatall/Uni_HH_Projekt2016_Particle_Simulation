/*
 * EnumInputType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumInputType.hpp"

const char* g_input_names[] = { "UNDEFINED",         "RANDOM",
                                "RANDOM_UNIFORM",    "SINGLE_OBJECT_MIDDLE",
                                "GRID_DISTRIBUTION", "MULTIPLE_OBJECTS" };

std::ostream& operator<< (std::ostream& stream, const e_input_type p_input_type) {
    switch (p_input_type) {
        case e_input_type::RANDOM:
        case e_input_type::RANDOM_UNIFORM:
        case e_input_type::SINGLE_OBJECT_MIDDLE:
        case e_input_type::GRID_DISTRIBUTION:
        case e_input_type::MULTIPLE_OBJECTS:
            return stream << g_input_names[p_input_type - 1];
        default:
            throw InputTypeInvalidException (p_input_type);
    }
}