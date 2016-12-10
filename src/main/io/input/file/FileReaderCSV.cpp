/*
 * FileReaderCSV.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "FileReaderCSV.hpp"

FileReaderCSV::FileReaderCSV (s_options& p_options, DatastructureBase& p_datastructure)
: InputBase (p_options, p_datastructure) {
}

FileReaderCSV::~FileReaderCSV () {
}

void FileReaderCSV::initialize_datastructure () {
    std::ifstream file (m_options.m_in_file_name);
    std::string   line;
    std::string   word;
    int           found;
    std::vector<std::pair<e_csv_column_type, int>> dataTypeFromColumn;
    data_type id;
    Vec3f     position;
    Vec3f     velocity;
    int       column;
    // read caption line
    if (std::getline (file, line)) {
        std::stringstream linestreamcaption (line);
        while (linestreamcaption.good ()) {
            std::getline (linestreamcaption, word, ',');
            std::pair<e_csv_column_type, int>* tmp = get_enum_for_printed_csv_column_name (word.c_str ());
            if (tmp) {
                dataTypeFromColumn.push_back (*tmp);
                delete (tmp);
            }
        }
        // read data
        while (std::getline (file, line)) {
            std::stringstream linestream (line);
            column = 0;
            found  = 0;
            while (linestream.good ()) {
                std::getline (linestream, word, ',');
                std::stringstream wordstream (word);
                switch (dataTypeFromColumn[column].first) {
                    case e_csv_column_type::ID: {
                        wordstream >> id;
                        found++;
                        break;
                    }
                    case e_csv_column_type::POSITION: {
                        switch (dataTypeFromColumn[column].second) {
                            case 0: {
                                wordstream >> position.x;
                                found++;
                                break;
                            }
                            case 1: {
                                wordstream >> position.y;
                                found++;
                                break;
                            }
                            case 2: {
                                wordstream >> position.z;
                                found++;
                                break;
                            }
                            default: { break; }
                        }
                        break;
                    }
                    case e_csv_column_type::VELOCITY: {
                        switch (dataTypeFromColumn[column].second) {
                            case 0: {
                                wordstream >> velocity.x;
                                found++;
                                break;
                            }
                            case 1: {
                                wordstream >> velocity.y;
                                found++;
                                break;
                            }
                            case 2: {
                                wordstream >> velocity.z;
                                found++;
                                break;
                            }
                            default: { break; }
                        }
                        break;
                    }
                    default: { break; }
                }
                m_datastructure.add_particle (position, velocity);
                column++;
            }
        }
    }
}
