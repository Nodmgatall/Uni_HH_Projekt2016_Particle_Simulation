/*
 * ParticleBoundsCorrection.hpp
 *
 *  Created on: 06.12.2016
 *      Author: benjamin
 */
#ifndef SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTION_HPP_
#define SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTION_HPP_
#include "Vec3.hpp"
#include "datastructures/helper/ParticleGroup.hpp"
class BorderBase {
  protected:
    Vec3f&      m_bounds;
    std::string m_stucture_name;

  public:
    /**
     * constructor
     */
    BorderBase (Vec3f& p_bounds) : m_bounds (p_bounds) {
    }
    /**
     * destructor
     */
    virtual ~BorderBase () {
    } /**
     * returns the class name for verifying which subclass is used
     */
    std::string get_structure_name () {
        return m_stucture_name;
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
    virtual bool updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z, const Vec3f& m_corner000, const Vec3f& m_corner111) = 0;
    /**
     * check if the positions are within the cube between 000 m_bounds.
     * updates the position based on m_bounds
     * if position changed m_otherx/y/z will move by the same offset
     * returns if a the position values have changed
     * @param m_x
     * @param m_y
     * @param m_z
     * @return
     */
    virtual bool updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z) = 0;
    virtual bool updatePosition (ParticleGroup& p_cell, int p_idx_a, bool& p_error_happened) = 0;
};
#endif /* SRC_ALGORITHMS_PARTICLEBOUNDSCORRECTION_HPP_ */
