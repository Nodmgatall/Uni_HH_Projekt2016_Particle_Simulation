#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP
#include "../Definitions.hpp"
#include <map>

#include "../options/Options.hpp"
#include "Config.hpp"

class ConfigLoader {
  public:
    std::string m_config_file_name;
    std::map<std::string, Config> m_configs;

    ConfigLoader ();
    ~ConfigLoader ();
    void load_config (std::string p_config_name, s_options& p_options);
    void save_config (std::string p_config_name, s_options& p_options);
    void serialize_configs ();
    void deserialize_configs ();
    void list_configs ();
};
#endif
