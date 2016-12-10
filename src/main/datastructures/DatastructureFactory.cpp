/*
 * DatastructureFactory.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "DatastructureFactory.hpp"

DatastructureBase DatastructureFactory::build (s_options&          p_options,
                                               BorderBase&         p_border,
                                               AlgorithmBase&      p_algorithm,
                                               ParticleWriterBase& p_writer) {
    switch (p_options.m_data_structure) {
        case e_datastructure_type::GRID:
            return DatastructureGrid (p_options, p_border, p_algorithm, p_writer);
        case e_datastructure_type::LIST:
            return DatastructureList (p_options, p_border, p_algorithm, p_writer);
            break;
        default:
            throw DatastructureTypeInvalidException (p_options.m_data_structure);
    }
}
