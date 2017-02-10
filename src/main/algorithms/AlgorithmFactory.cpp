/*
 * AlgorithmFactory.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "AlgorithmFactory.hpp"
AlgorithmBase* AlgorithmFactory::build (s_options& p_options) {
    switch (p_options.m_algorithm_type) {
        case e_algorithm_type::LENNARD_JONES:
            return new AlgorithmStoermerVerletLennardJones (p_options);
        default:
            throw AlgorithmTypeInvalidException (p_options.m_algorithm_type);
    }
}
