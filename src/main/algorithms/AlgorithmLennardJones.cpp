/*
 * LennardJonesAlgorithm.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#include "AlgorithmLennardJones.hpp"
AlgorithmLennardJones::AlgorithmLennardJones (s_options& p_options) : AlgorithmBase (p_options) {
    m_stucture_name = "AlgorithmLennardJones";
    A_ij            = 48 * p_options.m_timestep * p_options.m_timestep;
    B_ij            = 24 * p_options.m_timestep * p_options.m_timestep;
    m_i             = 1;
    m_j             = 1;
}
void AlgorithmLennardJones::step_1_local (const data_type& p_position_a, data_type& p_position_b) {
    p_position_b = p_position_a * 2 - p_position_b;
}

void AlgorithmLennardJones::step_1 (const data_type& p_position_ax,
                                    const data_type& p_position_ay,
                                    const data_type& p_position_az,
                                    data_type&       p_position_bx,
                                    data_type&       p_position_by,
                                    data_type&       p_position_bz) {
    step_1_local (p_position_ax, p_position_bx);
    step_1_local (p_position_ay, p_position_by);
    step_1_local (p_position_az, p_position_bz);
}
void AlgorithmLennardJones::step_2 (const data_type&       p_position_aix,
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
        const data_type r_ij_2  = d_x * d_x + d_y * d_y + d_z * d_z;
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
// PROOF OF CONCEPT! do not use!
// NOT USABLE FOR GRID since it is not yet implemented to ignore the particle that
// these calculations are done for!
// also not implementd is the condition if they are in only in rc and not in rc + shell_rc!
/*
void AlgorithmLennardJones::velocityVerletScheme (data_type* distances,
                                                  data_type& delta_t,
                                                  data_type  acceleration,
                                                  data_type,
                                                  data_type     velocity,
                                                  data_type     mass,
                                                  unsigned long number_of_interactions) {
    for (unsigned long particle_idx = 0; particle_idx < number_of_interactions) {
        data_type distance_ts1 = distance + veloctity * delta_t + (0.5) * (acceleration *
acceleration);
        data_type velocity_half_dt velocity + 0.5 * acceleration;
        data_type acceleration_ts1 (-1 / mass) * LennardJonesPotential (distance_ts1);
        data_type velocity_ts1;
        velocity_half_dt + 0.5 * acceleration_ts1* delta_t;
    }
}

void AlgorithmLennardJones::LennardJonesPotential (data_type distance_14, data_type distance_8) {
    return (1 / distance_13 - 0.5 * (1 / distance_8)) * distance_scalar * direction;
}
*/
