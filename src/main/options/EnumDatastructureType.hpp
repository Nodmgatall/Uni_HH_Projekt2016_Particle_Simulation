/*
 * EnumDatastructureType.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUM_DATASTRUCTURE_TYPE_HPP_
#define SRC_MAIN_OPTIONS_ENUM_DATASTRUCTURE_TYPE_HPP_

#include <ostream>

enum e_datastructure_type { GRID = 1, LIST = 2, LISTEDGIRD = 3 };

std::ostream& operator<< (std::ostream& stream, const e_datastructure_type p_datastructure_type);

extern const char* g_datastructure_names[];

class DatastructureTypeInvalidException : public std::exception {
  private:
    e_datastructure_type m_datastructure_type;

  public:
    DatastructureTypeInvalidException () : m_datastructure_type ((e_datastructure_type) 0) {
    }
    DatastructureTypeInvalidException (e_datastructure_type p_datastructure_type)
    : m_datastructure_type (p_datastructure_type) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "datastructure type ( %s ) is invalid", g_datastructure_names[m_datastructure_type]);
        return text;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMDATASTRUCTURETYPE_HPP_ */
