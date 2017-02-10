/*
 * DatastructureFactory.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */
#include "DatastructureFactory.hpp"
DatastructureBase* DatastructureFactory::build (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_writer) {
    switch (p_options.m_data_structure_type) {
        case e_datastructure_type::LINKED_CELLS:
            return new DatastructureLinkedCells (p_options, p_border, p_algorithm, p_writer);
        case e_datastructure_type::NEIGHBOR_LIST:
            return new DatastructureNeighborList (p_options, p_border, p_algorithm, p_writer);
        case e_datastructure_type::LINKED_CELLS_NEIGHBOR_LIST:
            return new DatastructureLinkedCellsNeighborList (p_options, p_border, p_algorithm, p_writer);
        default:
            throw DatastructureTypeInvalidException (p_options.m_data_structure_type);
    }
}
