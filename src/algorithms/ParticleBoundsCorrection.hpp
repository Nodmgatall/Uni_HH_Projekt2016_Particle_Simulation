/*
 * ParticleBoundsCorrection.hpp
 *
 *  Created on: 06.12.2016
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTION_HPP_
#define SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTION_HPP_
#include "../vec3.hpp"
class ParticleBoundsCorrection {
    protected:
    vec3f *m_bounds;

    public:
    ParticleBoundsCorrection (vec3f *p_bounds) : m_bounds (p_bounds) {
    }
    virtual ~ParticleBoundsCorrection () {
    }
    /**
     * check if the positions are within the cube between m_corner000 m_corner111.
     * updates the position based on m_bounds
     * if position changed m_otherx/y/z will move by the same offset
     * returns if a the position values have changed
     * @param m_x
     * @param m_y
     * @param m_z
     * @param m_corner000
     * @param m_corner111
     * @return
     */
    virtual bool updatePosition (float &m_x,
                                 float &m_y,
                                 float &m_z,
                                 float &m_other_x,
                                 float &m_other_y,
                                 float &m_other_z,
                                 vec3f &m_corner000,
                                 vec3f &m_corner111) = 0;
};

#endif /* SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTION_HPP_ */
