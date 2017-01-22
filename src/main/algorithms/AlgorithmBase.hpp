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
    /**
     * The option struct generated from the parameters given aut program-launch
     */
    s_options& m_options;
    /**
     * identifier of subclass name
     */
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
         * first part of  Calculation
         *
         * @param p_position_ax current_position
         * @param p_position_ay current_position
         * @param p_position_az current_position
         * @param p_position_bx input old_position -> output next_position
         * @param p_position_by input old_position -> output next_position
         * @param p_position_bz input old_position -> output next_position
         */
    virtual void step_1 (const data_type& p_position_ax,
                         const data_type& p_position_ay,
                         const data_type& p_position_az,
                         data_type&       p_position_bx,
                         data_type&       p_position_by,
                         data_type&       p_position_bz) = 0;
    /**
        * second part of Calculation
        * a__ -> current
        * b__ -> next -- modifications inplace!!
        * _i_ -> particle i
        * _j_ -> particles j
        *__x __y __z -> Coordinate-components
        *
        * @param p_position_aix current_position of particle i
        * @param p_position_aiy current_position of particle i
        * @param p_position_aiz current_position of particle i
        * @param p_position_bix next_position of particle i
        * @param p_position_biy next_position of particle i
        * @param p_position_biz next_position of particle i
        * @param p_position_ajx current_positions of particles j
        * @param p_position_ajy current_positions of particles j
        * @param p_position_ajz current_positions of particles j
        * @param p_position_bjx next_positions of particles j
        * @param p_position_bjy next_positions of particles j
        * @param p_position_bjz next_positions of particles j
        * @param p_index_j_begin array-bounds for j
        * @param p_index_j_end array-bounds for j
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
    /**
         * second part of  Calculation
         * a__ -> current
         * b__ -> next -- modifications inplace!!
         * _i_ -> particle i
         * _j_ -> particles j
         *__x __y __z -> Coordinate-components
         *
         * @param p_offset_position_aix offset for particle i to calculate interactions around
      *borders
         * @param p_offset_position_aiy offset for particle i to calculate interactions around
      *borders
         * @param p_offset_position_aiz offset for particle i to calculate interactions around
      *borders
         * @param p_position_aix current_position of particle i
         * @param p_position_aiy current_position of particle i
         * @param p_position_aiz current_position of particle i
         * @param p_position_bix next_position of particle i
         * @param p_position_biy next_position of particle i
         * @param p_position_biz next_position of particle i
         * @param p_position_ajx current_positions of particles j
         * @param p_position_ajy current_positions of particles j
         * @param p_position_ajz current_positions of particles j
         * @param p_position_bjx next_positions of particles j
         * @param p_position_bjy next_positions of particles j
         * @param p_position_bjz next_positions of particles j
         * @param p_index_j_begin array-bounds for j
         * @param p_index_j_end array-bounds for j
         */
    virtual void step_2_offset (const data_type&       p_offset_position_aix,
                                const data_type&       p_offset_position_aiy,
                                const data_type&       p_offset_position_aiz,
                                const data_type&       p_position_aix,
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
