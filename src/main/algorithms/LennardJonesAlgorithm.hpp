/*
 * LennardJonesAlgorithm.hpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_
#define SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_

#include "../Definitions.hpp"
#include "../IO/Options.hpp"
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
    static data_type   A_ij;
    static data_type   B_ij;
    static data_type   m_i;
    static data_type   m_j;
    static inline void step_1_local (const data_type &p_position_a, data_type &p_position_b) {
        p_position_b = p_position_a * 2 - p_position_b;
    }

    public:
    static void init (const s_options &options) {
        A_ij = 48 * options.m_timestep * options.m_timestep;
        B_ij = 24 * options.m_timestep * options.m_timestep;
        m_i  = 1;
        m_j  = 1;
    }
    static inline void step_1 (const data_type &p_position_ax,
                               const data_type &p_position_ay,
                               const data_type &p_position_az,
                               data_type &      p_position_bx,
                               data_type &      p_position_by,
                               data_type &      p_position_bz) {
        step_1_local (p_position_ax, p_position_bx);
        step_1_local (p_position_ay, p_position_by);
        step_1_local (p_position_az, p_position_bz);
    }
    static inline void step_2 (const data_type &p_position_aix,
                               const data_type &p_position_aiy,
                               const data_type &p_position_aiz,
                               data_type &      p_position_bix,
                               data_type &      p_position_biy,
                               data_type &      p_position_biz,
                               const data_type &p_position_ajx,
                               const data_type &p_position_ajy,
                               const data_type &p_position_ajz,
                               data_type &      p_position_bjx,
                               data_type &      p_position_bjy,
                               data_type &      p_position_bjz) {
        const data_type d_x     = p_position_ajx - p_position_aix;
        const data_type d_y     = p_position_ajy - p_position_aiy;
        const data_type d_z     = p_position_ajz - p_position_aiz;
        const data_type r_ij_2  = d_x * d_x + d_y * d_y + d_z * d_z;
        const data_type r_ij_4  = r_ij_2 * r_ij_2;
        const data_type r_ij_6  = r_ij_2 * r_ij_4;
        const data_type r_ij_14 = r_ij_6 * r_ij_6 * r_ij_2;
        const data_type s_ij    = (A_ij - B_ij * r_ij_6) / (r_ij_14);
        const data_type s_ij_x  = s_ij * d_x;
        const data_type s_ij_y  = s_ij * d_y;
        const data_type s_ij_z  = s_ij * d_z;
        p_position_bix += s_ij_x / m_i;
        p_position_biy += s_ij_y / m_i;
        p_position_biz += s_ij_z / m_i;
        p_position_bjx -= s_ij_x / m_j;
        p_position_bjy -= s_ij_y / m_j;
        p_position_bjz -= s_ij_z / m_j;
    }
};

#endif /* SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_ */
