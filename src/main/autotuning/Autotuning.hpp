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
class Autotuning {
  public:
    /**
     * returns an fully initialized datastructure which should be the fastest for the given input
     */
    static inline DatastructureBase*
        get_best_datastructure (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, OutputBase& p_writer, DatastructureBase* datastructure_original = NULL) {
        m_standard_stream << "a" << std::endl;
        if (datastructure_original) {
            m_standard_stream << "b" << std::endl;
            datastructure_original->analyse ();
            m_standard_stream << "c" << std::endl;
            p_options.m_initial_speed       = datastructure_original->m_options.m_initial_speed;
            p_options.m_data_structure_type = datastructure_original->m_options.m_data_structure_type;
            m_standard_stream << "d" << std::endl;
        } else if ((p_options.m_input_type == e_input_type::GENERATOR_RANDOM) || (p_options.m_input_type == e_input_type::FILE_CSV)) {
            // TODO unknown
            datastructure_original = new DatastructureLinkedCells (p_options, p_border, p_algorithm, p_writer);
            InputBase* input       = InputFactory::build (p_options, *datastructure_original);
            input->initialize_datastructure ();
            datastructure_original->analyse ();
            p_options.m_initial_speed       = datastructure_original->m_options.m_initial_speed;
            p_options.m_data_structure_type = datastructure_original->m_options.m_data_structure_type;
        }
        m_standard_stream << "e" << std::endl;
        Vec3l              tmp                    = DatastructureLinkedCells::getSize (p_options);
        data_type          distance_until_rebuild = MAX (p_options.m_cut_off_radius * (p_options.m_cut_off_radius_extra_factor - 1.0), 0);
        unsigned long long particles_per_cell     = p_options.m_particle_count / (tmp.x * tmp.y * tmp.z);
        m_standard_stream << "f" << std::endl;
        m_standard_stream << "autotuneing-choosing (" << p_options.m_initial_speed * p_options.m_timestep * 2.0 << "<" << distance_until_rebuild << ")"
                          << " speed=" << p_options.m_initial_speed << std::endl;
        if (36 < particles_per_cell) {
            // if there are too much particles per cell, then the additional cost for list construction are more expensive than the actual calculation
            p_options.m_data_structure_type = e_datastructure_type::LINKED_CELLS;
        } else if (p_options.m_initial_speed * p_options.m_timestep * 2.0 < distance_until_rebuild) {
            /*  v * t < distance_until_rebuild
             *  v   = p_options.m_initial_speed
             *	t   = p_options.m_timestep
             *	2.0 = mixed form is better if there are at least 2 calculations per rebuild
             */
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
                    // simulation should be for short-distance-interactions. if nearly all particles are in range, this would be long-distance_until_rebuild-interactions, which are
                    // not
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
        m_standard_stream << "g" << std::endl;
        DatastructureBase* result = NULL;
        if (datastructure_original && (datastructure_original->get_structure_type () == p_options.m_data_structure_type)) {
            result = datastructure_original;
            m_standard_stream << "autotuneing-choosing-not-switching " << p_options.m_data_structure_type << std::endl;
        } else {
            m_standard_stream << p_options.m_data_structure_type << std::endl;
            result = DatastructureFactory::build (p_options, p_border, p_algorithm, p_writer);
            if (datastructure_original) {
                m_standard_stream << "h" << std::endl;
                m_standard_stream << result << std::endl;
                m_standard_stream << datastructure_original << std::endl;
                // do not load an file again ...
                // if random is generated again, everything could be different
                datastructure_original->transfer_particles_to (result);
                m_standard_stream << "i" << std::endl;
                delete datastructure_original;
                m_standard_stream << "j" << std::endl;
                m_standard_stream << "autotuneing-choosing-with-switching " << p_options.m_data_structure_type << std::endl;
            } else {
                // the generator generates an distribution which will fit in certain criteria so no
                // transfer needed. instead particles can be generated directly into the final
                // datastructure
                InputBase* input = InputFactory::build (p_options, *result);
                input->initialize_datastructure ();
                delete input;
                m_standard_stream << "autotuneing-choosing-initial " << p_options.m_data_structure_type << std::endl;
            }
        }
        m_standard_stream << "k" << std::endl;
        return result;
    }
};
#endif /* SRC_MAIN_AUTOTUNING_AUTOTUNING_HPP_ */
