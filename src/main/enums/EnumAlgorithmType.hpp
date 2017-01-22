/*
 * EnumAlgorithmType.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_OPTIONS_ENUM_ALGORITHM_TYPE_HPP_
#define SRC_MAIN_OPTIONS_ENUM_ALGORITHM_TYPE_HPP_

#include <cstring>
#include <exception>
#include <istream>
#include <ostream>
#include <vector>
/**
 * implemented or planned algorithm_types
 */
enum class e_algorithm_type {
    LENNARD_JONES                  = 1,
    SMOTHED_PARTICLE_HYDRODYNAMICS = 2,
    DISSIPATIVE_PARTICLE_DYNAMICS  = 3
};

std::ostream& operator<< (std::ostream& stream, const e_algorithm_type& p_algorithm_type);
std::istream& operator>> (std::istream& stream, e_algorithm_type& p_algorithm_type);

extern std::vector<const char*> g_algorithm_names;
extern std::vector<bool>        g_algorithm_implemented;

class AlgorithmTypeInvalidException : public std::exception {
  private:
    char* m_what;

  public:
    AlgorithmTypeInvalidException () {
        m_what = (char*) malloc (100);
        sprintf (m_what, "algorithm type ( %s ) is invalid", g_algorithm_names[0]);
    }
    AlgorithmTypeInvalidException (e_algorithm_type m_type) {
        m_what = (char*) malloc (100);
        sprintf (m_what, "algorithm type ( %s ) is invalid", g_algorithm_names[static_cast<int> (m_type)]);
    }
    ~AlgorithmTypeInvalidException () {
        free (m_what);
    }
    const char* what () const throw () {
        return m_what;
    }
};

#endif /* SRC_MAIN_OPTIONS_ENUMALGORITHMTYPE_HPP_ */
