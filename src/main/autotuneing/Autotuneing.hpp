/*
 * Autotuneing.hpp
 *
 *  Created on: Jan 21, 2017
 *      Author: benjamin
 */

#ifndef SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_
#define SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_

#include "options/Options.hpp"

class Autotuneing {
  public:
    static inline e_datastructure_type get_best_datastructure (s_options& p_options) {
        switch (p_options.m_input_type) {
            case e_input_type::GENERATOR_RANDOM_UNIFORM:
            case e_input_type::GENERATOR_GRID_DISTRIBUTION: {
                // the particles are evenly distributed
                return e_datastructure_type::GRID;
            }
            case e_input_type::GENERATOR_MULTIPLE_OBJECTS: {
                // the particles are in different cells, but inside the cells list structure may
                // improve the calculations
                return e_datastructure_type::LISTEDGIRD;
            }
            case e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE: {
                // particles are distributed at a single point. grid wont help here
                return e_datastructure_type::LIST_BENJAMIN;
            }
            case e_input_type::GENERATOR_RANDOM:
            case e_input_type::FILE_CSV: {
                // here we need to scan the entire file to decide what to do
                break;
            }
        }
        return p_options.m_data_structure_type;
    }
};

#endif /* SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_ */
