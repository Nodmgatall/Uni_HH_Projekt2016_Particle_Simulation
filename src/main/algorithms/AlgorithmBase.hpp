/*
 * AlgorithmBase.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_
#define SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_

#include "Definitions.hpp"
#include "options/Options.hpp"

class AlgorithmBase {
  protected:
    s_options&  m_options;
    std::string m_stucture_name;

  public:
    AlgorithmBase (s_options& p_options) : m_options (p_options) {
    }
    virtual ~AlgorithmBase () {
    }
    std::string get_structure_name () {
        return m_stucture_name;
    }
    /**
     *
     * @param p_position_ax current position x
     * @param p_position_ay current position y
     * @param p_position_az current position z
     * @param p_position_bx input=old position x -> output=next position x
     * @param p_position_by input=old position y -> output=next position y
     * @param p_position_bz input=old position z -> output=next position z
     */
    virtual void step_1 (const data_type& p_position_ax,
                         const data_type& p_position_ay,
                         const data_type& p_position_az,
                         data_type&       p_position_bx,
                         data_type&       p_position_by,
                         data_type&       p_position_bz) = 0;
    /**
     *
     * @param p_position_aix current position x for particle i
     * @param p_position_aiy current position y for particle i
     * @param p_position_aiz current position z for particle i
     * @param p_position_bix next position x for particle i
     * @param p_position_biy next position y for particle i
     * @param p_position_biz next position z for particle i
     * @param p_position_ajx current position (array) x for particles j
     * @param p_position_ajy current position (array) y for particles j
     * @param p_position_ajz current position (array) z for particles j
     * @param p_position_bjx next position (array) x for particles j
     * @param p_position_bjy next position (array) y for particles j
     * @param p_position_bjz next position (array) z for particles j
     * @param p_index_j_begin array begin for particles j (inclusive)
     * @param p_index_j_end array end for particles j (exclusive)
     */
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
                         const unsigned long    p_index_j_end) = 0;
};

#endif /* SRC_MAIN_ALGORITHMS_ALGORITHMBASE_HPP_ */
