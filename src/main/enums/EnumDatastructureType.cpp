/*
 * EnumDatastructureType.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "enums/EnumDatastructureType.hpp"
std::vector<const char*> g_datastructure_names       = { "UNDEFINED", "LINKED_CELLS", "NEIGHBOR_LIST", "LINKED_CELLS+NEIGHBOR_LIST" };
std::vector<bool>        g_datastructure_implemented = { false, true, true, true, true };
std::ostream& operator<< (std::ostream& stream, const e_datastructure_type& p_datastructure_type) {
    int index = static_cast<int> (p_datastructure_type);
    if ((index < (signed) g_datastructure_names.size ()) && (index > 0))
        return stream << g_datastructure_names[index];
    else
        throw DatastructureTypeInvalidException (p_datastructure_type);
}
std::istream& operator>> (std::istream& stream, e_datastructure_type& p_datastructure_type) {
    std::string name;
    stream >> name;
    unsigned int index;
    for (index = 0; index < g_datastructure_names.size (); index++)
        if (0 == strcmp (g_datastructure_names[index], name.c_str ())) {
            p_datastructure_type = static_cast<e_datastructure_type> (index);
        }
    return stream;
}
