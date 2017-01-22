/*
 * FileReaderCSV.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */
#ifndef SRC_MAIN_IO_INPUT_FILE_FILEREADERCSV_HPP_
#define SRC_MAIN_IO_INPUT_FILE_FILEREADERCSV_HPP_
#include "io/input/InputBase.hpp"
#include <algorithm>
class FileReaderCSV : public InputBase {
  protected:
    /**
     * string left trim removes whitespaces etc from the left string side
     */
    static inline void ltrim (std::string& s);
    /**
     * string left trim removes whitespaces etc from the right string side
     */
    static inline void rtrim (std::string& s);
    /**
     * string left trim removes whitespaces etc from the left and the right string side
     */
    static inline void trim (std::string& s);
  public:
    /**
     * constructor
     */
    FileReaderCSV (s_options& p_options, DatastructureBase& p_datastructure);
    /**
     * destructor
     */
    virtual ~FileReaderCSV ();
    virtual void initialize_datastructure () override;
};
#endif /* SRC_MAIN_IO_INPUT_FILE_FILEREADERCSV_HPP_ */
