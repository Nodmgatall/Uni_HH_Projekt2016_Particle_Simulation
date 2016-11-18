/*
 * LennardJonesAlgorithm.hpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_
#define SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_

#include "../IO/OptionsSimulation.hpp"

class LennardJonesAlgorithm {
    private:
    static float A_ij;
    static float B_ij;
    static float m_i;
    static float m_j;
    static void step_1_local (float &p_position_a, float &p_position_b);

    public:
    static void init (s_simulator_options *options);
    static void step_1 (float &p_position_ax,
                        float &p_position_ay,
                        float &p_position_az,
                        float &p_position_bx,
                        float &p_position_by,
                        float &p_position_bz);
    static void step_2 (float &p_position_aix,
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
                        float &p_position_bjz);
};

#endif /* SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_ */
