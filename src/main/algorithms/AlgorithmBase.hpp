/*
 * AlgorithmBase.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_
#define SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_

#include "../Definitions.hpp"
#include "../options/Options.hpp"

class AlgorithmBase {
  private:
    s_options& m_options;

  public:
    AlgorithmBase (s_options& p_options) : m_options (p_options) {
    }
    virtual ~AlgorithmBase () {
        (void) m_options;
    }
    virtual void step_1 (const data_type& p_position_ax,
                         const data_type& p_position_ay,
                         const data_type& p_position_az,
                         data_type&       p_position_bx,
                         data_type&       p_position_by,
                         data_type&       p_position_bz) {
        (void) p_position_ax;
        (void) p_position_ay;
        (void) p_position_az;
        (void) p_position_bx;
        (void) p_position_by;
        (void) p_position_bz;
    }
    virtual void step_2 (const data_type&       p_position_aix,
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
        (void) p_position_aix;
        (void) p_position_aiy;
        (void) p_position_aiz;
        (void) p_position_bix;
        (void) p_position_biy;
        (void) p_position_biz;
        (void) p_position_ajx;
        (void) p_position_ajy;
        (void) p_position_ajz;
        (void) p_position_bjx;
        (void) p_position_bjy;
        (void) p_position_bjz;
        (void) p_index_j_begin;
        (void) p_index_j_end;
    }
};

#endif /* SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_ */
