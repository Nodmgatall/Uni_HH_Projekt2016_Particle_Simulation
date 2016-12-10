/*
 * EnumGeneratorMode.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumGeneratorMode.hpp"

const char* g_generator_names[] = { "UNDEFINED",         "RANDOM",
                                    "RANDOM_UNIFORM",    "SINGLE_OBJECT_MIDDLE",
                                    "GRID_DISTRIBUTION", "MULTIPLE_OBJECTS" };

std::ostream& operator<< (std::ostream& stream, const e_generator_mode p_generator_mode) {
    switch (p_generator_mode) {
        case e_generator_mode::RANDOM:
        case e_generator_mode::RANDOM_UNIFORM:
        case e_generator_mode::SINGLE_OBJECT_MIDDLE:
        case e_generator_mode::GRID_DISTRIBUTION:
        case e_generator_mode::MULTIPLE_OBJECTS:
            return stream << g_generator_names[p_generator_mode];
        default:
            throw GeneratorModeInvalidException (p_generator_mode);
    }
}
