#include "../Definitions.hpp"
#include <fstream>
#include <iostream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include "Config.hpp"
#include "ConfigLoader.hpp"
#include "OptionsGenerator.hpp"
#include "OptionsSimulation.hpp"

ConfigLoader::ConfigLoader () : m_config_file_name (".config_sim") {
    deserialize_configs ();
}

ConfigLoader::~ConfigLoader () {
    serialize_configs ();
}

void ConfigLoader::serialize_configs () {
    std::ofstream out_file_stream (m_config_file_name);
    if (out_file_stream.is_open ()) {
        boost::archive::xml_oarchive out_archive (out_file_stream);
        out_archive << boost::serialization::make_nvp ("configs", m_configs);
    } else {
        std::cout << "Error: could not open file: " << m_config_file_name << std::endl;
        exit (EXIT_FAILURE);
    }
}

void ConfigLoader::deserialize_configs () {
    std::string   input;
    std::ifstream in_file_stream (m_config_file_name);
    if (in_file_stream.is_open ()) {
        if (in_file_stream.good ()) {

            if (in_file_stream.peek () == std::ifstream::traits_type::eof ()) {
                std::cout << "Config file empty or corrupted" << std::endl;
                std::cout << "Do you wan to continue? File could be deleted(y/n)" << std::endl;
#ifndef DESKTOP_VERSION
                std::cin >> input;
#else
                input = "n";
#endif
                if (input[0] != 'y') {
                    exit (EXIT_SUCCESS);
                }
            } else {
                boost::archive::xml_iarchive in_archive (in_file_stream);
                in_archive >> boost::serialization::make_nvp ("configs", m_configs);
            }
        }
    } else {
        std::cout << "Error: File not found: " << m_config_file_name << std::endl;
        std::cout << "do you want to create a new file vor saving input configs?(y/n)" << std::endl;
#ifndef DESKTOP_VERSION
        std::cin >> input;
#else
        input = "n";
#endif
        if (input[0] == 'y') {
            std::cout << "created new config file" << std::endl;
        } else {
            exit (EXIT_FAILURE);
        }
    }
}

void ConfigLoader::load_config (std::string          p_config_name,
                                s_simulator_options *p_sim_options,
                                s_generator_options *p_gen_options) {
    *p_sim_options = m_configs[p_config_name].m_sim_options;
    *p_gen_options = m_configs[p_config_name].m_gen_options;
}

void ConfigLoader::save_config (std::string          p_config_name,
                                s_simulator_options *p_sim_options,
                                s_generator_options *p_gen_options) {
    if (m_configs.find (p_config_name) == m_configs.end ()) {
        Config new_config;
        new_config.m_config_name = p_config_name;
        new_config.m_gen_options = *p_gen_options;
        new_config.m_sim_options = *p_sim_options;
        m_configs[p_config_name] = new_config;
    } else {
        std::cout << "Error: config name " << p_config_name << "already in use" << std::endl;
        exit (EXIT_FAILURE);
    }
}

void ConfigLoader::list_configs () {
    std::cout << "Saved configs:" << std::endl;
    for (auto map_iterator = m_configs.begin (); map_iterator != m_configs.end (); map_iterator++) {
        std::cout << map_iterator->first << std::endl;
    }
}
