#ifndef OPTION_HANDLER_HPP
#define OPTION_HANDLER_HPP

#include "Definitions.hpp"
#include "Options.hpp"
#include "io/config/ConfigLoader.hpp"
#include <getopt.h>

class OptionHandler {
  protected:
    void print_usage_algorithm ();
    void print_usage_data_structure ();
    void print_usage_input ();
    void print_usage_output ();
    void print_usage_write_modes ();
    void print_usage_autotuneing ();
    void print_usage_bounds ();
    void print_usage_write_fequency ();
    void print_usage_help ();
    void print_usage_in_file_name ();
    void print_usage_run_time_limit ();
    void print_usage_max_iterations ();
    void print_usage_out_file_name ();
    void print_usage_particle_count ();
    void print_usage_cut_off_radius ();
    void print_usage_seed ();
    void print_usage_timestep ();
    void print_usage_verbose ();
    void print_usage_load_confing ();
    void print_usage_print_config ();
    void print_usage_list_configs ();
    void print_usage_save_config ();
    //
    void print_choosen_options (s_options& p_options);
    void print_usage_particle_sim ();

  public:
    void handle_options (int p_argc, char** p_argv, s_options& p_options);
};

#endif
