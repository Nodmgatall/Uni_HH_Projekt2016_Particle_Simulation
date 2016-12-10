/*
 * ParticleFileWriter.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleFileWriter.hpp"
ParticleFileWriter::ParticleFileWriter (std::map<e_particle_variable, bool>& p_write_modes,
                                        const std::string& p_file_name_base)
: m_timestep (0), m_file_name_base (p_file_name_base), m_write_modes (p_write_modes) {
}
void ParticleFileWriter::start () {
    m_file = std::ofstream (m_file_name_base + std::to_string (m_timestep) + ".csv");
    m_file << "id, x coordinate, y coordinate, z coordinate\n"; // absichtlich
                                                                // NICHT std::endl
                                                                // !!!!!
}
void ParticleFileWriter::saveData (std::vector<data_type>*     p_positions_x,
                                   std::vector<data_type>*     p_positions_y,
                                   std::vector<data_type>*     p_positions_z,
                                   std::vector<unsigned long>* ids) {
    unsigned long count = ids[0].size ();
    for (unsigned long i = 0; i < count; i++) {
        m_file << ids[0][i];
        m_file << ", " << p_positions_x[0][i] << ", " << p_positions_y[0][i] << ", " << p_positions_z[0][i];
        m_file << "\n";
    }
}

void ParticleFileWriter::end () {
    m_file.close ();
    m_timestep++;
}
