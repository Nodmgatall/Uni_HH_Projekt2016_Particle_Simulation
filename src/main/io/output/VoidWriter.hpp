/*
 * VoidWriter.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_PARTICLEFILE_WRITER_HPP_
#define SRC_PARTICLEFILE_WRITER_HPP_
#include <io/output/OutputBase.hpp>
/**
 * This class does not write any Output
 */
class VoidWriter : public OutputBase {
  public:
    void saveData (std::vector<data_type>& p_positions_x, std::vector<data_type>& p_positions_y, std::vector<data_type>& p_positions_z, std::vector<unsigned long>& p_ids) override {
        (void) p_positions_x;
        (void) p_positions_y;
        (void) p_positions_z;
        (void) p_ids;
    }
    /**
     * constructor
     */
    VoidWriter () {
    }
    void start () override {
    }
    void end () override {
    }
    void finalize () override {
    }
};
#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
