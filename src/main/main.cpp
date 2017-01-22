#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "algorithms/AlgorithmFactory.hpp"
#include "autotuneing/Autotuneing.hpp"
#include "borders/BorderWrapparound.hpp"
#include "datastructures/DatastructureFactory.hpp"
#include "io/input/InputFactory.hpp"
#include "io/output/file/FileWriterCSV.hpp"
#include "options/OptionHandler.hpp"
#include "options/OptionHandler.hpp"

int main (int argc, char** argv) {
    std::cout << std::fixed << std::setprecision (6) << std::setfill ('0');
    s_options     options;
    OptionHandler option_handler;
    if (int return_value = option_handler.handle_options (argc, argv, options))
        return return_value;
    if (mkdir (options.m_out_file_name.c_str (), 0700)) {
        // don't care ... but return value is used
    }
    WriterBase*        writer        = new FileWriterCSV (options, options.m_out_file_name + "/data");
    BorderBase*        border        = new BorderWrapparound (options.m_bounds);
    AlgorithmBase*     algorithm     = AlgorithmFactory::build (options);
    DatastructureBase* datastructure = 0;
    if (options.m_autotuneing) {
        datastructure = Autotuneing::get_best_datastructure (options, *border, *algorithm, *writer);
    } else {
        datastructure    = DatastructureFactory::build (options, *border, *algorithm, *writer);
        InputBase* input = InputFactory::build (options, *datastructure);
        input->initialize_datastructure ();
        delete input;
    }
    ParticleSimulator particle_simulator (options, datastructure);
    Benchmark::begin ("everything", false);
    particle_simulator.simulate ();
    Benchmark::end ();
    writer->finalize ();
    delete writer;
    delete border;
    delete algorithm;
    delete datastructure;
}
