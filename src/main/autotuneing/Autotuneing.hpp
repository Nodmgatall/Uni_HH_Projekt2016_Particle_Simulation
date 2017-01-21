/*
 * Autotuneing.hpp
 *
 *  Created on: Jan 21, 2017
 *      Author: benjamin
 */

#ifndef SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_
#define SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_

#include "datastructures/DatastructureFactory.hpp"
#include "options/Options.hpp"
#include <autotuneing/DatastructureAnalyser.hpp>

class Autotuneing {
  public:
    static inline DatastructureBase get_best_datastructure (s_options& p_options) {
        DatastructureAnalyser* analyser = 0;
        switch (p_options.m_input_type) {
            case e_input_type::GENERATOR_RANDOM_UNIFORM:
            case e_input_type::GENERATOR_GRID_DISTRIBUTION: {
                // the particles are evenly distributed
                p_options.m_data_structure_type = e_datastructure_type::GRID;
                break;
            }
            case e_input_type::GENERATOR_MULTIPLE_OBJECTS: {
                // the particles are in different cells, but inside the cells list structure may
                // improve the calculations
                p_options.m_data_structure_type = e_datastructure_type::LISTEDGIRD;
                break;
            }
            case e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE: {
                // particles are distributed at a single point. grid wont help here
                p_options.m_data_structure_type = e_datastructure_type::LIST_BENJAMIN;
                break;
            }
            case e_input_type::GENERATOR_RANDOM:
            case e_input_type::FILE_CSV: {
                // here we need to scan the entire file to decide what to do
                analyser = new DatastructureAnalyser (p_options,
                                                      BorderWrapparound (p_options.m_bounds),
                                                      AlgorithmLennardJones (p_options),
                                                      FileWriterCSV (p_options, ""));
                break;
            }
        }
    }
};

#endif /* SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_ */

/*
 * TODO data into analyser
 * TODO analyse
 * TODO data to final structure
 *
 */
