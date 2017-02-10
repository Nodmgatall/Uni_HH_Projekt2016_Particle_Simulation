/*
 * FileReaderCSV.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_IO_INPUT_FILE_FILEINPUTCSV_HPP_
#define SRC_MAIN_IO_INPUT_FILE_FILEINPUTCSV_HPP_
#include "io/input/InputBase.hpp"
#include <algorithm>
class FileInputCSV : public InputBase {
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
    FileInputCSV (s_options& p_options, DatastructureBase& p_datastructure);
    /**
     * destructor
     */
    virtual ~FileInputCSV ();
    virtual void initialize_datastructure () override;
};
#endif /* SRC_MAIN_IO_INPUT_FILE_FILEINPUTCSV_HPP_ */
