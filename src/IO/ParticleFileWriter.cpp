/*
 * ParticleFileWriter.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleFileWriter.hpp"
int ParticleFileWriter::m_timestep = 0;
std::string ParticleFileWriter::m_file_name_base;

void writeVectorToStream(std::ofstream &p_stream, glm::vec3 p_data) {
	p_stream << p_data.x << ", " << p_data.y << ", " << p_data.z;
}

void ParticleFileWriter::saveData(std::shared_ptr<ParticlesBase> p_particles) {
	std::ofstream csv_file = std::ofstream(
			m_file_name_base + std::to_string(m_timestep) + ".csv");
	csv_file<<"id";
	csv_file << ",x coordinate,y coordinate,z coordinate";
	csv_file << ",x velocity,y velocity,z velocity";
	csv_file << ",x acceleration,y acceleration,z acceleration";
	for (unsigned long i = 0; i < p_particles->get_particle_count(); i++) {
		csv_file<<p_particles->m_ids[i];
		writeVectorToStream(csv_file, p_particles->m_positions[i]);
		csv_file << ", ";
		writeVectorToStream(csv_file, p_particles->m_velocities[i]);
		csv_file << ", ";
		writeVectorToStream(csv_file, p_particles->m_accelerations[i]);
		csv_file << "\n";
	}
}
