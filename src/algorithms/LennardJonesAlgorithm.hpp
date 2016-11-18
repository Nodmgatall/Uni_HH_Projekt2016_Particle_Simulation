/*
 * LennardJonesAlgorithm.hpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_
#define SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_

#include "../IO/OptionsSimulation.hpp"
/*
 * definitions are in the latex-document with the same name as this class
 * _a -> actual Value
 * _b -> last/next Value
 * */
class LennardJonesAlgorithm {
    private:
    static float       A_ij;
    static float       B_ij;
    static float       m_i;
    static float       m_j;
    static inline void step_1_local (float &p_position_a, float &p_position_b) {
        p_position_b = p_position_a * 2 - p_position_b;
    }

    public:
    static void init (s_simulator_options *options);
    static inline void step_1 (float &p_position_ax,
                               float &p_position_ay,
                               float &p_position_az,
                               float &p_position_bx,
                               float &p_position_by,
                               float &p_position_bz) {
        step_1_local (p_position_ax, p_position_bx);
        step_1_local (p_position_ay, p_position_by);
        step_1_local (p_position_az, p_position_bz);
    }
    static inline void step_2 (float &p_position_aix,
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
        const float d_x;
        const float d_y;
        const float d_z;
        const float r_ij_2;  // r_ij_2=r_ij^2
        const float r_ij_4;  // r_ij_4=r_ij^4
        const float r_ij_6;  // r_ij_6=r_ij^6
        const float r_ij_14; // r_ij_14=r_ij^14
        const float s_ij;
        const float s_ij_x;
        const float s_ij_y;
        const float s_ij_z;
        d_x = p_position_ajx - p_position_aix;
        d_y = p_position_ajy - p_position_aiy;
        d_z = p_position_ajz - p_position_aiz;
        r_ij_2   = d_x * d_x + d_y * d_y + d_z * d_z;
        r_ij_4   = r_ij_2 * r_ij_2;
        r_ij_6   = r_ij_2 * r_ij_4;
        r_ij_14  = r_ij_6 * r_ij_6 * r_ij_2;
        s_ij     = (A_ij - B_ij * r_ij_6) / (r_ij_14);
        s_ij_x   = s_ij * d_x;
        s_ij_y   = s_ij * d_y;
        s_ij_z   = s_ij * d_z;
        p_position_bix += s_ij_x / m_i;
        p_position_biy += s_ij_y / m_i;
        p_position_biz += s_ij_z / m_i;
        p_position_bjx -= s_ij_x / m_j;
        p_position_bjy -= s_ij_y / m_j;
        p_position_bjz -= s_ij_z / m_j;
    }
};

#endif /* SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_ */
