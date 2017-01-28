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
bool BorderWrapparound::updatePosition (ParticleGroup& p_cell, int p_idx_a, bool& p_error_happened) {
    bool flag = false;
    int  i, j;
    for (i = p_cell.m_ids.size () - 1; i >= 0; i--) {
        Vec3l idx;
        while (p_cell.m_positions_x[p_idx_a][i] < 0) {
            flag = true;
            if (!(p_cell.m_positions_x[p_idx_a][i] >= -m_bounds.x * 10)) { // Comparisons with NaN (except!=)return false
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                p_error_happened = true;
                m_error_stream << "a" << std::endl;
                return true;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_x[j][i] += m_bounds.x;
            }
        }
        while (p_cell.m_positions_x[p_idx_a][i] >= m_bounds.x) {
            flag = true;
            if (!(p_cell.m_positions_x[p_idx_a][i] <= m_bounds.x * 10)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                p_error_happened = true;
                return true;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_x[j][i] -= m_bounds.x;
            }
        }
        while (p_cell.m_positions_y[p_idx_a][i] < 0) {
            flag = true;
            if (!(p_cell.m_positions_y[p_idx_a][i] >= -m_bounds.y * 10)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                p_error_happened = true;
                return true;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_y[j][i] += m_bounds.y;
            }
        }
        while (p_cell.m_positions_y[p_idx_a][i] > m_bounds.y) {
            flag = true;
            if (!(p_cell.m_positions_y[p_idx_a][i] <= m_bounds.y * 10)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                p_error_happened = true;
                return true;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_y[j][i] -= m_bounds.y;
            }
        }
        while (p_cell.m_positions_z[p_idx_a][i] < 0) {
            flag = true;
            if (!(p_cell.m_positions_z[p_idx_a][i] >= -m_bounds.z * 10)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                p_error_happened = true;
                return true;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_z[j][i] += m_bounds.z;
            }
        }
        while (p_cell.m_positions_z[p_idx_a][i] >= m_bounds.z) {
            flag = true;
            if (!(p_cell.m_positions_z[p_idx_a][i] <= m_bounds.z * 10)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                p_error_happened = true;
                return true;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_z[j][i] -= m_bounds.z;
            }
        }
    }
    return flag;
}
