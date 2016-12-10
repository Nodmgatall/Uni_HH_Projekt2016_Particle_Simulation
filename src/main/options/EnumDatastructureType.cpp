/*
 * EnumDatastructureType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumDatastructureType.hpp"

const char* g_datastructure_names[] = { "GRID", "LIST", "LISTEDGIRD" };

std::ostream& operator<< (std::ostream& stream, const e_datastructure_type p_datastructure_type) {
    switch (p_datastructure_type) {
        case e_datastructure_type::GRID:
        case e_datastructure_type::LIST:
        case e_datastructure_type::LISTEDGIRD:
            return stream << g_datastructure_names[p_datastructure_type - 1];
        default:
            throw DatastructureTypeInvalidException (p_datastructure_type);
    }
}
