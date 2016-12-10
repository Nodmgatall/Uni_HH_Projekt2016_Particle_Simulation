/*
 * EnumGeneratorType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumGeneratorType.hpp"

const char* g_generator_names[] = { "UNDEFINED",         "RANDOM",
                                    "RANDOM_UNIFORM",    "SINGLE_OBJECT_MIDDLE",
                                    "GRID_DISTRIBUTION", "MULTIPLE_OBJECTS" };

std::ostream& operator<< (std::ostream& stream, const e_generator_type p_generator_type) {
    switch (p_generator_type) {
        case e_generator_type::RANDOM:
        case e_generator_type::RANDOM_UNIFORM:
        case e_generator_type::SINGLE_OBJECT_MIDDLE:
        case e_generator_type::GRID_DISTRIBUTION:
        case e_generator_type::MULTIPLE_OBJECTS:
            return stream << g_generator_names[p_generator_type - 1];
        default:
            throw GeneratorTypeInvalidException (p_generator_type);
    }
}
