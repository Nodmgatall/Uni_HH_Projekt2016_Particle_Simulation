/*
 * EnumDatastructureType.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_ENUMS_ENUMDATASTRUCTURETYPE_HPP_
#define SRC_MAIN_ENUMS_ENUMDATASTRUCTURETYPE_HPP_
#include <cstring>
#include <exception>
#include <istream>
#include <ostream>
#include <vector>
/**
 * implemented or plannes datastructures for optimizeing the particle-calculation
 */
enum class e_datastructure_type { LINKED_CELLS = 1, NEIGHBOR_LIST = 2, LINKED_CELLS_NEIGHBOR_LIST = 3 };
std::ostream& operator<< (std::ostream& stream, const e_datastructure_type& p_datastructure_type);
std::istream& operator>> (std::istream& stream, e_datastructure_type& p_datastructure_type);
extern std::vector<const char*> g_datastructure_names;
extern std::vector<bool>        g_datastructure_implemented;
class DatastructureTypeInvalidException : public std::exception {
  private:
    char* m_what;

  public:
    DatastructureTypeInvalidException () {
        m_what = (char*) malloc (100);
        sprintf (m_what, "datastructure type ( %s ) is invalid", g_datastructure_names[0]);
    }
    DatastructureTypeInvalidException (e_datastructure_type m_type) {
        m_what = (char*) malloc (100);
        sprintf (m_what, "datastructure type ( %s ) is invalid", g_datastructure_names[static_cast<int> (m_type)]);
    }
    ~DatastructureTypeInvalidException () {
        free (m_what);
    }
    const char* what () const throw () {
        return m_what;
    }
};
#endif /* SRC_MAIN_OPTIONS_ENUMDATASTRUCTURETYPE_HPP_ */
