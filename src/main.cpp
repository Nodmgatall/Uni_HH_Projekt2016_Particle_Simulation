#define EXTERN
#define MAIN_CPP
#include "Definitions.hpp"
#include "IO/OptionHandler.hpp"
#include "ParticleSimulator.hpp"

int main (int argc, char **argv) {
    s_generator_options                generator_options;
    s_simulator_options                simulator_options;
    std::unique_ptr<ParticleSimulator> particle_simulator (
        new ParticleSimulator (&simulator_options, &generator_options));
    std::unique_ptr<OptionHandler> option_handler (new OptionHandler ());
    option_handler->handle_options (argc, argv, &simulator_options, &generator_options);
    particle_simulator->init_particle_data ();
    particle_simulator->find_simulation_algorithm ();
    particle_simulator->simulate ();
}
