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

    int         argv_index;
    bool        save_config         = false;
    bool        load_config         = false;
    bool        list_configs        = false;
    bool        config_feature_used = false;
    bool        print_config        = true;
    bool        print_saved_config  = false;
    std::string config_name         = "";
    int         algorithm_set       = 0;
    int         data_format_set     = 0;
    int         generator_mode_set  = 0;
    int         index;
    const int   algorithm_type_index     = 1;
    const int   datastructure_type_index = 2;
    const int   input_type_index         = 3;
    const int   output_type_index        = 4;
    const int   write_modes_index        = 5;
    /*clang-format off */
    std::vector<option> options = { { "algorithm", required_argument, 0, algorithm_type_index * 1000 },
                                    { "data_structure", required_argument, 0, datastructure_type_index * 1000 },
                                    { "input", required_argument, 0, input_type_index * 1000 },
                                    { "output", required_argument, 0, output_type_index * 1000 },

                                    // Verbose option
                                    { "verbose", no_argument, 0, 'v' },

                                    // Simulation parameters
                                    { "seed", required_argument, 0, 's' },
                                    { "particle_count", required_argument, 0, 'p' },
                                    { "run_time_limit", required_argument, 0, 'l' },
                                    { "timestep", required_argument, 0, 't' },
                                    { "dynamic", no_argument, 0, 'd' },
                                    { "write_fequency", required_argument, 0, 'f' },
                                    { "cutoff_radius", required_argument, 0, 'r' },
                                    { "iterations", required_argument, 0, 'i' },

                                    // Misc
                                    { "help", no_argument, 0, 'h' },
                                    { "load_config", required_argument, 0, 28 },
                                    { "print_config", required_argument, 0, 29 },
                                    { "list_configs", no_argument, 0, 30 },
                                    { "save_config", required_argument, 0, 31 }

    };
    for (index = 1; index < (signed) g_csv_column_names.size (); index++) {
        options.push_back ({ g_csv_column_names[index], required_argument, 0, write_modes_index * 1000 + index });
    }

    /*clang-format on */
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
            default:
                switch (argv_index) {
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
                    case 'v': {
                        p_options.m_verbose = true;
                        break;
                    }
                    case 's': {
                        p_options.m_seed = std::stoi (optarg);
                        break;
                    }
                    case 'p': {
                        p_options.m_particle_count = std::stoi (optarg);
                        break;
                    }
                    case 'f': {
                        p_options.m_write_fequency = std::stoi (optarg);
                        break;
                    }
                    case 'r':
                        p_options.m_cut_off_radius = std::stof (optarg);
                        break;
                    case 'l': {
                        p_options.m_run_time_limit = std::stof (optarg);
                        break;
                    }
                    case 't': {
                        p_options.m_timestep = std::stof (optarg);
                        break;
                    }
                    case 'd': {
                        p_options.m_autotuneing = true;
                        break;
                    }
                    case 'i': {
                        p_options.m_max_iterations = std::stoi (optarg);
                        break;
                    }
                    case 'h': {
                        print_usage_particle_sim ();
                        exit (EXIT_SUCCESS);
                        break;
                    }
                    case '?': {
                        std::cout << "Error: unkown option" << std::endl;
                        print_usage_particle_sim ();
                        exit (EXIT_SUCCESS);
                        break;
                    }
                }
        }
    }
    if (generator_mode_set > 1) {
        std::cout << "Error: multiple generator modes set" << std::endl;
        exit (EXIT_SUCCESS);
    }
    if (algorithm_set > 1) {
        std::cout << "Error: multiple algorithms set" << std::endl;
        exit (EXIT_SUCCESS);
    }
    if (data_format_set > 1) {
        std::cout << "Error: multiple data formats set" << std::endl;
        exit (EXIT_SUCCESS);
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
    (void) p_options;
    // DEBUG_BEGIN << "algorithm     :" << m_algorithm << DEBUG_END;
    // DEBUG_BEGIN << "particles:" << m_particles << DEBUG_END;
    DEBUG_BEGIN << "generator seed : " << p_options.m_seed << DEBUG_END;
    DEBUG_BEGIN << "generator mode : " << p_options.m_input_type << DEBUG_END;
    DEBUG_BEGIN << "algorithm_type : " << p_options.m_algorithm_type << DEBUG_END;
    DEBUG_BEGIN << "autotuneing    : " << p_options.m_autotuneing << DEBUG_END;
    DEBUG_BEGIN << "data_format    : " << p_options.m_output_type << DEBUG_END;
    DEBUG_BEGIN << "file_in_name   : " << p_options.m_in_file_name << DEBUG_END;
    DEBUG_BEGIN << "file_out_name  : " << p_options.m_out_file_name << DEBUG_END;
    DEBUG_BEGIN << "particle_count : " << p_options.m_particle_count << DEBUG_END;
    DEBUG_BEGIN << "run_time_limit : " << p_options.m_run_time_limit << DEBUG_END;
    DEBUG_BEGIN << "timestep       : " << p_options.m_timestep << DEBUG_END;
    DEBUG_BEGIN << "verbose        : " << p_options.m_verbose << DEBUG_END;
    DEBUG_BEGIN << "write_fequency : " << p_options.m_write_fequency << DEBUG_END;
    DEBUG_BEGIN << "cut_off_radius : " << p_options.m_cut_off_radius << DEBUG_END;
    DEBUG_BEGIN << "write_modes    : [ID";
    if (p_options.m_write_modes[e_csv_column_type::POSITION]) {
        g_debug_stream << ", " << e_csv_column_type::POSITION;
    }
    if (p_options.m_write_modes[e_csv_column_type::VELOCITY]) {
        g_debug_stream << ", " << e_csv_column_type::VELOCITY;
    }
    if (p_options.m_write_modes[e_csv_column_type::ACCELERATION]) {
        g_debug_stream << ", " << e_csv_column_type::ACCELERATION;
    }
    if (p_options.m_write_modes[e_csv_column_type::PARTICLE_TYPE]) {
        g_debug_stream << ", " << e_csv_column_type::PARTICLE_TYPE;
    }
    g_debug_stream << "]" << DEBUG_END;
    /*
     macro_debug("generator_mode :" ,
     p_options.particle_generator->get_generator_mode());
     macro_debug("data_structure :" , p_options.particles->get_structure_name());
     */
    Benchmark::end ();
}

