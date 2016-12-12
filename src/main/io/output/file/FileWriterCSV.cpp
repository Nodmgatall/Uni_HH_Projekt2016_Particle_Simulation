/*
 * ParticleFileWriter.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "FileWriterCSV.hpp"

FileWriterCSV::FileWriterCSV (std::map<e_csv_column_type, bool>& p_write_modes, const std::string& p_file_name_base)
: WriterBase (), m_timestep (0), m_file_name_base (p_file_name_base), m_write_modes (p_write_modes) {
    m_stucture_name = "FileWriterCSV";
}
void FileWriterCSV::start () {
    m_file = std::ofstream (m_file_name_base + std::to_string (m_timestep) + ".csv");
    m_file << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::ID)][0];
    if (m_write_modes[e_csv_column_type::POSITION]) {
        for (int i = 0; i < 3; i++) {
            m_file << ", " << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][i];
        }
    }
    // absichtlich NICHT std::endl !!!!!
    m_file << "\n";
}
void FileWriterCSV::saveData (std::vector<data_type>&     p_positions_x,
                              std::vector<data_type>&     p_positions_y,
                              std::vector<data_type>&     p_positions_z,
                              std::vector<unsigned long>& p_ids) {
    unsigned long count = p_ids.size ();
    for (unsigned long i = 0; i < count; i++) {
        m_file << p_ids[i];
        if (m_write_modes[e_csv_column_type::POSITION]) {
            m_file << ", " << p_positions_x[i] << ", " << p_positions_y[i] << ", " << p_positions_z[i];
        }
        m_file << "\n";
    }
}
void FileWriterCSV::end () {
    m_file.close ();
    m_timestep++;
}
