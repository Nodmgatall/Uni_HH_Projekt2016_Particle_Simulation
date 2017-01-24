/*
 * Statistics.hpp
 *
 *  Created on: 24.01.2017
 *      Author: benjamin
 */

#ifndef SRC_MAIN_STATISTICS_HPP_
#define SRC_MAIN_STATISTICS_HPP_
#include "DataType.hpp"
#include "options/Options.hpp"
#include "tools/Debug.hpp"
/**
 * undef to disable calculation of statistics
 */
#define CALCULATE_STATISTICS

#ifdef CALCULATE_STATISTICS
struct Statistics {
    /**
     * datastructure-rebuild-count
     */
    unsigned int m_total_datastructure_rebuild_count;
    /**
     * total runtime in seconds
     */
    unsigned long m_total_runtime;
    Statistics () : m_total_datastructure_rebuild_count (0), m_total_runtime (0) {
    }
    void print_statistics (s_options p_options) {
        m_verbose_stream << "total_runtime" << m_total_runtime << std::endl;
        m_verbose_stream << "total_datastructure_rebuild_count" << m_total_datastructure_rebuild_count << std::endl;
        m_verbose_stream << "average_time_per_iteration" << (m_total_runtime / p_options.m_max_iterations) << std::endl;
        m_verbose_stream << "average_iterations_between_rebuild" << (m_total_datastructure_rebuild_count / p_options.m_max_iterations) << std::endl;
    }
};
extern Statistics g_statistics;
#endif

#endif /* SRC_MAIN_STATISTICS_HPP_ */
