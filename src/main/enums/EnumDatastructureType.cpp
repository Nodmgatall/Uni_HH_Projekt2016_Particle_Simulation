/*
 * EnumDatastructureType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "../enums/EnumDatastructureType.hpp"

const char* g_datastructure_names[] = { "UNDEFINED", "GRID", "LIST", "LISTEDGIRD" };

std::ostream& operator<< (std::ostream& stream, const e_datastructure_type p_datastructure_type) {
    switch (p_datastructure_type) {
        case e_datastructure_type::GRID:
        case e_datastructure_type::LIST:
        case e_datastructure_type::LISTEDGIRD:
            return stream << g_datastructure_names[static_cast<int> (p_datastructure_type)];
        default:
            throw DatastructureTypeInvalidException (p_datastructure_type);
    }
}
