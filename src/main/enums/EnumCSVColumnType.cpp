/*
 * EnumCSVColumnType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumCSVColumnType.hpp"

const char* g_csv_column_names[] = { "UNDEFINED",
                                     "ID",
                                     "VELOCITY",
                                     "POSITION",
                                     "ACCELERATION",
                                     "PARTICLE_"
                                     "TYPE" };

const char* g_printed_csv_column_names[]
                                      [3] = { { "ID", "", "" },
                                              { "VelocityX", "VelocityY", "VelocityZ" },
                                              { "PositionX", "PositionY", "PositionZ" },
                                              { "AccelerationX", "AccelerationY", "AccelerationZ" },
                                              { "ParticleType", "", "" } };

std::pair<e_csv_column_type, int>* get_enum_for_printed_csv_column_name (const char* string) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (strcmp (string, g_printed_csv_column_names[i][j])) {
                return new std::pair<e_csv_column_type, int> (static_cast<e_csv_column_type> (i + 1), j);
            }
        }
    }
    return 0;
}

std::ostream& operator<< (std::ostream& stream, const e_csv_column_type p_csv_column_type) {
    switch (p_csv_column_type) {
        case e_csv_column_type::ID:
        case e_csv_column_type::VELOCITY:
        case e_csv_column_type::POSITION:
        case e_csv_column_type::ACCELERATION:
        case e_csv_column_type::PARTICLE_TYPE:
            return stream << g_csv_column_names[static_cast<int> (p_csv_column_type)];
        default:
            throw CSVColumnTypeInvalidException (p_csv_column_type);
    }
}
