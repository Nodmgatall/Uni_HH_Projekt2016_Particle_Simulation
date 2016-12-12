#include "Definitions.hpp"
#include <fstream>
#include <iostream>
#ifdef BOOST_AVAILABLE
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>
#endif
#include "Config.hpp"
#include "ConfigLoader.hpp"

ConfigLoader::ConfigLoader () : m_config_file_name (".config_sim") {
    deserialize_configs ();
}

ConfigLoader::~ConfigLoader () {
    serialize_configs ();
}

void ConfigLoader::serialize_configs () {
#ifdef BOOST_AVAILABLE
    std::ofstream out_file_stream (m_config_file_name);
    if (out_file_stream.is_open ()) {
        boost::archive::xml_oarchive out_archive (out_file_stream);
        out_archive << boost::serialization::make_nvp ("configs", m_configs);
    } else {
        m_error_stream << "Error: could not open file: " << m_config_file_name << std::endl;
        exit (EXIT_FAILURE);
    }
#endif
}

void ConfigLoader::deserialize_configs () {
#ifdef BOOST_AVAILABLE
    std::string   input;
    std::ifstream in_file_stream (m_config_file_name);
    if (in_file_stream.is_open ()) {
        if (in_file_stream.good ()) {
            if (in_file_stream.peek () == std::ifstream::traits_type::eof ()) {
                m_error_stream << "Config file empty or corrupted" << std::endl;
                m_error_stream << "Do you wan to continue? File could be deleted(y/n)" << std::endl;
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
        m_error_stream << "Error: File not found: " << m_config_file_name << std::endl;
        m_error_stream << "do you want to create a new file vor saving input configs?(y/n)" << std::endl;
#ifndef DESKTOP_VERSION
        std::cin >> input;
#else
        input         = "n";
#endif
        if (input[0] == 'y') {
            m_error_stream << "created new config file" << std::endl;
        } else {
            exit (EXIT_FAILURE);
        }
    }
#endif
}

void ConfigLoader::load_config (std::string p_config_name, s_options& p_options) {
    p_options = m_configs[p_config_name].m_options;
}

void ConfigLoader::save_config (std::string p_config_name, s_options& p_options) {
    if (m_configs.find (p_config_name) == m_configs.end ()) {
        Config new_config;
        new_config.m_config_name = p_config_name;
        new_config.m_options     = p_options;
        m_configs[p_config_name] = new_config;
    } else {
        m_error_stream << "Error: config name " << p_config_name << "already in use" << std::endl;
        exit (EXIT_FAILURE);
    }
}

void ConfigLoader::list_configs () {
    m_standard_stream << "Saved configs:" << std::endl;
    for (auto map_iterator = m_configs.begin (); map_iterator != m_configs.end (); map_iterator++) {
        m_standard_stream << map_iterator->first << std::endl;
    }
}
