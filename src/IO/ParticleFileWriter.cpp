/*
 * ParticleFileWriter.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleFileWriter.hpp"
ParticleFileWriter::ParticleFileWriter () : m_timestep (0), m_file_name_base ("") {
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
        csv_file << i;
        if (p_write_modes[e_particle_variable::POSITION]) {
            csv_file << ", " << *p_particles->get_positions_x ()[i] << ", "
                     << *p_particles->get_positions_y ()[i] << ", "
                     << *p_particles->get_positions_z ()[i];
        }
        if (p_write_modes[e_particle_variable::VELOCITY]) {
            csv_file << ", " << *p_particles->get_velocities_x ()[i] << ", "
                     << *p_particles->get_velocities_y ()[i] << ", "
                     << *p_particles->get_velocities_z ()[i];
        }
        if (p_write_modes[e_particle_variable::ACCELERATION]) {
            csv_file << ", " << *p_particles->get_accelerations_x ()[i] << ", "
                     << *p_particles->get_accelerations_y ()[i] << ", "
                     << *p_particles->get_accelerations_z ()[i];
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
