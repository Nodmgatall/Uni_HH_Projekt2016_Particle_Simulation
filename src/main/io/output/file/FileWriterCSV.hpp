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
    /**
     * the current timestep which is used as fileending. this could be much less, than the timestep
     * used by the particlesimulator-class for simulating the interactions
     */
    int m_timestep;
    /**
     * thie file-name-prefix used for the output csv files
     */
    std::string m_file_name_base;
    /**
     * the currently opened outputstream.
     */
    std::ofstream m_file;
    /**
        * The option struct generated from the parameters given aut program-launch
        */
    s_options& m_options;
  public:
    void saveData (std::vector<data_type>& p_positions_x, std::vector<data_type>& p_positions_y, std::vector<data_type>& p_positions_z, std::vector<unsigned long>& p_ids) override;
    /**
     * constructor
     */
    FileWriterCSV (s_options& p_options, const std::string& p_file_name_base);
    void start () override;
    void end () override;
    void finalize () override;
};
#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
