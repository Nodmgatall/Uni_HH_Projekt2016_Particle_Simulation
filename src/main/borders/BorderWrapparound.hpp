/*
 * BorderWrapparound.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTIONWRAPAROUND_HPP_
#define SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTIONWRAPAROUND_HPP_
#include "BorderBase.hpp"
class BorderWrapparound : public BorderBase {
  public:
    /**
     * constructor
     */
    BorderWrapparound (Vec3f& p_bounds);
    /**
     * destructor
     */
    virtual ~BorderWrapparound ();
    bool updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z, const Vec3f& m_corner000, const Vec3f& m_corner111) override;
    bool updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z) override;
    bool updatePosition (ParticleGroup& p_cell, int p_idx_a, bool& p_error_happened) override;
};
#endif /* SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTIONWRAPAROUND_HPP_ */
