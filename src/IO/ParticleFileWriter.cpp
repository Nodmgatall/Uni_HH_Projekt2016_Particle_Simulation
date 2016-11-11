/*
 * ParticleFileWriter.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleFileWriter.hpp"
ParticleFileWriter::ParticleFileWriter () : m_timestep (0), m_file_name_base ("") {
}
void writeVectorToStream (std::ofstream &p_stream, glm::vec3 p_data) {
    p_stream << p_data.x << ", " << p_data.y << ", " << p_data.z;
}
void ParticleFileWriter::saveData (std::shared_ptr<ParticlesBase> p_particles,
                                   std::map<e_particle_variable, bool> p_write_modes) {
    Benchmark::begin ("saving the data", false);
    std::ofstream csv_file =
        std::ofstream (m_file_name_base + std::to_string (m_timestep) + ".csv");
    csv_file << "id";
    if (p_write_modes[e_particle_variable::POSITION])
        csv_file << ", x coordinate, y coordinate, z coordinate";
    if (p_write_modes[e_particle_variable::VELOCITY])
        csv_file << ", x velocity, y velocity, z velocity";
    if (p_write_modes[e_particle_variable::ACCELERATION])
        csv_file << ", x acceleration, y acceleration, z acceleration";
    if (p_write_modes[e_particle_variable::PARTICLE_TYPE])
        csv_file << ", particleType";
    csv_file << "\n"; // absichtlich NICHT std::endl !!!!!
    unsigned long count = p_particles->get_particle_count ();
    for (unsigned long i = 0; i < count; i++) {
        csv_file << p_particles->m_ids[i];
        if (p_write_modes[e_particle_variable::POSITION]) {
            csv_file << ", ";
            writeVectorToStream (csv_file, p_particles->m_positions[i]);
        }
        if (p_write_modes[e_particle_variable::VELOCITY]) {
            csv_file << ", ";
            writeVectorToStream (csv_file, p_particles->m_velocities[i]);
        }
        if (p_write_modes[e_particle_variable::ACCELERATION]) {
            csv_file << ", ";
            writeVectorToStream (csv_file, p_particles->m_accelerations[i]);
        }
        if (p_write_modes[e_particle_variable::PARTICLE_TYPE]) {
            DEBUG_BEGIN << "error not implemented" << DEBUG_END;
            // TODO
            exit (1);
        }
        csv_file << "\n";
    }
    m_timestep++;
    Benchmark::end ();
}

void ParticleFileWriter::set_file_name_base (const std::string &file_name_base) {
    m_file_name_base = file_name_base;
}
