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
    e_csv_column_type m_csv_column_type;

  public:
    CSVColumnTypeInvalidException () : m_csv_column_type ((e_csv_column_type) 0) {
    }
    CSVColumnTypeInvalidException (e_csv_column_type p_csv_column_type)
    : m_csv_column_type (p_csv_column_type) {
    }
    const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "csv_column type ( %s ) is invalid", g_csv_column_names[static_cast<int> (m_csv_column_type)]);
        return text;
    }
};

#endif /* SRC_MAIN_ENUMS_ENUMCSVCOLUMNTYPE_HPP_ */
