#include "OptionHandler.hpp"

OptionHandler::OptionHandler () {
}

int OptionHandler::indexInArray (std::vector<const char*> elements, char* element) {
    unsigned int index;
    for (index = 0; index < elements.size (); index++)
        if (0 == strcmp (elements[index], element)) {
            return index;
        }
    return -1;
}

int OptionHandler::handle_options (int p_argc, char** p_argv, s_options& p_options) {
    print_header ();
    int                 argv_index;
    bool                help_defined             = false;
    bool                help_printed             = false;
    bool                save_config              = false;
    bool                load_config              = false;
    bool                list_configs             = false;
    bool                config_feature_used      = false;
    bool                print_config             = true;
    bool                print_saved_config       = false;
    std::string         config_name              = "";
    float               run_time_limit           = -1;
    int                 long_options             = 0;
    int                 index                    = 0;
    const int           algorithm_type_index     = 1;
    const int           datastructure_type_index = 2;
    const int           input_type_index         = 3;
    const int           output_type_index        = 4;
    const int           write_modes_index        = 5;
    std::vector<option> options = { { "algorithm", required_argument, 0, algorithm_type_index * 1000 },
                                    { "data_structure", required_argument, 0, datastructure_type_index * 1000 },
                                    { "input", required_argument, 0, input_type_index * 1000 },
                                    { "output", required_argument, 0, output_type_index * 1000 },
                                    // simulation options
                                    { "autotuneing", no_argument, 0, 'a' },
                                    { "bounds", required_argument, 0, 'b' },
                                    { "count", required_argument, 0, 'c' },
                                    { "write_fequency", required_argument, 0, 'f' },
                                    { "help", no_argument, 0, 'h' },
                                    { "in_file_name", required_argument, 0, 'i' },
                                    { "run_time_limit", required_argument, 0, 'l' },
                                    { "max_iterations", required_argument, 0, 'm' },
                                    { "out_file_name", required_argument, 0, 'o' },
                                    { "cut_off_radius", required_argument, 0, 'r' },
                                    { "seed", required_argument, 0, 's' },
                                    { "timestep", required_argument, 0, 't' },
                                    { "verbose", no_argument, 0, 'v' },
                                    { "max_iterations_between_datastructure_rebuild", required_argument, 0, 6000 },
                                    // Misc
                                    { "load_config", required_argument, 0, 28 },
                                    { "print_config", required_argument, 0, 29 },
                                    { "list_configs", no_argument, 0, 30 },
                                    { "save_config", required_argument, 0, 31 } };
    for (index = 1; index < (signed) g_csv_column_names.size (); index++) {
        options.push_back ({ (std::string ("WRITE_") + g_csv_column_names[index]).c_str (),
                             required_argument,
                             0,
                             write_modes_index * 1000 + index });
    }
    opterr = 0;
    while ((argv_index = getopt_long (p_argc, p_argv, "ab::c::f::hi::l::m::o::r::s::t::v", &options[0], &long_options)) !=
           -1) {
        switch (argv_index / 1000) {
            case algorithm_type_index:
                if (help_defined) {
                    print_usage_algorithm ();
                    help_printed = true;
                } else {
                    p_options.m_algorithm_type =
                        static_cast<e_algorithm_type> (indexInArray (g_algorithm_names, optarg));
                }
                break;
            case datastructure_type_index:
                if (help_defined) {
                    print_usage_data_structure ();
                    help_printed = true;
                } else {
                    p_options.m_data_structure =
                        static_cast<e_datastructure_type> (indexInArray (g_datastructure_names, optarg));
                }
                break;
            case input_type_index:
                if (help_defined) {
                    print_usage_input ();
                    help_printed = true;
                } else {
                    p_options.m_input_type = static_cast<e_input_type> (indexInArray (g_input_names, optarg));
                }
                break;
            case output_type_index:
                if (help_defined) {
                    print_usage_output ();
                    help_printed = true;
                } else {
                    p_options.m_output_type =
                        static_cast<e_output_type> (indexInArray (g_output_names, optarg));
                }
                break;
            case write_modes_index:
                if (help_defined) {
                    print_usage_write_modes ();
                    help_printed = true;
                } else {
                    p_options.m_write_modes[static_cast<e_csv_column_type> (argv_index % 1000)] =
                        !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
                }
                break;
            default: {
                std::stringstream line;
                if (optarg) {
                    line.str (optarg);
                }
                switch (argv_index) {
                    case 'a': {
                        if (help_defined) {
                            print_usage_autotuneing ();
                            help_printed = true;
                        } else {
                            p_options.m_autotuneing = true;
                        }
                        break;
                    }
                    case 'b': {
                        if (help_defined) {
                            print_usage_bounds ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_bounds;
                        }
                        break;
                    }
                    case 'c': {
                        if (help_defined) {
                            print_usage_particle_count ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_particle_count;
                        }
                        break;
                    }
                    case 'f': {
                        if (help_defined) {
                            print_usage_write_fequency ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_write_fequency;
                        }
                        break;
                    }
                    case 'h': {
                        help_defined = true;
                        break;
                    }
                    case 'i': {
                        if (help_defined) {
                            print_usage_in_file_name ();
                            help_printed = true;
                        } else {
                            p_options.m_in_file_name = line.str ();
                        }
                        break;
                    }
                    case 'l': {
                        if (help_defined) {
                            print_usage_run_time_limit ();
                            help_printed = true;
                        } else {
                            line >> run_time_limit;
                        }
                        break;
                    }
                    case 'm': {
                        if (help_defined) {
                            print_usage_max_iterations ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_max_iterations;
                        }
                        break;
                    }
                    case 'o': {
                        if (help_defined) {
                            print_usage_out_file_name ();
                            help_printed = true;
                        } else {
                            p_options.m_out_file_name = line.str ();
                        }
                        break;
                    }
                    case 'r':
                        if (help_defined) {
                            print_usage_cut_off_radius ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_cut_off_radius;
                        }
                        break;
                    case 's': {
                        if (help_defined) {
                            print_usage_seed ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_seed;
                        }
                        break;
                    }
                    case 't': {
                        if (help_defined) {
                            print_usage_timestep ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_timestep;
                        }
                        break;
                    }
                    case 'v': {
                        if (help_defined) {
                            print_usage_verbose ();
                            help_printed = true;
                        } else {
                            p_options.m_verbose = true;
                        }
                        break;
                    }
                    case 6000: {
                        if (help_defined) {
                            print_usage_max_iterations_between_datastructure_rebuild ();
                            help_printed = true;
                        } else {
                            line >> p_options.m_max_iterations_between_datastructure_rebuild;
                        }
                        break;
                    }
                    case 28:
                        config_feature_used = true;
                        load_config         = true;
                        config_name         = std::string (optarg);
                        break;
                    case 29:
                        config_feature_used = true;
                        print_saved_config  = true;
                        config_name         = std::string (optarg);
                        break;
                    case 30:
                        config_feature_used = true;
                        list_configs        = true;
                        break;
                    case 31:
                        config_feature_used = true;
                        save_config         = true;
                        config_name         = std::string (optarg);
                        break;
                    case '?': {
                        m_standard_stream << "Error: unknown option" << std::endl;
                        help_defined = true;
                        break;
                    }
                }
            }
        }
    }
    if (help_defined) {
        if (!help_printed) {
            print_usage_particle_sim ();
        }
        return 1;
    }
    if (run_time_limit > -1) {
        p_options.m_max_iterations = run_time_limit / p_options.m_timestep;
    }
    if (config_feature_used == true) {
        ConfigLoader config_loader;
        if (list_configs == true) {
            config_loader.list_configs ();
            exit (EXIT_SUCCESS);
        }
        if (save_config == true) {
            config_loader.save_config (config_name, p_options);
        }
        if (load_config == true) {
            config_loader.load_config (config_name, p_options);
        }
        if (print_saved_config == true) {
            config_loader.load_config (config_name, p_options);
        }
    }
    if (print_config) {
        print_choosen_options (p_options);
        if (print_saved_config == true) {
            exit (EXIT_SUCCESS);
        }
    }
    g_verbose = p_options.m_verbose;

    return 0;
}
void OptionHandler::print_choosen_options (s_options& p_options) {
    Benchmark::begin ("Print-Options");
    int               index;
    std::stringstream ss;
    ss << "write_modes    : [ID";
    for (index = 2; index < (signed) g_csv_column_names.size (); index++) {
        if (p_options.m_write_modes[static_cast<e_csv_column_type> (index)]) {
            ss << ", " << g_csv_column_names[index];
        }
    }
    ss << "]" << std::endl;
    m_standard_stream
        << "algorithm_type                               " << p_options.m_algorithm_type << std::endl
        << "autotuneing                                  " << p_options.m_autotuneing << std::endl
        << "output_type                                  " << p_options.m_output_type << std::endl
        << "in_file_name                                 " << p_options.m_in_file_name << std::endl
        << "out_file_name                                " << p_options.m_out_file_name << std::endl
        << "timestep                                     " << p_options.m_timestep << std::endl
        << "verbose                                      " << p_options.m_verbose << std::endl
        << "write_fequency                               " << p_options.m_write_fequency << std::endl
        << "cut_off_radius                               " << p_options.m_cut_off_radius << std::endl
        << "data_structure                               " << p_options.m_data_structure << std::endl
        << "input_type                                   " << p_options.m_input_type << std::endl
        << "seed                                         " << p_options.m_seed << std::endl
        << "count                                        " << p_options.m_particle_count << std::endl
        << "max_iterations                               " << p_options.m_max_iterations << std::endl
        << "bounds                                       " << p_options.m_bounds << std::endl
        << "max_iterations_between_datastructure_rebuild "
        << p_options.m_max_iterations_between_datastructure_rebuild << std::endl
        << ss.str () << std::endl;
    Benchmark::end ();
}
void OptionHandler::print_header () {
    m_standard_stream //
        << std::endl
        << "+==============================================================================+" << std::endl
        << "|                             Particle Simulation                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                       Benjamin Warnke, Oliver Heidmann                       |" << std::endl
        << "|                                  Supervisor                                  |" << std::endl
        << "|                               Philipp Neumann                                |" << std::endl
        << "+==============================================================================+" << std::endl;
}
void OptionHandler::print_usage_algorithm () {
    int index;
    m_standard_stream //
        << "| --algorithm=         " << g_algorithm_names[1]
        << std::string (56 - strlen (g_algorithm_names[1]), ' ') << "|" << std::endl;
    for (index = 2; index < (signed) g_algorithm_names.size (); index++) {
        m_standard_stream //
            << "|                      " << g_algorithm_names[index]
            << std::string (56 - strlen (g_algorithm_names[index]), ' ') << "|" << std::endl;
    }
    m_standard_stream //
        << "|                          This option specifies the method to calculate the   |" << std::endl
        << "|                          forces between the particles. Based on the forces   |" << std::endl
        << "|                          the movement is calculated.                         |" << std::endl;
}
void OptionHandler::print_usage_data_structure () {
    int index;
    m_standard_stream //
        << "| --data_structure=    " << g_datastructure_names[1]
        << std::string (56 - strlen (g_datastructure_names[1]), ' ') << "|" << std::endl;
    for (index = 2; index < (signed) g_datastructure_names.size (); index++) {
        m_standard_stream //
            << "|                      " << g_datastructure_names[index]
            << std::string (56 - strlen (g_datastructure_names[index]), ' ') << "|" << std::endl;
    }
    m_standard_stream //
        << "|                          This option specifies the datastructure which       |" << std::endl
        << "|                          stores the particles. The different datastructures  |" << std::endl
        << "|                          have different advantages based on the              |" << std::endl
        << "|                          particle-placement. This option must not be used    |" << std::endl
        << "|                          together with 'autotuneing'.                        |" << std::endl;
}
void OptionHandler::print_usage_input () {
    int index;
    m_standard_stream //
        << "| --input=             " << g_input_names[1]
        << std::string (56 - strlen (g_input_names[1]), ' ') << "|" << std::endl;
    for (index = 2; index < (signed) g_input_names.size (); index++) {
        m_standard_stream //
            << "|                      " << g_input_names[index]
            << std::string (56 - strlen (g_input_names[index]), ' ') << "|" << std::endl;
    }
    m_standard_stream //
        << "|                          This option specifies how the particles are loaded  |" << std::endl
        << "|                          into the simulation.                                |" << std::endl
        << "|                          If the name contains 'GENERATOR' then the particles |" << std::endl
        << "|                          are generated at runtime based on 'count', 'bounds' |" << std::endl
        << "|                          and 'seed'.                                         |" << std::endl
        << "|                          If the name contains 'FILE' then the particles are  |" << std::endl
        << "|                          loaded from a file with the specified type from the |" << std::endl
        << "|                          file specified by 'in_file_name'.                   |" << std::endl;
}
void OptionHandler::print_usage_output () {
    int index;
    m_standard_stream //
        << "| --output=            " << g_output_names[1]
        << std::string (56 - strlen (g_output_names[1]), ' ') << "|" << std::endl;
    for (index = 2; index < (signed) g_output_names.size (); index++) {
        m_standard_stream //
            << "|                      " << g_output_names[index]
            << std::string (56 - strlen (g_output_names[index]), ' ') << "|" << std::endl;
    }
    m_standard_stream //

        << "|                          This option specifies how the particles are saved   |" << std::endl
        << "|                          from the simulation. Particles are saved before the |" << std::endl
        << "|                          first iteration, and then every 'write_fequency'    |" << std::endl
        << "|                          iterations.                                         |" << std::endl;
}
void OptionHandler::print_usage_write_modes () {
    int index;
    for (index = 1; index < (signed) g_csv_column_names.size (); index++) {
        m_standard_stream //
            << "| --WRITE_" << g_csv_column_names[index]
            << std::string (69 - strlen (g_csv_column_names[index]), ' ') << "|" << std::endl;
    }
    m_standard_stream //
        << "|                          If 'output' is set to 'FILE_CSV' then this options  |" << std::endl
        << "|                          defines which data from the individual particles    |" << std::endl
        << "|                          should be stored on disk. If 'output' is set to     |" << std::endl
        << "|                          something else, than this option must not be used.  |" << std::endl;
}
void OptionHandler::print_usage_autotuneing () {
    m_standard_stream //
        << "| --autotuneing                                                                |" << std::endl
        << "|  -a                      If 'autotuneing' is enabled, then the program will  |" << std::endl
        << "|                          choose the best datastructure based on the given    |" << std::endl
        << "|                          particles. This option must not be used together    |" << std::endl
        << "|                          with the 'datastructure' option.                    |" << std::endl;
}
void OptionHandler::print_usage_bounds () {
    m_standard_stream //
        << "| --bounds=(float/float/float)                                                 |" << std::endl
        << "|  -b                      This option specifies in which space the particles  |" << std::endl
        << "|                          can move. If particles move outside of the given    |" << std::endl
        << "|                          bounds, than the datastructure may move them back   |" << std::endl
        << "|                          into the bounds.                                    |" << std::endl;
}
void OptionHandler::print_usage_write_fequency () {
    m_standard_stream //
        << "| --write_fequency=(integer)                                                   |" << std::endl
        << "|  -f                      This option specifies the count of iterations until |" << std::endl
        << "|                          the particles are saved to the next file. Larger    |" << std::endl
        << "|                          numbers result in a better performance, but the     |" << std::endl
        << "|                          data between the saves is lost.                     |" << std::endl;
}
void OptionHandler::print_usage_help () {
    m_standard_stream //
        << "| --help                                                                       |" << std::endl
        << "|  -h                      prints help for all possible options.               |" << std::endl;
}
void OptionHandler::print_usage_in_file_name () {
    m_standard_stream //
        << "| --in_file_name=(string)                                                      |" << std::endl
        << "|  -i                      This option specifies the file name in which the    |" << std::endl
        << "|                          initial particles are stored. Must be used together |" << std::endl
        << "|                          an 'input' which is based on file.                  |" << std::endl;
}
void OptionHandler::print_usage_run_time_limit () {
    m_standard_stream //
        << "| --run_time_limit=(float)                                                     |" << std::endl
        << "|  -l                      Defines the time at which the simulation should     |" << std::endl
        << "|                          end. each simulation starts at time 0. Time         |" << std::endl
        << "|                          increases every iteration based on 'timestep'. Must |" << std::endl
        << "|                          not be used together with 'max_iterations'.         |" << std::endl;
}
void OptionHandler::print_usage_max_iterations () {
    m_standard_stream //
        << "| --max_iterations=(integer)                                                   |" << std::endl
        << "|  -m                      Defines the number of iterations which should be    |" << std::endl
        << "|                          simulated. Must not be used together with the       |" << std::endl
        << "|                          'run_time_limit' option.                            |" << std::endl;
}
void OptionHandler::print_usage_out_file_name () {
    m_standard_stream //
        << "| --out_file_name=(string)                                                     |" << std::endl
        << "|  -o                      The particles are stored in files starting with the |" << std::endl
        << "|                          path and name provided by 'out_file_name'. After    |" << std::endl
        << "|                          the file base is an increasing number which         |" << std::endl
        << "|                          specifies the file order. The file-ending is chosen |" << std::endl
        << "|                          automatically based on the 'output' option.         |" << std::endl;
}
void OptionHandler::print_usage_particle_count () {
    m_standard_stream //
        << "| --count=(integer)                                                            |" << std::endl
        << "|  -p                      Specifies the particle count for the simulation.    |" << std::endl
        << "|                          Must be used if the specified input is based on     |" << std::endl
        << "|                          'GENERATOR'.                                        |" << std::endl;
}
void OptionHandler::print_usage_cut_off_radius () {
    m_standard_stream //
        << "| --cut_off_radius=(float)                                                     |" << std::endl
        << "|  -r                      Defines the max radius at which particles should    |" << std::endl
        << "|                          interact with each other. If particles are more     |" << std::endl
        << "|                          than this defined distance from each other, then no |" << std::endl
        << "|                          interaction will be calculated.                     |" << std::endl;
}
void OptionHandler::print_usage_seed () {
    m_standard_stream //
        << "| --seed=(integer)                                                             |" << std::endl
        << "|  -s                      Specifies the seed used for generation. Must be     |" << std::endl
        << "|                          used if the specified input is based on 'GENERATOR'.|" << std::endl;
}
void OptionHandler::print_usage_timestep () {
    m_standard_stream //
        << "| --timestep=(float)                                                           |" << std::endl
        << "|  -t                      Specifies the time-delta calculated in each         |" << std::endl
        << "|                          iteration.                                          |" << std::endl;
}
void OptionHandler::print_usage_verbose () {
    m_standard_stream //
        << "| --verbose                                                                    |" << std::endl
        << "|  -v                      If set, the program prints more messages to         |" << std::endl
        << "|                          console.                                            |" << std::endl;
}
void OptionHandler::print_usage_max_iterations_between_datastructure_rebuild () {
    m_standard_stream //
        << "| --max_iterations_between_datastructure_rebuild                               |" << std::endl
        << "|                          Specifies the iteration count after which the       |" << std::endl
        << "|                          datastructure should reorder its internal           |" << std::endl
        << "|                          structure.                                          |" << std::endl;
}
void OptionHandler::print_usage_load_confing () {
    m_standard_stream //
        << "| --load_confing                                                               |" << std::endl;
}
void OptionHandler::print_usage_print_config () {
    m_standard_stream //
        << "| --print_config                                                               |" << std::endl;
}
void OptionHandler::print_usage_list_configs () {
    m_standard_stream //
        << "| --list_configs                                                               |" << std::endl;
}
void OptionHandler::print_usage_save_config () {
    m_standard_stream //
        << "| --save_config                                                                |" << std::endl;
}

