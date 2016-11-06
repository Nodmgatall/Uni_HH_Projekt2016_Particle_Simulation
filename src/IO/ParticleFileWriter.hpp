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

    public:
    void saveData (std::shared_ptr<ParticlesBase> p_particles, std::map<e_particle_variable, bool> p_write_modes);
    ParticleFileWriter ();
    void set_file_name_base (const std::string &file_name_base);
};

#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
