/*
 * ParticleBoundsCorrectionWraparound.hpp
 *
 *  Created on: 06.12.2016
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTIONWRAPAROUND_HPP_
#define SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTIONWRAPAROUND_HPP_

#include "ParticleBoundsCorrection.hpp"

class ParticleBoundsCorrectionWraparound : public ParticleBoundsCorrection {
  public:
    ParticleBoundsCorrectionWraparound (Vec3f& p_bounds);
    virtual ~ParticleBoundsCorrectionWraparound ();
    bool updatePosition (data_type&   m_x,
                         data_type&   m_y,
                         data_type&   m_z,
                         data_type&   m_other_x,
                         data_type&   m_other_y,
                         data_type&   m_other_z,
                         const Vec3f& m_corner000,
                         const Vec3f& m_corner111);
    bool updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z);
};

#endif /* SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTIONWRAPAROUND_HPP_ */
