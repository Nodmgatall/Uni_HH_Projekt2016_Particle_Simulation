#include "Definitions.hpp"
#include "ParticleSimulator.hpp"
#include "options/OptionHandler.hpp"

void print_header () {
    DEBUG_BEGIN << std::endl;
    DEBUG_BEGIN << "=======================================================" << std::endl;
    DEBUG_BEGIN << "                  Particle Simulation                  " << std::endl;
    DEBUG_BEGIN << "=======================================================" << std::endl;
    DEBUG_BEGIN << "            Benjamin Wanke, Oliver Heidmann            " << std::endl;
    DEBUG_BEGIN << "                      Supervisior                      " << std::endl;
    DEBUG_BEGIN << "                    Philipp Neumann                    " << std::endl;
    DEBUG_BEGIN << "=======================================================" << std::endl;
    DEBUG_BEGIN << "=======================================================" << std::endl;
}
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
    g_debug_stream.open (std::string (log_folder) + "/log.txt", std::fstream::out);
    if (unlink ("logdata/latest")) {
        // don't care ... but return value is used
    }
    if (symlink ((std::string ("../") + log_folder).c_str (), "logdata/latest")) {
        DEBUG_BEGIN << "symlink @ 'logdata/latest' failed" << std::endl;
        exit (1);
    }
}
int main (int argc, char** argv) {
    createOutputDirectory ();
    print_header ();
    s_options options;

    OptionHandler option_handler;
    option_handler.handle_options (argc, argv, options);

    ParticleSimulator particle_simulator (options);

    Benchmark::begin ("everything", false);
    particle_simulator.simulate ();
    Benchmark::end ();
}
