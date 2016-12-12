#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "options/OptionHandler.hpp"

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
    if (unlink ("logdata/latest")) {
        // don't care ... but return value is used
    }
    if (symlink ((std::string ("../") + log_folder).c_str (), "logdata/latest")) {
        m_error_stream << "symlink @ 'logdata/latest' failed" << std::endl;
        exit (1);
    }
}
int main (int argc, char** argv) {
    createOutputDirectory ();
    s_options options;

    OptionHandler option_handler;
    if (int return_value = option_handler.handle_options (argc, argv, options))
        return return_value;

    ParticleSimulator particle_simulator (options);

    Benchmark::begin ("everything", false);
    particle_simulator.simulate ();
    Benchmark::end ();
}
