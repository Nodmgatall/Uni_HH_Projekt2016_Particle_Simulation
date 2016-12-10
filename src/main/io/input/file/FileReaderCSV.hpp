/*
 * FileReaderCSV.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_IO_INPUT_FILE_FILEREADERCSV_HPP_
#define SRC_MAIN_IO_INPUT_FILE_FILEREADERCSV_HPP_

#include "../InputBase.hpp"

class FileReaderCSV : public InputBase {
  public:
    FileReaderCSV (s_options& p_options, DatastructureBase& p_datastructure);
    virtual ~FileReaderCSV ();
    virtual void initialize_datastructure ();
};

#endif /* SRC_MAIN_IO_INPUT_FILE_FILEREADERCSV_HPP_ */
