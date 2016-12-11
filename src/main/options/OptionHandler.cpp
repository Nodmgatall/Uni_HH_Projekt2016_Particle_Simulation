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
                                    { "write_fequency", required_argument, 0, 'f' },
                                    { "help", no_argument, 0, 'h' },
                                    { "in_file_name", required_argument, 0, 'i' },
                                    { "run_time_limit", required_argument, 0, 'l' },
                                    { "max_iterations", required_argument, 0, 'm' },
                                    { "out_file_name", required_argument, 0, 'o' },
                                    { "particle_count", required_argument, 0, 'p' },
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
    int long_options;
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
                std::stringstream line (optarg);
                switch (argv_index) {
                    case 'a': {
                        p_options.m_autotuneing = true;
                        break;
                    }
                    case 'b': {
                        line >> p_options.m_bounds;
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
                        line >> p_options.m_in_file_name;
                        break;
                    }
                    case 'l': {
                        line >> p_options.m_run_time_limit;
                        break;
                    }
                    case 'm': {
                        line >> p_options.m_max_iterations;
                        break;
                    }
                    case 'o': {
                        line >> p_options.m_out_file_name;
                        break;
                    }
                    case 'p': {
                        line >> p_options.m_particle_count;
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

                    // config options
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
    DEBUG_BEGIN << "run_time_limit                               " << p_options.m_run_time_limit << DEBUG_END;
    DEBUG_BEGIN << "timestep                                     " << p_options.m_timestep << DEBUG_END;
    DEBUG_BEGIN << "verbose                                      " << p_options.m_verbose << DEBUG_END;
    DEBUG_BEGIN << "write_fequency                               " << p_options.m_write_fequency << DEBUG_END;
    DEBUG_BEGIN << "cut_off_radius                               " << p_options.m_cut_off_radius << DEBUG_END;
    DEBUG_BEGIN << "data_structure                               " << p_options.m_data_structure << DEBUG_END;
    DEBUG_BEGIN << "input_type                                   " << p_options.m_input_type << DEBUG_END;
    DEBUG_BEGIN << "seed                                         " << p_options.m_seed << DEBUG_END;
    DEBUG_BEGIN << "particle_count                               " << p_options.m_particle_count << DEBUG_END;
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

void OptionHandler::print_usage_particle_sim () {
    int index;
    std::cout << "Usage:" << std::endl;
    //
    std::cout << "--algorithm=< " << g_algorithm_names[1];
    for (index = 1; index < (signed) g_algorithm_names.size (); index++) {
        std::cout << " | " << g_algorithm_names[index];
    }
    std::cout << " >" << std::endl;
    //
    std::cout << "--data_structure=< " << g_datastructure_names[1];
    for (index = 1; index < (signed) g_datastructure_names.size (); index++) {
        std::cout << " | " << g_datastructure_names[index];
    }
    std::cout << " >" << std::endl;
    //
    std::cout << "--input=< " << g_input_names[1];
    for (index = 1; index < (signed) g_input_names.size (); index++) {
        std::cout << " | " << g_input_names[index];
    }
    std::cout << " >" << std::endl;
    //
    std::cout << "--output=< " << g_output_names[1];
    for (index = 1; index < (signed) g_output_names.size (); index++) {
        std::cout << " | " << g_output_names[index];
    }
    std::cout << " >" << std::endl;
    //
    for (index = 1; index < (signed) g_csv_column_names.size (); index++) {
        std::cout << "--WRITE_" << g_csv_column_names[index];
    }
    //
    std::cout << "Simulation parameters" << std::endl;
    std::cout << "  -v | --verbose" << std::endl;
    std::cout << "  -s | --seed" << std::endl;
    std::cout << "  -p | --particle_count" << std::endl;
    std::cout << "  -l | --run_time_limit" << std::endl;
    std::cout << "  -f | --write_fequency" << std::endl;
    std::cout << "  -r | --cut_off_radius" << std::endl;
    std::cout << "  -t | --timestep" << std::endl;
    std::cout << "  -h | --help" << std::endl;
    std::cout << "  -a | --autotuneing" << std::endl << std::endl;

    std::cout << "Config options" << std::endl;
    std::cout << "  --load_confing " << std::endl;
    std::cout << "  --print_config" << std::endl;
    std::cout << "  --list_configs" << std::endl;
    std::cout << "  --save_config" << std::endl;
}
