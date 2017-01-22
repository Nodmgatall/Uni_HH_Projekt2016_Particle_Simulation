#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "options/OptionHandler.hpp"
#include <unistd.h>

#include "options/OptionHandler.hpp"

#include "borders/BorderWrapparound.hpp"
#include "io/output/file/FileWriterCSV.hpp"

#include "algorithms/AlgorithmFactory.hpp"
#include "autotuneing/Autotuneing.hpp"
#include "datastructures/DatastructureFactory.hpp"
#include "io/input/InputFactory.hpp"

std::string output_folder_name;

void createOutputDirectory () {
    time_t     current_time;
    struct tm* time_info;
    time (&current_time);
    time_info = localtime (&current_time);
    strftime (log_folder, sizeof (log_folder), "logdata/%Y-%m-%d_%H-%M-%S", time_info);
    if (mkdir ("logdata", 0700)) {
        // don't care ... but return value is used
    }
    if (mkdir (log_folder, 0700)) {
        // don't care ... but return value is used
    }
    g_log_file.open (std::string (log_folder) + "/log.txt", std::fstream::out);
    g_log_file << std::fixed << std::setprecision (6) << std::setfill ('0');
    if (unlink ("logdata/latest")) {
        // don't care ... but return value is used
    }
    output_folder_name = (std::string ("./") + log_folder);
    if (symlink (output_folder_name.c_str (), "logdata/latest")) {
        m_error_stream << "symlink @ 'logdata/latest' failed" << std::endl;
        exit (1);
    }
}
int main (int argc, char** argv) {
    createOutputDirectory ();
    s_options     options;
    OptionHandler option_handler;
    if (int return_value = option_handler.handle_options (argc, argv, options))
        return return_value;

    WriterBase*    writer    = new FileWriterCSV (options, std::string (log_folder) + "/data");
    BorderBase*    border    = new BorderWrapparound (options.m_bounds);
    AlgorithmBase* algorithm = AlgorithmFactory::build (options);

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

    if (options.m_out_file_name.length () > 0) {
        if (rename (output_folder_name.c_str (), options.m_out_file_name.c_str ())) {
            m_error_stream << "moving to " << options.m_out_file_name << " failed" << std::endl;
        } else {
            if (unlink ("logdata/latest")) {
                // don't care ... but return value is used
            }
            std::string path_prefix ("");
            if (options.m_out_file_name.c_str ()[0] == '.') {
                // relative path to absolute path
                char cCurrentPath[FILENAME_MAX];
                if (getcwd (cCurrentPath, sizeof (cCurrentPath))) {
                    path_prefix = std::string (cCurrentPath) + "/";
                } else {
                    // unable to get current directory
                }
            }
            if (symlink ((path_prefix + options.m_out_file_name.c_str ()).c_str (),
                         "logdata/latest")) {
                m_error_stream << "symlink @ 'logdata/latest' failed" << std::endl;
                exit (1);
            }
        }
    }
}
