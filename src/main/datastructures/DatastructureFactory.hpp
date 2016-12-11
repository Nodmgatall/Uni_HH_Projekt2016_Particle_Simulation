/*
 * DatastructureFactory.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#ifndef SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREFACTORY_HPP_
#define SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREFACTORY_HPP_

#include "../algorithms/AlgorithmBase.hpp"
#include "../borders/BorderBase.hpp"
#include "../io/output/WriterBase.hpp"
#include "../options/Options.hpp"
#include "../tools/Debug.hpp"
#include "DatastructureBase.hpp"
#include "DatastructureGrid.hpp"
#include "DatastructureList.hpp"

class DatastructureFactory {
  public:
    static DatastructureBase*
        build (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_writer);
};

#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREFACTORY_HPP_ */
