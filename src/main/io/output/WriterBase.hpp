/*
 * ParticleWriterBase.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_
#define SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_

#include "Definitions.hpp"

class WriterBase {
  protected:
    std::string m_stucture_name;

  public:
    WriterBase () {
    }
    virtual ~WriterBase () {
    }
    std::string get_structure_name () {
        return m_stucture_name;
    }
    virtual void saveData (std::vector<data_type>&     p_positions_x,
                           std::vector<data_type>&     p_positions_y,
                           std::vector<data_type>&     p_positions_z,
                           std::vector<unsigned long>& p_ids) = 0;
    virtual void start ()                                     = 0;
    virtual void end ()                                       = 0;
};

#endif /* SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_ */
