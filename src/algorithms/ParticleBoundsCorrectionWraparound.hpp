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
    ParticleBoundsCorrectionWraparound (vec3f *p_bounds);
    virtual ~ParticleBoundsCorrectionWraparound ();
    bool updatePosition (float &m_x,
                         float &m_y,
                         float &m_z,
                         float &m_other_x,
                         float &m_other_y,
                         float &m_other_z,
                         vec3f &m_corner000,
                         vec3f &m_corner111);
};

#endif /* SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTIONWRAPAROUND_HPP_ */
