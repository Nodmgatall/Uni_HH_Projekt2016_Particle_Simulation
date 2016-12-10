/*
 * EnumAlgorithmType.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUMALGORITHMTYPE_HPP_
#define SRC_MAIN_OPTIONS_ENUMALGORITHMTYPE_HPP_

#include <ostream>

enum e_algorithm_type {
    UNDEFINED                      = 0,
    LENNARD_JONES                  = 1,
    SMOTHED_PARTICLE_HYDRODYNAMICS = 2,
    DISSIPATIVE_PARTICLE_DYNAMICS  = 3
};
extern const char* g_algorithm_names[];
class AlgorithmTypeInvalidException : public std::exception {
  private:
    e_algorithm_type m_algorithm_type;

  public:
    AlgorithmTypeInvalidException () : m_algorithm_type (e_algorithm_type::UNDEFINED) {
    }
    AlgorithmTypeInvalidException (e_algorithm_type p_algorithm_type)
    : m_algorithm_type (p_algorithm_type) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "algorithm type ( %s ) is invalid", g_algorithm_names[m_algorithm_type]);
        return text;
    }
};
std::ostream& operator<< (std::ostream& stream, const e_algorithm_type p_algorithm_type);

#endif /* SRC_MAIN_OPTIONS_ENUMALGORITHMTYPE_HPP_ */
