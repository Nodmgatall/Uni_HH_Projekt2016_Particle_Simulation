#include "OptionHandler.hpp"

int indexInArray (std::vector<const char*> elements, char* element) {
    unsigned int index;
    for (index = 0; index < elements.size (); index++)
        if (0 == strcmp (elements[index], element)) {
            return index;
        }
    return -1;
}

void OptionHandler::handle_options (int p_argc, char** p_argv, s_options& p_options) {
    Benchmark::begin ("OptionHandler");
    int                 argv_index;
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
    while ((argv_index = getopt_long (p_argc, p_argv, "vs:p:l:t:dr:f:i:h", &options[0], &long_options)) != -1) {
        if (optarg && (strcmp (optarg, "-h") == 0 || strcmp (optarg, "--help") == 0)) {
            // TODO:  Display help from option
            std::cout << "here should the help for the choosen operator be printed, "
                         "sadly this is "
                         "not implemented"
                      << std::endl;
            exit (EXIT_SUCCESS);
        }
        switch (argv_index / 1000) {
            case algorithm_type_index:
                p_options.m_algorithm_type =
                    static_cast<e_algorithm_type> (indexInArray (g_algorithm_names, optarg));
                break;
            case datastructure_type_index:
                p_options.m_data_structure =
                    static_cast<e_datastructure_type> (indexInArray (g_datastructure_names, optarg));
                break;
            case input_type_index:
                p_options.m_input_type = static_cast<e_input_type> (indexInArray (g_input_names, optarg));
                break;
            case output_type_index:
                p_options.m_output_type = static_cast<e_output_type> (indexInArray (g_output_names, optarg));
                break;
            case write_modes_index:
                p_options.m_write_modes[static_cast<e_csv_column_type> (argv_index % 1000)] =
                    !(isdigit (optarg[0]) && std::stoi (optarg) == 0);
                break;
            default: {
                std::stringstream line;
                if (optarg) {
                    line.str (optarg);
                }
                switch (argv_index) {
                    case 'a': {
                        p_options.m_autotuneing = true;
                        break;
                    }
                    case 'b': {
                        line >> p_options.m_bounds;
                        break;
                    }
                    case 'c': {
                        line >> p_options.m_particle_count;
                        break;
                    }
                    case 'f': {
                        line >> p_options.m_write_fequency;
                        break;
                    }
                    case 'h': {
                        print_usage_particle_sim ();
                        exit (EXIT_SUCCESS);
                        break;
                    }
                    case 'i': {
                        p_options.m_in_file_name = line.str ();
                        break;
                    }
                    case 'l': {
                        line >> run_time_limit;
                        break;
                    }
                    case 'm': {
                        line >> p_options.m_max_iterations;
                        break;
                    }
                    case 'o': {
                        p_options.m_out_file_name = line.str ();
                        break;
                    }
                    case 'r':
                        line >> p_options.m_cut_off_radius;
                        break;
                    case 's': {
                        line >> p_options.m_seed;
                        break;
                    }
                    case 't': {
                        line >> p_options.m_timestep;
                        break;
                    }
                    case 'v': {
                        p_options.m_verbose = true;
                        break;
                    }
                    case 6000: {
                        line >> p_options.m_max_iterations_between_datastructure_rebuild;
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
                        std::cout << "Error: unkown option" << std::endl;
                        print_usage_particle_sim ();
                        exit (EXIT_SUCCESS);
                        break;
                    }
                }
            }
        }
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
    Benchmark::end ();
    if (print_config) {
        print_choosen_options (p_options);
        if (print_saved_config == true) {
            exit (EXIT_SUCCESS);
        }
    }
}
void OptionHandler::print_choosen_options (s_options& p_options) {
    Benchmark::begin ("Print-Options");
    int index;
    DEBUG_BEGIN << "algorithm_type                               " << p_options.m_algorithm_type << DEBUG_END;
    DEBUG_BEGIN << "autotuneing                                  " << p_options.m_autotuneing << DEBUG_END;
    DEBUG_BEGIN << "output_type                                  " << p_options.m_output_type << DEBUG_END;
    DEBUG_BEGIN << "in_file_name                                 " << p_options.m_in_file_name << DEBUG_END;
    DEBUG_BEGIN << "out_file_name                                " << p_options.m_out_file_name << DEBUG_END;
    DEBUG_BEGIN << "timestep                                     " << p_options.m_timestep << DEBUG_END;
    DEBUG_BEGIN << "verbose                                      " << p_options.m_verbose << DEBUG_END;
    DEBUG_BEGIN << "write_fequency                               " << p_options.m_write_fequency << DEBUG_END;
    DEBUG_BEGIN << "cut_off_radius                               " << p_options.m_cut_off_radius << DEBUG_END;
    DEBUG_BEGIN << "data_structure                               " << p_options.m_data_structure << DEBUG_END;
    DEBUG_BEGIN << "input_type                                   " << p_options.m_input_type << DEBUG_END;
    DEBUG_BEGIN << "seed                                         " << p_options.m_seed << DEBUG_END;
    DEBUG_BEGIN << "count                                        " << p_options.m_particle_count << DEBUG_END;
    DEBUG_BEGIN << "max_iterations                               " << p_options.m_max_iterations << DEBUG_END;
    DEBUG_BEGIN << "bounds                                       " << p_options.m_bounds << DEBUG_END;
    DEBUG_BEGIN << "max_iterations_between_datastructure_rebuild "
                << p_options.m_max_iterations_between_datastructure_rebuild << DEBUG_END;
    DEBUG_BEGIN << "write_modes    : [ID";
    for (index = 2; index < (signed) g_csv_column_names.size (); index++) {
        if (p_options.m_write_modes[static_cast<e_csv_column_type> (index)]) {
            g_debug_stream << ", " << g_csv_column_names[index];
        }
    }
    g_debug_stream << "]" << DEBUG_END;
    Benchmark::end ();
}

void OptionHandler::print_usage_algorithm () {
    int index;
    std::cout << "  --algorithm=< " << g_algorithm_names[1];
    for (index = 2; index < (signed) g_algorithm_names.size (); index++) {
        std::cout << " | " << g_algorithm_names[index];
    }
    std::cout << " >" << std::endl;
    std::cout //
        << "                           This option specifies the method to calculate the    " << std::endl
        << "                           forces between the particles. Based on the forces the" << std::endl
        << "                           movement is calculated.                              " << std::endl;
}
void OptionHandler::print_usage_data_structure () {
    int index;
    std::cout << "  --data_structure=< " << g_datastructure_names[1];
    for (index = 2; index < (signed) g_datastructure_names.size (); index++) {
        std::cout << " | " << g_datastructure_names[index];
    }
    std::cout << " >" << std::endl;
    std::cout //
        << "                           This option specifies the datastructure which stores " << std::endl
        << "                           the particles. The different datastructures have     " << std::endl
        << "                           different advantages based on the particle-placement." << std::endl
        << "                           this option must not be used together with           " << std::endl
        << "                           'autotuneing'.                                       " << std::endl;
}
void OptionHandler::print_usage_input () {
    int index;
    std::cout << "  --input=< " << g_input_names[1];
    for (index = 2; index < (signed) g_input_names.size (); index++) {
        std::cout << " | " << g_input_names[index];
    }
    std::cout << " >" << std::endl;
    std::cout //
        << "                           This option specifies how the particles are loaded   " << std::endl
        << "                           into the simulation.                                 " << std::endl
        << "                           If the name contains 'GENERATOR' then the particles  " << std::endl
        << "                           are generated at runtime based on 'count', 'bounds'  " << std::endl
        << "                           and 'seed'.                                          " << std::endl
        << "                           If the name contains 'FILE' then the particles are   " << std::endl
        << "                           loaded from a file with the specified type from the  " << std::endl
        << "                           file specified by 'in_file_name'.                    " << std::endl;
}
void OptionHandler::print_usage_output () {
    int index;
    std::cout << "  --output=< " << g_output_names[1];
    for (index = 2; index < (signed) g_output_names.size (); index++) {
        std::cout << " | " << g_output_names[index];
    }
    std::cout //
        << " >" << std::endl
        << "                           This option specifies how the particles are saved    " << std::endl
        << "                           from the simulation. Particles are saved before the  " << std::endl
        << "                           first iteration, and then every 'write_fequency'     " << std::endl
        << "                           iterations.                                          " << std::endl;
}
void OptionHandler::print_usage_write_modes () {
    int index;
    for (index = 1; index < (signed) g_csv_column_names.size (); index++) {
        std::cout << "  --WRITE_" << g_csv_column_names[index];
    }
    std::cout //
        << std::endl
        << "                           If 'output' is set to 'FILE_CSV' then this options   " << std::endl
        << "                           defines which data from the individual particles     " << std::endl
        << "                           should be stored on disk. If 'output' is set to      " << std::endl
        << "                           something else, than this option must not be used.   " << std::endl;
}
void OptionHandler::print_usage_autotuneing () {
    std::cout //
        << "  --autotuneing                | -a" << std::endl
        << "                           If 'autotuneing' is enabled, then the program will   " << std::endl
        << "                           choose the best datastructure based on the given     " << std::endl
        << "                           particles. This option must not be used together with" << std::endl
        << "                           the 'datastructure' option.                          " << std::endl;
}
void OptionHandler::print_usage_bounds () {
    std::cout //
        << "  --bounds=(float/float/float) | -b" << std::endl
        << "                           This option specifies in which space the particles   " << std::endl
        << "                           can move. If particles move outside of the given     " << std::endl
        << "                           bounds, than the datastructure may move them back    " << std::endl
        << "                           into the bounds.                                     " << std::endl;
}
void OptionHandler::print_usage_write_fequency () {
    std::cout //
        << "  --write_fequency=(integer)   | -f" << std::endl
        << "                           This option specifies the count of iterations until  " << std::endl
        << "                           the particles are saved to the next file. Larger     " << std::endl
        << "                           numbers result in a better performance, but the data " << std::endl
        << "                           between the saves is lost.                           " << std::endl;
}
void OptionHandler::print_usage_help () {
    std::cout //
        << "  --help                       | -h" << std::endl
        << "                           prints help for all possible options.                " << std::endl;
}
void OptionHandler::print_usage_in_file_name () {
    std::cout //
        << "  --in_file_name=(string)      | -i" << std::endl
        << "                           This option specifies the file name in which the     " << std::endl
        << "                           initial particles are stored. Must be used together  " << std::endl
        << "                           an 'input' which is based on file.                   " << std::endl;
}
void OptionHandler::print_usage_run_time_limit () {
    std::cout //
        << "  --run_time_limit=(float)     | -l" << std::endl
        << "                           Defines the time at which the simulation should end. " << std::endl
        << "                           each simulation starts at time 0. Time increases     " << std::endl
        << "                           every iteration based on 'timestep'. Must not be used" << std::endl
        << "                           together with 'max_iterations'.                      " << std::endl;
}
void OptionHandler::print_usage_max_iterations () {
    std::cout //
        << "  --max_iterations=(integer)   | -m" << std::endl
        << "                           Defines the number of iterations which should be     " << std::endl
        << "                           simulated. Must not be used together with the        " << std::endl
        << "                           'run_time_limit' option.                             " << std::endl;
}
void OptionHandler::print_usage_out_file_name () {
    std::cout //
        << "  --out_file_name=(string)     | -i" << std::endl
        << "                           The particles are stored in files starting with the  " << std::endl
        << "                           path and name provided by 'out_file_name'. After the " << std::endl
        << "                           file base is an increasing number which specifies    " << std::endl
        << "                           the file order. The file-ending is chosen            " << std::endl
        << "                           automatically based on the 'output' option.          " << std::endl;
}
void OptionHandler::print_usage_particle_count () {
    std::cout //
        << "  --particle_count             | -p" << std::endl
        << "                           Specifies the particle count for the simulation. Must" << std::endl
        << "                           be used if the specified input is based on           " << std::endl
        << "                           'GENERATOR'.                                         " << std::endl;
}
void OptionHandler::print_usage_cut_off_radius () {
    std::cout //
        << "  --cut_off_radius             | -r" << std::endl
        << "                           Defines the max radius at which particles should     " << std::endl
        << "                           interact with each other. If particles are more than " << std::endl
        << "                           this defined distance from each other, then no       " << std::endl
        << "                           interaction will be calculated.                      " << std::endl;
}
void OptionHandler::print_usage_seed () {
    std::cout //
        << "  --seed                       | -s" << std::endl
        << "                           Specifies the seed used for generation. Must be used " << std::endl
        << "                           if the specified input is based on 'GENERATOR'.      " << std::endl;
}
void OptionHandler::print_usage_timestep () {
    std::cout //
        << "  --timestep                   | -t" << std::endl
        << "                           Specifies the deltatime calculated in each iteration." << std::endl;
}
void OptionHandler::print_usage_verbose () {
    std::cout //
        << "  --verbose                    | -v" << std::endl
        << "                           If set, the program prints more messages to console. " << std::endl;
}
void OptionHandler::print_usage_load_confing () {
    std::cout //
        << "  --load_confing               " << std::endl;
}
void OptionHandler::print_usage_print_config () {
    std::cout //
        << "  --print_config               " << std::endl;
}
void OptionHandler::print_usage_list_configs () {
    std::cout //
        << "  --list_configs               " << std::endl;
}
void OptionHandler::print_usage_save_config () {
    std::cout //
        << "  --save_config                " << std::endl;
}

void OptionHandler::print_usage_particle_sim () {
    std::cout << "Usage:" << std::endl;
    print_usage_algorithm ();
    print_usage_data_structure ();
    print_usage_input ();
    print_usage_output ();
    print_usage_write_modes ();
    //
    print_usage_autotuneing ();
    print_usage_bounds ();
    print_usage_write_fequency ();
    print_usage_help ();
    print_usage_in_file_name ();
    print_usage_run_time_limit ();
    print_usage_max_iterations ();
    print_usage_out_file_name ();
    print_usage_particle_count ();
    print_usage_cut_off_radius ();
    print_usage_seed ();
    print_usage_timestep ();
    print_usage_verbose ();
    //
    print_usage_load_confing ();
    print_usage_print_config ();
    print_usage_list_configs ();
    print_usage_save_config ();
}
