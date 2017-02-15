/*
 * ParticleGroup.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include <datastructures/helper/ParticleGroup.hpp>
ParticleGroup::ParticleGroup (Vec3l p_idx, Vec3f p_size_per_group) {
    m_idx       = p_idx;
    m_corner000 = Vec3f (m_idx - 1L) * p_size_per_group;
    m_corner111 = Vec3f (m_idx) * p_size_per_group;
}
void ParticleGroup::add_particle (Vec3f p_current_position, Vec3f p_old_position, int p_current_index, int p_id) {
    m_positions_x[p_current_index].push_back (p_current_position.x);
    m_positions_y[p_current_index].push_back (p_current_position.y);
    m_positions_z[p_current_index].push_back (p_current_position.z);
    m_positions_x[!p_current_index].push_back (p_old_position.x);
    m_positions_y[!p_current_index].push_back (p_old_position.y);
    m_positions_z[!p_current_index].push_back (p_old_position.z);
    m_ids.push_back (p_id);
}
