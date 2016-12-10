/*
 * LennardJonesAlgorithm.hpp
 *
 *  Created on: Nov 18, 2016
 *      Author: benjamin
 */

#ifndef SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_
#define SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_

#include "AlgorithmBase.hpp"
/*
 * definitions are in the latex-document with the same name as this class
 * _a -> actual Value
 * _b -> next Value
 * step_1 manipulations on only one particle
 * step 2 calculate forces between particles
 * step 3 swap arrays for old and new positions
 * */
class AlgorithmLennardJones : public AlgorithmBase {
  private:
    data_type A_ij;
    data_type B_ij;
    data_type m_i;
    data_type m_j;
    void step_1_local (const data_type& p_position_a, data_type& p_position_b);

  public:
    AlgorithmLennardJones (s_options& p_options);
    void step_1 (const data_type& p_position_ax,
                 const data_type& p_position_ay,
                 const data_type& p_position_az,
                 data_type&       p_position_bx,
                 data_type&       p_position_by,
                 data_type&       p_position_bz);
    void step_2 (const data_type&       p_position_aix,
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
                 const unsigned long    p_index_j_end);
};

#endif /* SRC_ALGORITHMS_LENNARDJONESALGORITHM_HPP_ */
