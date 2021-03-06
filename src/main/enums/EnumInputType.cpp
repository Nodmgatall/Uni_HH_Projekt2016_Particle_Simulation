/*
 * EnumInputType.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "enums/EnumInputType.hpp"
std::vector<const char*> g_input_names = { "UNDEFINED",
                                           "GENERATOR_RANDOM",
                                           "GENERATOR_RANDOM_UNIFORM",
                                           "GENERATOR_SINGLE_OBJECT_MIDDLE",
                                           "GENERATOR_GRID_DISTRIBUTION",
                                           "GENERATOR_MULTIPLE_OBJECTS",
                                           "FILE_CSV",
                                           "AUTOTUNING_REGULAR_DISTRIBUTION",
                                           "AUTOTUNING_IRREGULAR_DISTRIBUTION",
                                           "AUTOTUNING_ERROR" };
std::vector<bool> g_input_implemented = { false, true, false, true, true, false, true, true, true };
std::ostream& operator<< (std::ostream& stream, const e_input_type& p_input_type) {
    int index = static_cast<int> (p_input_type);
    if ((index < (signed) g_input_names.size ()) && (index > 0))
        return stream << g_input_names[index];
    else
        throw InputTypeInvalidException (p_input_type);
}
std::istream& operator>> (std::istream& stream, e_input_type& p_input_type) {
    std::string name;
    stream >> name;
    unsigned int index;
    for (index = 0; index < g_input_names.size (); index++)
        if (0 == strcmp (g_input_names[index], name.c_str ())) {
            p_input_type = static_cast<e_input_type> (index);
        }
    return stream;
}
