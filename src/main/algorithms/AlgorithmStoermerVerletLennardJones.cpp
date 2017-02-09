/*
 * LennardJonesAlgorithm.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */
#include "AlgorithmStoermerVerletLennardJones.hpp"
AlgorithmStoermerVerletLennardJones::AlgorithmStoermerVerletLennardJones (s_options& p_options) : AlgorithmBase (p_options) {
    m_stucture_name   = "AlgorithmStoermerVerletLennardJones";
    A_ij              = 48 * p_options.m_timestep * p_options.m_timestep;
    B_ij              = 24 * p_options.m_timestep * p_options.m_timestep;
    m_i               = 1;
    m_j               = 1;
    m_cut_off_squared = p_options.m_cut_off_radius * p_options.m_cut_off_radius;
}
void AlgorithmStoermerVerletLennardJones::step_1_local (const data_type& p_position_a, data_type& p_position_b) {
    p_position_b = p_position_a * 2 - p_position_b;
}
void AlgorithmStoermerVerletLennardJones::step_1 (const data_type& p_position_ax,
                                                  const data_type& p_position_ay,
                                                  const data_type& p_position_az,
                                                  data_type&       p_position_bx,
                                                  data_type&       p_position_by,
                                                  data_type&       p_position_bz) {
    step_1_local (p_position_ax, p_position_bx);
    step_1_local (p_position_ay, p_position_by);
    step_1_local (p_position_az, p_position_bz);
}
#ifndef OPTIMIZED
void AlgorithmStoermerVerletLennardJones::step_2 (const data_type&       p_position_aix,
                                                  const data_type&       p_position_aiy,
                                                  const data_type&       p_position_aiz,
                                                  data_type&             p_position_bix,
                                                  data_type&             p_position_biy,
                                                  data_type&             p_position_biz,
                                                  const data_type* const p_position_ajx,
                                                  const data_type* const p_position_ajy,
                                                  const data_type* const p_position_ajz,
                                                  data_type* const       p_position_bjx,
                                                  data_type* const       p_position_bjy,
                                                  data_type* const       p_position_bjz,
                                                  const unsigned long    p_index_j_begin,
                                                  const unsigned long    p_index_j_end) {
    unsigned long j;
    for (j = p_index_j_begin; j < p_index_j_end; j++) {
        // Distance vector calculation
        const data_type d_x = p_position_ajx[j] - p_position_aix;
        const data_type d_y = p_position_ajy[j] - p_position_aiy;
        const data_type d_z = p_position_ajz[j] - p_position_aiz;
        // distance scalar squared calc
        const data_type r_ij_2 = d_x * d_x + d_y * d_y + d_z * d_z;
        if (r_ij_2 < m_cut_off_squared) {
            const data_type r_ij_4  = r_ij_2 * r_ij_2;
            const data_type r_ij_6  = r_ij_2 * r_ij_4;
            const data_type r_ij_14 = r_ij_6 * r_ij_6 * r_ij_2;
            const data_type s_ij    = (A_ij - B_ij * r_ij_6) / (r_ij_14);
            const data_type s_ij_x  = s_ij * d_x;
            const data_type s_ij_y  = s_ij * d_y;
            const data_type s_ij_z  = s_ij * d_z;
            p_position_bix -= s_ij_x / m_i;
            p_position_biy -= s_ij_y / m_i;
            p_position_biz -= s_ij_z / m_i;
            p_position_bjx[j] += s_ij_x / m_j;
            p_position_bjy[j] += s_ij_y / m_j;
            p_position_bjz[j] += s_ij_z / m_j;
        }
    }
}
#else
#include <iostream>
void AlgorithmStoermerVerletLennardJones::step_2 (const data_type& __restrict__ p_position_aix,
                                                  const data_type& __restrict__ p_position_aiy,
                                                  const data_type& __restrict__ p_position_aiz,
                                                  data_type& __restrict__ p_position_bix,
                                                  data_type& __restrict__ p_position_biy,
                                                  data_type& __restrict__ p_position_biz,
                                                  const data_type* const __restrict__ p_position_ajx,
                                                  const data_type* const __restrict__ p_position_ajy,
                                                  const data_type* const __restrict__ p_position_ajz,
                                                  data_type* const __restrict__ p_position_bjx,
                                                  data_type* const __restrict__ p_position_bjy,
                                                  data_type* const __restrict__ p_position_bjz,
                                                  const unsigned long p_index_j_begin,
                                                  const unsigned long p_index_j_end) {
    unsigned long          num_of_calculations = p_index_j_end - p_index_j_begin;
    std::vector<data_type> change_x (num_of_calculations);
    std::vector<data_type> change_y (num_of_calculations);
    std::vector<data_type> change_z (num_of_calculations);

    // data_type change_x;
    // data_type change_y;
    // data_type change_z;

    const data_type* const __restrict__ x_pos_other_a = p_position_ajx + p_index_j_begin;
    const data_type* const __restrict__ y_pos_other_a = p_position_ajy + p_index_j_begin;
    const data_type* const __restrict__ z_pos_other_a = p_position_ajz + p_index_j_begin;

    data_type* const __restrict__ x_pos_other_b = p_position_bjx + p_index_j_begin;
    data_type* const __restrict__ y_pos_other_b = p_position_bjy + p_index_j_begin;
    data_type* const __restrict__ z_pos_other_b = p_position_bjz + p_index_j_begin;
    data_type     d_x;
    data_type     d_y;
    data_type     d_z;
    data_type     s_ij;
    data_type     r_ij_2;
    unsigned long j;
    // vectorized
    for (j = 0; j < num_of_calculations; j++) {
        d_x    = x_pos_other_a[j] - p_position_aix;
        d_y    = y_pos_other_a[j] - p_position_aiy;
        d_z    = z_pos_other_a[j] - p_position_aiz;
        r_ij_2 = d_x * d_x + d_y * d_y + d_z * d_z;

        // NOTE: badly visible if statement for vectorization
        s_ij = r_ij_2 > m_cut_off_squared ? 0 : 1;

        const data_type r_ij_4  = r_ij_2 * r_ij_2;
        const data_type r_ij_6  = r_ij_2 * r_ij_4;
        const data_type r_ij_14 = r_ij_6 * r_ij_6 * r_ij_2;

        s_ij *= (A_ij - B_ij * r_ij_6) / (r_ij_14);
        change_x[j] = (s_ij * d_x) / m_i;
        change_y[j] = (s_ij * d_y) / m_i;
        change_z[j] = (s_ij * d_z) / m_i;
        x_pos_other_b[j] += change_x[j];
        y_pos_other_b[j] += change_y[j];
        z_pos_other_b[j] += change_z[j];
               /*
        change_x[j] =( s_ij * d_x) / m_i;
        change_y[j] =( s_ij * d_y) / m_i;
        change_z[j] =( s_ij * d_z) / m_i;
        x_pos_other_b[j] +=  change_x[j];
        y_pos_other_b[j] +=  change_y[j];
        z_pos_other_b[j] +=  change_z[j];
        p_position_bix -= change_x[j];
        p_position_biy -= change_y[j];
        p_position_biz -= change_z[j];

        */
    }
    for (j = 0; j < num_of_calculations; j++) {
            p_position_bix -= change_x[j];
            p_position_biy -= change_y[j];
            p_position_biz -= change_z[j];
        }

}
#endif
void AlgorithmStoermerVerletLennardJones::step_2_offset (const data_type&       p_offset_position_aix,
                                                         const data_type&       p_offset_position_aiy,
                                                         const data_type&       p_offset_position_aiz,
                                                         const data_type&       p_position_aix,
                                                         const data_type&       p_position_aiy,
                                                         const data_type&       p_position_aiz,
                                                         data_type&             p_position_bix,
                                                         data_type&             p_position_biy,
                                                         data_type&             p_position_biz,
                                                         const data_type* const p_position_ajx,
                                                         const data_type* const p_position_ajy,
                                                         const data_type* const p_position_ajz,
                                                         data_type* const       p_position_bjx,
                                                         data_type* const       p_position_bjy,
                                                         data_type* const       p_position_bjz,
                                                         const unsigned long    p_index_j_begin,
                                                         const unsigned long    p_index_j_end) {
    unsigned long   j;
    const data_type ix = p_position_aix + p_offset_position_aix;
    const data_type iy = p_position_aiy + p_offset_position_aiy;
    const data_type iz = p_position_aiz + p_offset_position_aiz;
    for (j = p_index_j_begin; j < p_index_j_end; j++) {
        // Distance vector calculation
        const data_type d_x = p_position_ajx[j] - ix;
        const data_type d_y = p_position_ajy[j] - iy;
        const data_type d_z = p_position_ajz[j] - iz;
        // distance scalar squared calc
        const data_type r_ij_2 = d_x * d_x + d_y * d_y + d_z * d_z;
        if (r_ij_2 < m_cut_off_squared) {
            const data_type r_ij_4  = r_ij_2 * r_ij_2;
            const data_type r_ij_6  = r_ij_2 * r_ij_4;
            const data_type r_ij_14 = r_ij_6 * r_ij_6 * r_ij_2;
            const data_type s_ij    = (A_ij - B_ij * r_ij_6) / (r_ij_14);
            const data_type s_ij_x  = s_ij * d_x;
            const data_type s_ij_y  = s_ij * d_y;
            const data_type s_ij_z  = s_ij * d_z;
            p_position_bix -= s_ij_x / m_i;
            p_position_biy -= s_ij_y / m_i;
            p_position_biz -= s_ij_z / m_i;
            p_position_bjx[j] += s_ij_x / m_j;
            p_position_bjy[j] += s_ij_y / m_j;
            p_position_bjz[j] += s_ij_z / m_j;
        }
    }
}
