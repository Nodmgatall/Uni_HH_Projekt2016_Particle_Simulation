#ifndef OPTION_HANDLER_HPP
#define OPTION_HANDLER_HPP

#include <map>
#include <vector>

#include "../Definitions.hpp"
#include "ConfigLoader.hpp"
#include "OptionsGenerator.hpp"
#include "OptionsSimulation.hpp"

class OptionHandler {
    public:
    void handle_options (int p_argc, char **p_argv, s_simulator_options *p_sim_options, s_generator_options *p_gen_options);

    private:
    void print_choosen_options (s_simulator_options *p_sim_options, s_generator_options *p_gen_options);
    void print_usage_particle_sim ();
    void print_usage_generation_mode ();
};

#endif
