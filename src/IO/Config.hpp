#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "OptionsGenerator.hpp"
#include "OptionsSimulation.hpp"

struct Config {
	friend class boost::serialization::access;
	std::string			m_config_name;
	s_generator_options m_gen_options;
	s_simulator_options m_sim_options;

	template <class Archive>
	void serialize (Archive &archive, const unsigned int version) {
		(void) version;
		archive &BOOST_SERIALIZATION_NVP (m_config_name);
		archive &BOOST_SERIALIZATION_NVP (m_gen_options);
		archive &BOOST_SERIALIZATION_NVP (m_sim_options);
	}
};

#endif
