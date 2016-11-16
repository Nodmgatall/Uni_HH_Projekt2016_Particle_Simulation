/*
 * ParticleFileWriter.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleFileWriter.hpp"
ParticleFileWriter::ParticleFileWriter (std::map<e_particle_variable, bool> *p_write_modes)
: m_timestep (0), m_file_name_base (""), m_write_modes (p_write_modes) {
}
void ParticleFileWriter::start()
{
    m_file = std::ofstream (m_file_name_base + std::to_string (m_timestep) + ".csv");

}
void ParticleFileWriter::saveData (std::vector<float> *p_positions_x,
                                   std::vector<float> *p_positions_y,
                                   std::vector<float> *p_positions_z,
                                   std::vector<float> *p_velocities_x,
                                   std::vector<float> *p_velocities_y,
                                   std::vector<float> *p_velocities_z,
                                   std::vector<float> *p_accelerations_x,
                                   std::vector<float> *p_accelerations_y,
                                   std::vector<float> *p_accelerations_z,
                                   std::vector<unsigned long> *ids) {
    (void)(ids);
    
        m_file << "id";
    if ((*m_write_modes)[e_particle_variable::POSITION])
        m_file << ", x coordinate, y coordinate, z coordinate";
    if ((*m_write_modes)[e_particle_variable::VELOCITY])
        m_file << ", x velocity, y velocity, z velocity";
    if ((*m_write_modes)[e_particle_variable::ACCELERATION])
        m_file << ", x acceleration, y acceleration, z acceleration";
    if ((*m_write_modes)[e_particle_variable::PARTICLE_TYPE])
        m_file << ", particleType";
    m_file << "\n"; // absichtlich NICHT std::endl !!!!!
    unsigned long count = (*p_positions_x).size ();
    for (unsigned long i = 0; i < count; i++) {
        m_file << i;
        if ((*m_write_modes)[e_particle_variable::POSITION]) {
            m_file << ", " << (*p_positions_x)[i] << ", " << (*p_positions_y)[i] << ", "
                     << (*p_positions_z)[i];
        }
        if ((*m_write_modes)[e_particle_variable::VELOCITY]) {
            m_file << ", " << (*p_velocities_x)[i] << ", " << (*p_velocities_y)[i] << ", "
                     << (*p_velocities_z)[i];
        }
        if ((*m_write_modes)[e_particle_variable::ACCELERATION]) {
            m_file << ", " << (*p_accelerations_x)[i] << ", " << (*p_accelerations_y)[i] << ", "
                     << (*p_accelerations_z)[i];
        }
        if ((*m_write_modes)[e_particle_variable::PARTICLE_TYPE]) {
            DEBUG_BEGIN << "error not implemented" << DEBUG_END;
            // TODO
            exit (1);
        }
        m_file << "\n";
    }
    m_timestep++;
}

void ParticleFileWriter::end()
{
    m_file.close();
}

void ParticleFileWriter::set_file_name_base (const std::string &file_name_base) {
    m_file_name_base = file_name_base;
}
