/*
 * AlgorithmFactory.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
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
