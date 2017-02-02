/*
 * Autotuneing.hpp
 *
 *  Created on: Jan 21, 2017
 *      Author: benjamin
 */
#ifndef SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_
#define SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_
#include "autotuneing/DatastructureAnalyser.hpp"
#include "datastructures/DatastructureFactory.hpp"
#include "io/input/InputBase.hpp"
#include "io/input/InputFactory.hpp"
#include "options/Options.hpp"
class Autotuneing {
  public:
    /**
     * returns an fully initialized datastructure which should be the fastest for the given input
     */
    static inline DatastructureBase* get_best_datastructure (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_writer) {
        DatastructureAnalyser* analyser = 0;
        switch (p_options.m_input_type) {
            case e_input_type::GENERATOR_RANDOM_UNIFORM:
            case e_input_type::GENERATOR_GRID_DISTRIBUTION: {
                // the particles are evenly distributed
                // useing the same function as in DatastructureBase::calculate_next_datastructure_rebuild to calculate iteration-count to rebuild
                if (2.0 * p_options.m_initial_speed < (p_options.m_cut_off_radius * (p_options.m_cut_off_factor - 1.0) - 1.0)) {
                    p_options.m_data_structure_type = e_datastructure_type::GRID_LIST;
                    // PROVED by tests
                } else {
                    p_options.m_data_structure_type = e_datastructure_type::GRID;
                    // PROVED by tests
                }
                break;
            }
            case e_input_type::GENERATOR_MULTIPLE_OBJECTS:
            case e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE: {
                // TODO unknown
                // particles are distributed at a single point. grid wont help here
                p_options.m_data_structure_type = e_datastructure_type::LIST_BENJAMIN;
                break;
            }
            case e_input_type::GENERATOR_RANDOM:
            case e_input_type::FILE_CSV: {
                // here we need to scan the entire file to decide what to do
                // TODO unknown
                analyser         = new DatastructureAnalyser (p_options, p_border, p_algorithm, p_writer);
                InputBase* input = InputFactory::build (p_options, *analyser);
                input->initialize_datastructure ();
                p_options.m_data_structure_type = analyser->analyse ();
                break;
            }
        }
        DatastructureBase* result = DatastructureFactory::build (p_options, p_border, p_algorithm, p_writer);
        if (analyser) {
            // dont load an file again ...
            // if random is generated again, everything could be different
            analyser->transfer_particles_to (*result);
            delete analyser;
        } else {
            // the generator generates an distribution which will fit in certain criteria so no
            // transfer needed. instead particles can be generated directly into the final
            // datastructure
            InputBase* input = InputFactory::build (p_options, *result);
            input->initialize_datastructure ();
        }
        return result;
    }
};
#endif /* SRC_MAIN_AUTOTUNEING_AUTOTUNEING_HPP_ */
