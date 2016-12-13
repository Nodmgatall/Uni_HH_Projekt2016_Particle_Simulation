#ifndef OPTION_HANDLER_HPP
#define OPTION_HANDLER_HPP

#include "Definitions.hpp"
#include "Options.hpp"
#include <cstring>
#include <getopt.h>

class OptionHandler {
  protected:
    int indexInArray (std::vector<const char*> elements, char* element);
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
    void print_usage_max_iterations_between_datastructure_rebuild ();
    void print_usage_particle_sim ();
    void print_header ();
    void print_usage_print_config ();

  public:
    /**
     * takes the arguments passed to application and parses them into the option struct
     * @param p_argc given at program startup
     * @param p_argv given at program startup
     * @param p_options the struct into which the parameters are written
     * @return if != 0 the program should terminate right after the function returns
     */
    int handle_options (int p_argc, char** p_argv, s_options& p_options);
    /**
     * pints the options specified by the struct to logfile
     * @param p_options
     */
    void print_choosen_options (s_options& p_options);
};

#endif
