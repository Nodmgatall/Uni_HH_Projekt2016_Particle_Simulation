/*
 * FileWriterCSV.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_IO_OUTPUT_FILE_FILEOUTPUTCSV_HPP_
#define SRC_MAIN_IO_OUTPUT_FILE_FILEOUTPUTCSV_HPP_
#include <io/output/OutputBase.hpp>
class FileOutputCSV : public OutputBase {
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
    FileOutputCSV (s_options& p_options);
    void start () override;
    void end () override;
    void finalize () override;
};
#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
