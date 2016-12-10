/*
 * EnumInputType.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUM_INPUT_TYPE_HPP_
#define SRC_MAIN_OPTIONS_ENUM_INPUT_TYPE_HPP_

#include <ostream>

enum class e_input_type {
    RANDOM               = 1,
    RANDOM_UNIFORM       = 2,
    SINGLE_OBJECT_MIDDLE = 3,
    GRID_DISTRIBUTION    = 4,
    MULTIPLE_OBJECTS     = 5,
    CSV                  = 6,
};

std::ostream& operator<< (std::ostream& stream, const e_input_type p_input_type);

extern const char* g_input_names[];

class InputTypeInvalidException : public std::exception {
  private:
    e_input_type m_input_type;

  public:
    InputTypeInvalidException () : m_input_type ((e_input_type) 0) {
    }
    InputTypeInvalidException (e_input_type p_input_type) : m_input_type (p_input_type) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "algorithm type ( %s ) is invalid", g_input_names[static_cast<int> (m_input_type) - 1]);
        return text;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMInputType_HPP_ */
