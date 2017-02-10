/*
 * Autotuning.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_AUTOTUNING_AUTOTUNING_HPP_
#define SRC_MAIN_AUTOTUNING_AUTOTUNING_HPP_
#include "datastructures/DatastructureFactory.hpp"
#include "io/input/InputBase.hpp"
#include "io/input/InputFactory.hpp"
#include "options/Options.hpp"
#include <autotuning/DatastructureAnalyser.hpp>
class Autotuning {
  public:
    /**
     * returns an fully initialized datastructure which should be the fastest for the given input
     */
    static inline DatastructureBase* get_best_datastructure (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, OutputBase& p_writer) {
        DatastructureAnalyser* analyser = 0;
        if ((p_options.m_input_type == e_input_type::GENERATOR_RANDOM) || (p_options.m_input_type == e_input_type::FILE_CSV)) {
            // TODO unknown
            analyser         = new DatastructureAnalyser (p_options, p_border, p_algorithm, p_writer);
            InputBase* input = InputFactory::build (p_options, *analyser);
            input->initialize_datastructure ();
            analyser->analyse ();
        }
        if (2.0 * p_options.m_initial_speed < (p_options.m_cut_off_radius * (p_options.m_cut_off_factor - 1.0) - 1.0)) {
            // slow particles do not need rebuild of datastructure and could use the advantages of mixed datastructure
            p_options.m_data_structure_type = e_datastructure_type::LINKED_CELLS_NEIGHBOR_LIST;
        } else {
            // particles moves too fast to just use the mixed datastructure.
            // other criteria could be more important, so the mixed datastructure may still be used here
            switch (p_options.m_input_type) {
                case e_input_type::GENERATOR_RANDOM_UNIFORM:
                case e_input_type::GENERATOR_GRID_DISTRIBUTION:
                case e_input_type::AUTOTUNING_REGULAR_DISTRIBUTION:
                    // the particles are regular distributed, and too fast for the mixed datastructure to be efficient
                    p_options.m_data_structure_type = e_datastructure_type::LINKED_CELLS;
                    break;
                case e_input_type::GENERATOR_MULTIPLE_OBJECTS:
                case e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE:
                case e_input_type::AUTOTUNING_IRREGULAR_DISTRIBUTION:
                    // distribution of particles is irregular
                    // lot of cells are unused, most interactions are within a few cells. list would improve the runtime
                    // simulation should be for short-distance-interactions. if nearly all particles are in range, this would be long-distance-interactions, which are not
                    // the target
                    p_options.m_data_structure_type = e_datastructure_type::LINKED_CELLS_NEIGHBOR_LIST;
                    break;
                case e_input_type::AUTOTUNING_ERROR:
                    // this happens if input is empty or *corrupt*
                    return 0;
                case e_input_type::GENERATOR_RANDOM:
                case e_input_type::FILE_CSV: {
                    // this NEVER happens
                    return 0;
                }
            }
        }
        DatastructureBase* result = DatastructureFactory::build (p_options, p_border, p_algorithm, p_writer);
        if (analyser) {
            // do not load an file again ...
            // if random is generated again, everything could be different
            analyser->transfer_particles_to (*result);
            delete analyser;
        } else {
            // the generator generates an distribution which will fit in certain criteria so no
            // transfer needed. instead particles can be generated directly into the final
            // datastructure
            InputBase* input = InputFactory::build (p_options, *result);
            input->initialize_datastructure ();
            delete input;
        }
        return result;
    }
};
#endif /* SRC_MAIN_AUTOTUNING_AUTOTUNING_HPP_ */
