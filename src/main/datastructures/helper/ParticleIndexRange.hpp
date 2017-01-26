/*
 * ParticleIndexRange.hpp
 *
 *  Created on: Jan 24, 2017
 *      Author: benjamin
 */

#ifndef SRC_MAIN_DATASTRUCTURES_HELPER_PARTICLEINDEXRANGE_HPP_
#define SRC_MAIN_DATASTRUCTURES_HELPER_PARTICLEINDEXRANGE_HPP_

struct ParticleIndexRange {
    unsigned long m_left_index, m_right_index;
    ParticleIndexRange (unsigned long p_left_index, unsigned long p_right_index) : m_left_index (p_left_index), m_right_index (p_right_index) {
    }
};

#endif /* SRC_MAIN_DATASTRUCTURES_HELPER_PARTICLEINDEXRANGE_HPP_ */
