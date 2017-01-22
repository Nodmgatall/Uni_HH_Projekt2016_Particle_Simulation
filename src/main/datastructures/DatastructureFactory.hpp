/*
 * DatastructureFactory.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */
#ifndef SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREFACTORY_HPP_
#define SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREFACTORY_HPP_
#include "DatastructureBase.hpp"
#include "DatastructureGrid.hpp"
#include "DatastructureList.hpp"
#include "DatastructureListBenjamin.hpp"
#include "DatastructureListGrid.hpp"
#include "algorithms/AlgorithmBase.hpp"
#include "borders/BorderBase.hpp"
#include "io/output/WriterBase.hpp"
#include "options/Options.hpp"
#include "tools/Debug.hpp"
class DatastructureFactory {
  public:
    /**
     * builds the datastructure based on the given options.
     * @param p_options the options which define which datastructure to return
     * @param p_border each datastructure needs this in the constructor
     * @param p_algorithm each datastructure needs this in the constructor
     * @param p_writer each datastructure needs this in the constructor
     * @return
     */
    static DatastructureBase* build (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_writer);
};
#endif /* SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREFACTORY_HPP_ */
