/*
 * LennardJonesAlgorithm.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#include "AlgorithmLennardJones.hpp"
AlgorithmLennardJones::AlgorithmLennardJones(const s_options &p_options) :
		AlgorithmBase(p_options) {
	A_ij = 48 * p_options.m_timestep * p_options.m_timestep;
	B_ij = 24 * p_options.m_timestep * p_options.m_timestep;
	m_i = 1;
	m_j = 1;
}
void AlgorithmLennardJones::step_1_local(const data_type &p_position_a,
		data_type &p_position_b) {
	p_position_b = p_position_a * 2 - p_position_b;
}

void AlgorithmLennardJones::step_1(const data_type &p_position_ax,
		const data_type &p_position_ay, const data_type &p_position_az,
		data_type & p_position_bx, data_type & p_position_by,
		data_type & p_position_bz) {
	step_1_local(p_position_ax, p_position_bx);
	step_1_local(p_position_ay, p_position_by);
	step_1_local(p_position_az, p_position_bz);
}
void AlgorithmLennardJones::step_2(const data_type &p_position_aix,
		const data_type &p_position_aiy, const data_type &p_position_aiz,
		data_type & p_position_bix, data_type & p_position_biy,
		data_type & p_position_biz, const data_type &p_position_ajx,
		const data_type &p_position_ajy, const data_type &p_position_ajz,
		data_type & p_position_bjx, data_type & p_position_bjy,
		data_type & p_position_bjz) {
	const data_type d_x = p_position_ajx - p_position_aix;
	const data_type d_y = p_position_ajy - p_position_aiy;
	const data_type d_z = p_position_ajz - p_position_aiz;
	const data_type r_ij_2 = d_x * d_x + d_y * d_y + d_z * d_z;
	const data_type r_ij_4 = r_ij_2 * r_ij_2;
	const data_type r_ij_6 = r_ij_2 * r_ij_4;
	const data_type r_ij_14 = r_ij_6 * r_ij_6 * r_ij_2;
	const data_type s_ij = (A_ij - B_ij * r_ij_6) / (r_ij_14);
	const data_type s_ij_x = s_ij * d_x;
	const data_type s_ij_y = s_ij * d_y;
	const data_type s_ij_z = s_ij * d_z;
	p_position_bix += s_ij_x / m_i;
	p_position_biy += s_ij_y / m_i;
	p_position_biz += s_ij_z / m_i;
	p_position_bjx -= s_ij_x / m_j;
	p_position_bjy -= s_ij_y / m_j;
	p_position_bjz -= s_ij_z / m_j;
}
