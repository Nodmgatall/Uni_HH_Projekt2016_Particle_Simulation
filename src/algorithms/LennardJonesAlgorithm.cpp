/*
 * LennardJonesAlgorithm.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#include "LennardJonesAlgorithm.hpp"

float LennardJonesAlgorithm::A_ij = 1;
float LennardJonesAlgorithm::B_ij = 1;
float LennardJonesAlgorithm::m_i  = 1;
float LennardJonesAlgorithm::m_j  = 1;

void LennardJonesAlgorithm::init (s_simulator_options *options) {
    A_ij = 48 * options->m_timestep * options->m_timestep;
    B_ij = 24 * options->m_timestep * options->m_timestep;
    m_i  = 1;
    m_j  = 1;
}
