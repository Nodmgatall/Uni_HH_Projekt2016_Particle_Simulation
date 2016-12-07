/*
 * LennardJonesAlgorithm.hpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_
#define SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_

#include "../IO/OptionsSimulation.hpp"
#include "../tools/Debug.hpp"
/*
 * definitions are in the latex-document with the same name as this class
 * _a -> actual Value
 * _b -> next Value
 * step_1 manipulations on only one particle
 * step 2 calculate forces between particles
 * step 3 swap arrays for old and new positions
 * */
class LennardJonesAlgorithm {
    private:
    static float       A_ij;
    static float       B_ij;
    static float       m_i;
    static float       m_j;
    static inline void step_1_local (const float &p_position_a, float &p_position_b) {
        p_position_b = p_position_a * 2 - p_position_b;
    }

    public:
    static void init (const s_simulator_options &options) {
        A_ij = 48 * options.m_timestep * options.m_timestep;
        B_ij = 24 * options.m_timestep * options.m_timestep;
        m_i  = 1;
        m_j  = 1;
    }
    static inline void step_1 (const float &p_position_ax,
                               const float &p_position_ay,
                               const float &p_position_az,
                               float &      p_position_bx,
                               float &      p_position_by,
                               float &      p_position_bz) {
        step_1_local (p_position_ax, p_position_bx);
        step_1_local (p_position_ay, p_position_by);
        step_1_local (p_position_az, p_position_bz);
    }
    static inline void step_2 (const float &p_position_aix,
                               const float &p_position_aiy,
                               const float &p_position_aiz,
                               float &      p_position_bix,
                               float &      p_position_biy,
                               float &      p_position_biz,
                               const float &p_position_ajx,
                               const float &p_position_ajy,
                               const float &p_position_ajz,
                               float &      p_position_bjx,
                               float &      p_position_bjy,
                               float &      p_position_bjz) {
        const float d_x     = p_position_ajx - p_position_aix;
        const float d_y     = p_position_ajy - p_position_aiy;
        const float d_z     = p_position_ajz - p_position_aiz;
        const float r_ij_2  = d_x * d_x + d_y * d_y + d_z * d_z;
        const float r_ij_4  = r_ij_2 * r_ij_2;
        const float r_ij_6  = r_ij_2 * r_ij_4;
        const float r_ij_14 = r_ij_6 * r_ij_6 * r_ij_2;
        const float s_ij    = (A_ij - B_ij * r_ij_6) / (r_ij_14);
        const float s_ij_x  = s_ij * d_x;
        const float s_ij_y  = s_ij * d_y;
        const float s_ij_z  = s_ij * d_z;
        p_position_bix += s_ij_x / m_i;
        p_position_biy += s_ij_y / m_i;
        p_position_biz += s_ij_z / m_i;
        p_position_bjx -= s_ij_x / m_j;
        p_position_bjy -= s_ij_y / m_j;
        p_position_bjz -= s_ij_z / m_j;
    }
};

#endif /* SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_ */
