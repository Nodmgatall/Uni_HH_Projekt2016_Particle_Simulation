#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <map>

#include "Config.hpp"
#include "OptionsGenerator.hpp"
#include "OptionsSimulation.hpp"

class ConfigLoader {
	public:
	std::string m_config_file_name;
	std::map<std::string, Config> m_configs;

	ConfigLoader ();
    ~ConfigLoader();
	void load_config (std::string p_config_name, s_simulator_options *p_sim_options, s_generator_options *p_gen_options);
	void save_config (std::string p_config_name, s_simulator_options *p_sim_options, s_generator_options *p_gen_options);
	void serialize_configs ();
	void deserialize_configs ();
	void list_configs ();
};
#endif
