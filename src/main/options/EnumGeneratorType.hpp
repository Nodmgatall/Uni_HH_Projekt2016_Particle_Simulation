/*
 * EnumGeneratorType.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUM_GENERATOR_TYPE_HPP_
#define SRC_MAIN_OPTIONS_ENUM_GENERATOR_TYPE_HPP_

#include <ostream>

enum e_generator_type {
    RANDOM               = 1,
    RANDOM_UNIFORM       = 2,
    SINGLE_OBJECT_MIDDLE = 3,
    GRID_DISTRIBUTION    = 4,
    MULTIPLE_OBJECTS     = 5,
};

std::ostream& operator<< (std::ostream& stream, const e_generator_type p_generator_type);

extern const char* g_generator_names[];

class GeneratorTypeInvalidException : public std::exception {
  private:
    e_generator_type m_generator_type;

  public:
    GeneratorTypeInvalidException () : m_generator_type ((e_generator_type) 0) {
    }
    GeneratorTypeInvalidException (e_generator_type p_generator_type)
    : m_generator_type (p_generator_type) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "algorithm type ( %s ) is invalid", g_generator_names[m_generator_type - 1]);
        return text;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMGeneratorType_HPP_ */
