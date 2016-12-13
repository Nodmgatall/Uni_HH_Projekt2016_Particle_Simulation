/*
 * ParticleFileWriter.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEFILEWRITER_HPP_
#define SRC_PARTICLEFILEWRITER_HPP_

#include "io/output/WriterBase.hpp"

class FileWriterCSV : public WriterBase {
  protected:
    int           m_timestep;
    std::string   m_file_name_base;
    std::ofstream m_file;
    s_options &m_options;

  public:
    void saveData (std::vector<data_type>&     p_positions_x,
                   std::vector<data_type>&     p_positions_y,
                   std::vector<data_type>&     p_positions_z,
                   std::vector<unsigned long>& p_ids);
    FileWriterCSV (s_options &p_options, const std::string& p_file_name_base);
    void start ();
    void end ();
};

#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
