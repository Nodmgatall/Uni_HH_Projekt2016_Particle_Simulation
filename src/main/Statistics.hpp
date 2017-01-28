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
    data_type  m_total_runtime;
    s_options* m_options;
    Statistics () : m_total_datastructure_rebuild_count (0), m_total_runtime (0), m_options (0) {
    }

    friend std::ostream& operator<< (std::ostream& stream, const Statistics p_statistics) {
        stream << *p_statistics.m_options;
        stream << "statistics.total_runtime                                     : " << p_statistics.m_total_runtime << std::endl;
        stream << "statistics.total_datastructure_rebuild_count                 : " << p_statistics.m_total_datastructure_rebuild_count << std::endl;
        stream << "statistics.average_time_per_iteration                        : " << (p_statistics.m_total_runtime / p_statistics.m_options->m_max_iterations) << std::endl;
        stream << "statistics.average_iterations_between_rebuild                : " << (p_statistics.m_total_datastructure_rebuild_count / p_statistics.m_options->m_max_iterations)
               << std::endl;
        return stream;
    }
};
extern Statistics g_statistics;
#endif

#endif /* SRC_MAIN_STATISTICS_HPP_ */