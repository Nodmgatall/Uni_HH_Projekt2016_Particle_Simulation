/*
 * EnumGeneratorMode.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUMGENERATORMODE_HPP_
#define SRC_MAIN_OPTIONS_ENUMGENERATORMODE_HPP_

#include <ostream>

enum e_generator_mode {
    RANDOM               = 1,
    RANDOM_UNIFORM       = 2,
    SINGLE_OBJECT_MIDDLE = 3,
    GRID_DISTRIBUTION    = 4,
    MULTIPLE_OBJECTS     = 5,
};

std::ostream& operator<< (std::ostream& stream, const e_generator_mode p_generator_mode);

extern const char* g_generator_names[];

class GeneratorModeInvalidException : public std::exception {
  private:
    e_generator_mode m_generator_mode;

  public:
    GeneratorModeInvalidException () : m_generator_mode ((e_generator_mode) 0) {
    }
    GeneratorModeInvalidException (e_generator_mode p_generator_mode)
    : m_generator_mode (p_generator_mode) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "algorithm type ( %s ) is invalid", g_generator_names[m_generator_mode]);
        return text;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMGENERATORMODE_HPP_ */
