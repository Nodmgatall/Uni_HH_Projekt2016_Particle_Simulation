/*
 * BorderWrapparound.cpp
 *
 *  Created on: 06.12.2016
 *      Author: benjamin
 */
#include "BorderWrapparound.hpp"
BorderWrapparound::BorderWrapparound (Vec3f& p_bounds) : BorderBase (p_bounds) {
    m_stucture_name = "BorderWrapparound";
}
BorderWrapparound::~BorderWrapparound () {
}
bool BorderWrapparound::updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z) {
    return updatePosition (m_x, m_y, m_z, m_other_x, m_other_y, m_other_z, g_vec3f_0, m_bounds);
}
bool BorderWrapparound::updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z, const Vec3f& m_corner000, const Vec3f& m_corner111) {
    Vec3l delta (0);
    if (m_x < m_corner000.x) {
        delta.x = -1;
        while (m_x < 0) {
            m_x += m_bounds.x;
            m_other_x += m_bounds.x;
        }
    } else if (m_x >= m_corner111.x) {
        delta.x = +1;
        while (m_x > m_bounds.x) {
            m_x -= m_bounds.x;
            m_other_x -= m_bounds.x;
        }
    }
    if (m_y < m_corner000.y) {
        delta.y = -1;
        while (m_y < 0) {
            m_y += m_bounds.y;
            m_other_y += m_bounds.y;
        }
    } else if (m_y >= m_corner111.y) {
        delta.y = +1;
        while (m_y > m_bounds.y) {
            m_y -= m_bounds.y;
            m_other_y -= m_bounds.y;
        }
    }
    if (m_z < m_corner000.z) {
        delta.z = -1;
        while (m_z < 0) {
            m_z += m_bounds.z;
            m_other_z += m_bounds.z;
        }
    } else if (m_z >= m_corner111.z) {
        delta.z = +1;
        while (m_z > m_bounds.z) {
            m_z -= m_bounds.z;
            m_other_z -= m_bounds.z;
        }
    }
    return delta.x || delta.y || delta.z;
}
