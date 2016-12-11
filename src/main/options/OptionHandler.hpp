#ifndef OPTION_HANDLER_HPP
#define OPTION_HANDLER_HPP

#include "Definitions.hpp"
#include "Options.hpp"
#include "io/config/ConfigLoader.hpp"
#include <getopt.h>

class OptionHandler {
  public:
    void handle_options (int p_argc, char** p_argv, s_options& p_options);

  private:
    void print_choosen_options (s_options& p_options);
    void print_usage_particle_sim ();
};

#endif
