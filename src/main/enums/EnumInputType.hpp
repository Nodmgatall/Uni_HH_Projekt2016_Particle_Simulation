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
#include <istream>
#include <ostream>
#include <vector>
/**
 * implemented or planned input types for the simulation
 */
enum class e_input_type {
    GENERATOR_RANDOM                  = 1,
    GENERATOR_RANDOM_UNIFORM          = 2,
    GENERATOR_SINGLE_OBJECT_MIDDLE    = 3,
    GENERATOR_GRID_DISTRIBUTION       = 4,
    GENERATOR_MULTIPLE_OBJECTS        = 5,
    FILE_CSV                          = 6,
    AUTOTUNING_REGULAR_DISTRIBUTION   = 7,
    AUTOTUNING_IRREGULAR_DISTRIBUTION = 8,
    AUTOTUNING_ERROR                  = 9,
};
const int     g_input_type_autotuning_enums_count = 3;
std::ostream& operator<< (std::ostream& stream, const e_input_type& p_input_type);
std::istream& operator>> (std::istream& stream, e_input_type& p_input_type);
extern std::vector<const char*> g_input_names;
extern std::vector<bool>        g_input_implemented;
class InputTypeInvalidException : public std::exception {
  private:
    char* m_what;

  public:
    InputTypeInvalidException () {
        m_what = (char*) malloc (100);
        sprintf (m_what, "input type ( %s ) is invalid", g_input_names[0]);
    }
    InputTypeInvalidException (e_input_type m_type) {
        m_what = (char*) malloc (100);
        sprintf (m_what, "input type ( %s ) is invalid", g_input_names[static_cast<int> (m_type)]);
    }
    ~InputTypeInvalidException () {
        free (m_what);
    }
    const char* what () const throw () {
        return m_what;
    }
};
#endif /* SRC_MAIN_OPTIONS_ENUMInputType_HPP_ */