void OptionHandler::print_usage_generation_mode () {
    std::cout << "Usage:" << std::endl;
    std::cout << "-g [generation_mode]" << std::endl;
}

void OptionHandler::print_usage_particle_sim () {
    std::cout << "Usage:" << std::endl;
    std::cout << "Write options:" << std::endl;
    std::cout << "  --write_velo" << std::endl;
    std::cout << "  --write_pos" << std::endl;
    std::cout << "  --write_accel" << std::endl;
    std::cout << "  --write_type" << std::endl << std::endl;

    std::cout << "Particle generator modes:" << std::endl;
    std::cout << "  --multiple_objects" << std::endl;
    std::cout << "  --random" << std::endl;
    std::cout << "  --random_uniform" << std::endl;
    std::cout << "  --single_object_middle" << std::endl;
    std::cout << "  --uniform_dist" << std::endl << std::endl;

    std::cout << "Algorihm types:" << std::endl;
    std::cout << "  --lennard" << std::endl;
    std::cout << "  --smothed" << std::endl;
    std::cout << "  --dissapative" << std::endl << std::endl;

    std::cout << "Data structure types" << std::endl;
    std::cout << "  --grid" << std::endl;
    std::cout << "  --list" << std::endl << std::endl;

    std::cout << "Simulation parameters" << std::endl;
    std::cout << "  -v | --verbose" << std::endl;
    std::cout << "  -s | --seed" << std::endl;
    std::cout << "  -p | --particle_count" << std::endl;
    std::cout << "  -l | --run_time_limit" << std::endl;
    std::cout << "  -f | --write_fequency" << std::endl;
    std::cout << "  -r | --cut_off_radius" << std::endl;
    std::cout << "  -t | --timestep" << std::endl;
    std::cout << "  -h | --help" << std::endl;
    std::cout << "  -d | --dynamic" << std::endl << std::endl;

    std::cout << "Config options" << std::endl;
    std::cout << "  --load_confing " << std::endl;
    std::cout << "  --print_config" << std::endl;
    std::cout << "  --list_configs" << std::endl;
    std::cout << "  --save_config" << std::endl;
}
