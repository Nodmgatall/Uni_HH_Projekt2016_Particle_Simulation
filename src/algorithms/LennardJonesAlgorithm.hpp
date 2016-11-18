/*
 * LennardJonesAlgorithm.hpp
 *
 *  Created on: Nov i8, j0i6
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_
#define SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_

// Siehe Definitionen im PDF
inline void lennard_jones_algorithm_1_local (float &p_position_a, float &p_position_b) {
    p_position_b = p_position_a * 2 - p_position_b;
}
inline void lennard_jones_algorithm_1 (float &p_position_ax,
                                       float &p_position_ay,
                                       float &p_position_az,
                                       float &p_position_bx,
                                       float &p_position_by,
                                       float &p_position_bz) {
    lennard_jones_algorithm_1_local (p_position_ax, p_position_bx);
    lennard_jones_algorithm_1_local (p_position_ay, p_position_by);
    lennard_jones_algorithm_1_local (p_position_az, p_position_bz);
}
inline void lennard_jones_algorithm_2 (float &p_position_aix,
                                       float &p_position_aiy,
                                       float &p_position_aiz,
                                       float &p_position_bix,
                                       float &p_position_biy,
                                       float &p_position_biz,
                                       float &p_position_ajx,
                                       float &p_position_ajy,
                                       float &p_position_ajz,
                                       float &p_position_bjx,
                                       float &p_position_bjy,
                                       float &p_position_bjz) {
    // definition im PDF (A_ij = B_ij = m_i = m_j = 1) solange nur eine Partikelsorte verwendet wird
    const float A_ij     = 1;
    const float B_ij     = 1;
    const float m_i      = 1;
    const float m_j      = 1;
    float       delta_ax = p_position_ajx - p_position_aix;
    float       delta_ay = p_position_ajy - p_position_aiy;
    float       delta_az = p_position_ajz - p_position_aiz;
    // r_ij_* -> * für den exponenten des abstands
    float r_ij_2  = delta_ax * delta_ax + delta_ay * delta_ay + delta_az * delta_az;
    float r_ij_4  = r_ij_2 * r_ij_2;
    float r_ij_6  = r_ij_2 * r_ij_4;
    float r_ij_i4 = r_ij_6 * r_ij_6 * r_ij_2;
    float s_ij_   = (A_ij - B_ij * r_ij_6) / (r_ij_i4);
    float s_ij_x  = s_ij_ * delta_ax;
    float s_ij_y  = s_ij_ * delta_ay;
    float s_ij_z  = s_ij_ * delta_az;
    p_position_bix += s_ij_x / m_i;
    p_position_biy += s_ij_y / m_i;
    p_position_biz += s_ij_z / m_i;
    p_position_bjx -= s_ij_x / m_j;
    p_position_bjy -= s_ij_y / m_j;
    p_position_bjz -= s_ij_z / m_j;
}
#endif /* SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_ */
