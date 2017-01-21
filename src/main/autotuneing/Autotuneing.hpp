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
        return e_datastructure_type::GRID;
    }
};

#endif /* SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_ */
