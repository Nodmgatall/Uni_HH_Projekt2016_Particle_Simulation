/*
 * EnumInputType.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUM_INPUT_TYPE_HPP_
#define SRC_MAIN_OPTIONS_ENUM_INPUT_TYPE_HPP_

#include <cstring>
#include <exception>
#include <ostream>
#include <vector>

enum class e_input_type {
    GENERATOR_RANDOM               = 1,
    GENERATOR_RANDOM_UNIFORM       = 2,
    GENERATOR_SINGLE_OBJECT_MIDDLE = 3,
    GENERATOR_GRID_DISTRIBUTION    = 4,
    GENERATOR_MULTIPLE_OBJECTS     = 5,
    FILE_CSV                       = 6,
};

std::ostream& operator<< (std::ostream& stream, const e_input_type& p_input_type);
std::istream& operator>> (std::istream& stream, e_input_type& p_input_type);

extern std::vector<const char*> g_input_names;

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
        sprintf (text, "input type ( %s ) is invalid", g_input_names[static_cast<int> (m_input_type)]);
        return text;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMInputType_HPP_ */
