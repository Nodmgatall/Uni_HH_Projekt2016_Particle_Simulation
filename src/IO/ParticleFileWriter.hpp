/*
 * ParticleFileWriter.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEFILEWRITER_HPP_
#define SRC_PARTICLEFILEWRITER_HPP_
#include "../Definitions.hpp"
class ParticleFileWriter {
    private:
    int         m_timestep;
    std::string m_file_name_base;
    std::map<e_particle_variable, bool> *m_write_modes;

    public:
    void saveData (std::vector<float> *        p_positions_x,
                   std::vector<float> *        p_positions_y,
                   std::vector<float> *        p_positions_z,
                   std::vector<float> *        p_velocities_x,
                   std::vector<float> *        p_velocities_y,
                   std::vector<float> *        p_velocities_z,
                   std::vector<float> *        p_accelerations_x,
                   std::vector<float> *        p_accelerations_y,
                   std::vector<float> *        p_accelerations_z,
                   std::vector<unsigned long> *ids);

    ParticleFileWriter (std::map<e_particle_variable, bool> *p_write_modes);
    void set_file_name_base (const std::string &file_name_base);
};

#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
