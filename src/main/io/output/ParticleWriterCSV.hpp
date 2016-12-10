/*
 * ParticleFileWriter.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEFILEWRITER_HPP_
#define SRC_PARTICLEFILEWRITER_HPP_

#include "ParticleWriterBase.hpp"

class ParticleWriterCSV : public ParticleWriterBase {
  protected:
    int           m_timestep;
    std::string   m_file_name_base;
    std::ofstream m_file;
    std::map<e_particle_variable, bool>& m_write_modes;

  public:
    void saveData (std::vector<data_type>&     p_positions_x,
                   std::vector<data_type>&     p_positions_y,
                   std::vector<data_type>&     p_positions_z,
                   std::vector<unsigned long>& p_ids);
    ParticleWriterCSV (std::map<e_particle_variable, bool>& p_write_modes, const std::string& p_file_name_base);
    void start ();
    void end ();
};

#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
