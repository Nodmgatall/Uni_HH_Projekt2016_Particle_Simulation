/*
 * ParticleFileWriter.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEFILEWRITER_HPP_
#define SRC_PARTICLEFILEWRITER_HPP_

#include "../WriterBase.hpp"

class FileWriterCSV : public WriterBase {
  protected:
    int           m_timestep;
    std::string   m_file_name_base;
    std::ofstream m_file;
    std::map<e_csv_column_type, bool>& m_write_modes;

  public:
    void saveData (std::vector<data_type>&     p_positions_x,
                   std::vector<data_type>&     p_positions_y,
                   std::vector<data_type>&     p_positions_z,
                   std::vector<unsigned long>& p_ids);
    FileWriterCSV (std::map<e_csv_column_type, bool>& p_write_modes, const std::string& p_file_name_base);
    void start ();
    void end ();
};

#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
