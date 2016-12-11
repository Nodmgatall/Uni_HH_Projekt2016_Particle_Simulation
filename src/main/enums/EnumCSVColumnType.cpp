/*
 * EnumCSVColumnType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumCSVColumnType.hpp"

std::vector<const char*> g_csv_column_names = { "UNDEFINED",
                                                "ID",
                                                "VELOCITY",
                                                "POSITION",
                                                "ACCELERATION",
                                                "PARTICLE_"
                                                "TYPE" };

const char* g_printed_csv_column_names[]
                                      [3] = { { 0, 0, 0 },
                                              { "ID", 0, 0 },
                                              { "VelocityX", "VelocityY", "VelocityZ" },
                                              { "PositionX", "PositionY", "PositionZ" },
                                              { "AccelerationX", "AccelerationY", "AccelerationZ" },
                                              { "ParticleType", 0, 0 } };

std::pair<e_csv_column_type, int>* get_enum_for_printed_csv_column_name (const char* string) {
    for (int i = 1; i < (signed) g_csv_column_names.size (); i++) {
        for (int j = 0; j < 3; j++) {
            if (g_printed_csv_column_names[i][j]) {
                if (0 == strcmp (string, g_printed_csv_column_names[i][j])) {
                    return new std::pair<e_csv_column_type, int> (static_cast<e_csv_column_type> (i), j);
                }
            }
        }
    }
    return 0;
}

std::ostream& operator<< (std::ostream& stream, const e_csv_column_type p_csv_column_type) {
    int index = static_cast<int> (p_csv_column_type);
    if ((index < (signed) g_csv_column_names.size ()) && (index > 0))
        return stream << g_csv_column_names[index];
    else
        throw CSVColumnTypeInvalidException (p_csv_column_type);
}
