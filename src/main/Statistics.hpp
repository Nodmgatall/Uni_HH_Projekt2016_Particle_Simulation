/*
 * Statistics.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
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
     * total runtime in seconds*10⁻6
     */
    unsigned long long m_total_runtime;
    /**
     * total runtime used for calculateing the interactions in seconds*10⁻6
     */
    unsigned long long m_total_runtime_calculation;
    /**
     * total runtime used for rebuilding the datastructure in seconds*10⁻6
     */
    unsigned long long m_total_runtime_rebuild;
    /**
     * the number of cells used in the grid datastructure
     */
    unsigned long m_cell_count;
    /**
     * the options given by the program parameters
     */
    s_options* m_options;
    Statistics () : m_total_datastructure_rebuild_count (0), m_total_runtime (0), m_total_runtime_calculation (0), m_total_runtime_rebuild (0), m_cell_count (-1), m_options (0) {
    }

    friend std::ostream& operator<< (std::ostream& stream, const Statistics p_statistics) {
        stream << *p_statistics.m_options;
        stream << "statistics.total_runtime                                     : " << (p_statistics.m_total_runtime / 1.e6) << std::endl;
        stream << "statistics.m_total_runtime_calculation                       : " << (p_statistics.m_total_runtime_calculation / 1.e6) << std::endl;
        stream << "statistics.m_total_runtime_rebuild                           : " << (p_statistics.m_total_runtime_rebuild / 1.e6) << std::endl;
        stream << "statistics.total_datastructure_rebuild_count                 : " << p_statistics.m_total_datastructure_rebuild_count << std::endl;
        stream << "statistics.average_time_per_iteration                        : " << (p_statistics.m_total_runtime / p_statistics.m_options->m_max_iterations) << std::endl;
        stream << "statistics.average_iterations_between_rebuild                : " << (p_statistics.m_total_datastructure_rebuild_count / p_statistics.m_options->m_max_iterations)
               << std::endl;
        data_type volumen = p_statistics.m_options->m_bounds.x * p_statistics.m_options->m_bounds.y * p_statistics.m_options->m_bounds.z;
        stream << "statistics.volumen                                           : " << volumen << std::endl;
        stream << "statistics.partikeldichte                                    : " << (p_statistics.m_options->m_particle_count / volumen) << std::endl;
        stream << "statistics.m_cell_count                                      : " << p_statistics.m_cell_count << std::endl;
        stream << "statistics.particles_per_cell                                : " << (p_statistics.m_options->m_particle_count / p_statistics.m_cell_count) << std::endl;
        return stream;
    }
};
extern Statistics g_statistics;
#endif

#endif /* SRC_MAIN_STATISTICS_HPP_ */
