/*
 * EnumCSVColumnType.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "EnumCSVColumnType.hpp"

const char* g_csv_column_names[] = { "ID",
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

std::ostream& operator<< (std::ostream& stream, const e_csv_column_type p_csv_column_type) {
    switch (p_csv_column_type) {
        case e_csv_column_type::ID:
        case e_csv_column_type::VELOCITY:
        case e_csv_column_type::POSITION:
        case e_csv_column_type::ACCELERATION:
        case e_csv_column_type::PARTICLE_TYPE:
            return stream << g_csv_column_names[static_cast<int> (p_csv_column_type) - 1];
        default:
            throw CSVColumnTypeInvalidException (p_csv_column_type);
    }
}
