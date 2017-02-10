/*
 * FileReaderCSV.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "FileReaderCSV.hpp"
FileReaderCSV::FileReaderCSV (s_options& p_options, DatastructureBase& p_datastructure) : InputBase (p_options, p_datastructure) {
    m_stucture_name = "FileReaderCSV";
}
FileReaderCSV::~FileReaderCSV () {
}
void FileReaderCSV::ltrim (std::string& s) {
    s.erase (s.begin (), std::find_if (s.begin (), s.end (), std::not1 (std::ptr_fun<int, int> (std::isspace))));
}
void FileReaderCSV::rtrim (std::string& s) {
    s.erase (std::find_if (s.rbegin (), s.rend (), std::not1 (std::ptr_fun<int, int> (std::isspace))).base (), s.end ());
}
void FileReaderCSV::trim (std::string& s) {
    ltrim (s);
    rtrim (s);
}
void FileReaderCSV::initialize_datastructure () {
    std::ifstream file = std::ifstream (m_options.m_in_file_name);
    std::string   line;
    std::string   word;
    int           found;
    std::vector<std::pair<e_csv_column_type, int>> dataTypeFromColumn;
    long  id;
    Vec3f position;
    Vec3f velocity;
    int   column;
    // read caption line
    if (std::getline (file, line)) {
        std::stringstream linestreamcaption (line);
        while (linestreamcaption.good ()) {
            std::getline (linestreamcaption, word, ',');
            trim (word);
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
                trim (word);
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
                        }
                        break;
                    }
                    default: {}
                }
                column++;
            }
            if (found > 0) {
                m_datastructure.add_particle (position, velocity, id);
            }
        }
    }
    file.close ();
}
