#ifndef OPTION_HANDLER_HPP
#define OPTION_HANDLER_HPP

#include <map>
#include <vector>

#include "../Definitions.hpp"
#include "ConfigLoader.hpp"
#include "Options.hpp"
#include "Options.hpp"

class OptionHandler {
  public:
    void handle_options (int p_argc, char** p_argv, s_options& p_options);

  private:
    void print_choosen_options (s_options& p_options);
    void print_usage_particle_sim ();
    void print_usage_generation_mode ();
};

#endif