void OptionHandler::print_usage_particle_sim () {
    m_standard_stream //
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                               general  options                               |" << std::endl
        << "|                                                                              |" << std::endl;
    print_usage_help ();
    print_usage_verbose ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                          options for  the algorithm                          |" << std::endl
        << "|                                                                              |" << std::endl;
    print_usage_algorithm ();
    print_usage_cut_off_radius ();
    print_usage_timestep ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                        options for  the datastructure                        |" << std::endl
        << "|                                                                              |" << std::endl;
    print_usage_data_structure ();
    print_usage_autotuneing ();
    print_usage_max_iterations_between_datastructure_rebuild ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                            options for  the input                            |" << std::endl
        << "|                                                                              |" << std::endl;
    print_usage_input ();
    print_usage_in_file_name ();
    print_usage_particle_count ();
    print_usage_seed ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                            options for the output                            |" << std::endl
        << "|                                                                              |" << std::endl;
    print_usage_output ();
    print_usage_out_file_name ();
    print_usage_write_fequency ();
    print_usage_write_modes ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                         options for  the termination                         |" << std::endl
        << "|                                                                              |" << std::endl;
    print_usage_run_time_limit ();
    print_usage_max_iterations ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                                other  options                                |" << std::endl
        << "|                                                                              |" << std::endl;
    print_usage_bounds ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl
        << "|                                                                              |" << std::endl
        << "|                                config options                                |" << std::endl
        << "|                                                                              |" << std::endl;
    //
    print_usage_load_confing ();
    print_usage_print_config ();
    print_usage_list_configs ();
    print_usage_save_config ();
    m_standard_stream //
        << "|                                                                              |" << std::endl
        << "+==============================================================================+" << std::endl;
}
