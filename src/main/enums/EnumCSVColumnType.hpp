/*
 * EnumCSVColumnType.h
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_ENUMS_ENUMCSVCOLUMNTYPE_HPP_
#define SRC_MAIN_ENUMS_ENUMCSVCOLUMNTYPE_HPP_

#include <cstring>
#include <exception>
#include <istream>
#include <ostream>
#include <vector>

enum class e_csv_column_type {
    ID            = 1,
    VELOCITY      = 2,
    POSITION      = 3,
    ACCELERATION  = 4,
    PARTICLE_TYPE = 5
};

std::ostream& operator<< (std::ostream& stream, const e_csv_column_type p_csv_column_type);
std::istream& operator>> (std::istream& stream, e_csv_column_type& p_csv_column_type);

extern std::vector<const char*> g_csv_column_names;

extern const char* g_printed_csv_column_names[][3];

std::pair<e_csv_column_type, int>* get_enum_for_printed_csv_column_name (const char* string);

class CSVColumnTypeInvalidException : public std::exception {
  private:
    char* m_what;

  public:
    CSVColumnTypeInvalidException () {
        m_what = (char*) malloc (100);
        sprintf (m_what, "csv_column type ( %s ) is invalid", g_csv_column_names[0]);
    }
    CSVColumnTypeInvalidException (e_csv_column_type m_type) {
        m_what = (char*) malloc (100);
        sprintf (m_what, "csv_column type ( %s ) is invalid", g_csv_column_names[static_cast<int> (m_type)]);
    }
    ~CSVColumnTypeInvalidException () {
        free (m_what);
    }
    const char* what () const throw () {
        return m_what;
    }
};

#endif /* SRC_MAIN_ENUMS_ENUMCSVCOLUMNTYPE_HPP_ */
