/*
 * main.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "algorithms/AlgorithmFactory.hpp"
#include "borders/BorderWrapparound.hpp"
#include "datastructures/DatastructureFactory.hpp"
#include "io/input/InputFactory.hpp"
#include "options/OptionHandler.hpp"
#include "options/OptionHandler.hpp"
#include <Statistics.hpp>
#include <autotuning/Autotuning.hpp>
#include <io/output/OutputFactory.hpp>

int main (int argc, char** argv) {
    std::cout << std::fixed << std::setprecision (6) << std::setfill ('0') << std::boolalpha;
    s_options options;
#ifdef CALCULATE_STATISTICS
    g_statistics.m_options = &options; /*pointer*/
    data_type time_start;
    time_start = omp_get_wtime ();
#endif
    OptionHandler option_handler;
    try {
        if (int return_value = option_handler.handle_options (argc, argv, options))
            return return_value;
    } catch (...) {
        return (1);
    }
    m_verbose_stream << "a" << std::endl;
    OutputBase* output = OutputFactory::build (options);
    m_verbose_stream << "b" << std::endl;
    BorderBase* border = new BorderWrapparound (options.m_bounds);
    m_verbose_stream << "c" << std::endl;
    AlgorithmBase* algorithm = AlgorithmFactory::build (options);
    m_verbose_stream << "d" << std::endl;
    DatastructureBase* datastructure = 0;
    m_verbose_stream << "e" << std::endl;
    if (options.m_autotuning) {
        m_verbose_stream << "f" << std::endl;
        datastructure = Autotuning::get_best_datastructure (options, *border, *algorithm, *output);
    } else {
        datastructure    = DatastructureFactory::build (options, *border, *algorithm, *output);
        InputBase* input = InputFactory::build (options, *datastructure);
        input->initialize_datastructure ();
        delete input;
    }
    ParticleSimulator particle_simulator (options, output, border, algorithm, datastructure);
    Benchmark::begin ("everything", false);
    particle_simulator.simulate ();
    Benchmark::end ();
    output->finalize ();
#ifdef CALCULATE_STATISTICS
    m_verbose_stream << "calculate statistics" << std::endl;
    g_statistics.m_total_runtime = omp_get_wtime () - time_start;
    m_standard_stream << "print statistics" << std::endl;
    m_standard_stream << g_statistics;
#endif
    m_verbose_stream << "delete writer;" << std::endl;
    delete output;
    m_verbose_stream << "delete border;" << std::endl;
    delete border;
    m_verbose_stream << "delete algorithm;" << std::endl;
    delete algorithm;
    m_verbose_stream << "delete datastructure;" << std::endl;
    delete datastructure;
}
