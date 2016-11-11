#define EXTERN
#define MAIN_CPP
#include "Definitions.hpp"
#include "IO/OptionHandler.hpp"
#include "ParticleSimulator.hpp"

void print_header () {
    DEBUG_BEGIN << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
    DEBUG_BEGIN << "                  Particle Simulation                  " << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
    DEBUG_BEGIN << "            Benjamin Wanke, Oliver Heidmann            " << DEBUG_ENDL;
    DEBUG_BEGIN << "                      Supervisior                      " << DEBUG_END;
    DEBUG_BEGIN << "                    Philipp Neumann                    " << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
    DEBUG_BEGIN << "=======================================================" << DEBUG_END;
}
void createOutputDirectory () {
    time_t     current_time;
    struct tm *time_info;
    time (&current_time);
    time_info = localtime (&current_time);
    strftime (log_folder, sizeof (log_folder), "logdata/%Y-%m-%d_%H-%M-%S", time_info);
    mkdir ("logdata", 0700);
    mkdir (log_folder, 0700);
    g_debug_stream.open (std::string (log_folder) + "/log.txt", std::fstream::out);
    unlink ("logdata/latest");
    symlink ((std::string ("../") + log_folder).c_str (), "logdata/latest");
}
int main (int argc, char **argv) {
    createOutputDirectory ();
    print_header ();
    s_generator_options                generator_options;
    s_simulator_options                simulator_options;
    
    std::unique_ptr<OptionHandler> option_handler (new OptionHandler ());
    option_handler->handle_options (argc, argv, &simulator_options, &generator_options);
    
    std::unique_ptr<ParticleSimulator> particle_simulator (
        new ParticleSimulator (&simulator_options, &generator_options));
    
    Benchmark::begin ("everything", false);
    particle_simulator->init_particle_data ();
    particle_simulator->find_simulation_algorithm ();
    particle_simulator->simulate ();
    Benchmark::end ();
}
