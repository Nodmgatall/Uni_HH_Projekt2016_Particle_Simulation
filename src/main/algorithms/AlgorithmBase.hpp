/*
 * AlgorithmBase.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_
#define SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_

#include "../Definitions.hpp"
#include "../IO/Options.hpp"

class AlgorithmBase {
    private:
    const s_options &m_options;

    public:
    AlgorithmBase (const s_options &p_options) : m_options (p_options) {
    }
    virtual ~AlgorithmBase () {
    }
    virtual void step_1 (const data_type &p_position_ax,
                         const data_type &p_position_ay,
                         const data_type &p_position_az,
                         data_type &      p_position_bx,
                         data_type &      p_position_by,
                         data_type &      p_position_bz) = 0;
    virtual void step_2 (const data_type &p_position_aix,
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
                         data_type &      p_position_bjz) = 0;
};

#endif /* SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_ */
