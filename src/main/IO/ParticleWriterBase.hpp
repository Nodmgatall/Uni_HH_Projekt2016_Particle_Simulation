/*
 * ParticleWriterBase.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_
#define SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_

#include "../Definitions.hpp"

class ParticleWriterBase {
  public:
    ParticleWriterBase ();
    virtual ~ParticleWriterBase ();
    virtual void saveData (std::vector<data_type>*     p_positions_x,
                           std::vector<data_type>*     p_positions_y,
                           std::vector<data_type>*     p_positions_z,
                           std::vector<unsigned long>* p_ids);
    virtual void start ();
    virtual void end ();
};

#endif /* SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_ */
