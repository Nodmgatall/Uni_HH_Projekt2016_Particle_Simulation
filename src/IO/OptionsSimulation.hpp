#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "../Definitions.hpp"
#include <map>
#include <vector>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

struct s_simulator_options {
	friend class boost::serialization::access;
	e_algorithm_type m_algorithm_type = LENNARD_JONES;
	bool			 m_autotuneing	= false;
	e_data_format	m_data_format	= CSV;
	std::string		 m_in_file_name   = "";
	std::string		 m_out_file_name  = "";
	unsigned long	m_particle_count = 0;
	float			 m_run_time_limit = 1000;
	unsigned int	 m_seed			  = 0;
	float			 m_timestep		  = 1;
	bool			 m_verbose		  = false;
	int				 m_write_fequency = 1;
	e_data_structure m_data_structure = GRID;
	std::map<e_particle_variable, bool> m_write_modes = { { ID, true },
														  { POSITION, true },
														  { VELOCITY, true },
														  { ACCELERATION, true },
														  { PARTICLE_TYPE, true } };

	template <class Archive>
	void serialize (Archive &s_sim_options, const unsigned int version) {
		(void) version;
		s_sim_options &BOOST_SERIALIZATION_NVP (m_algorithm_type);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_autotuneing);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_data_format);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_in_file_name);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_out_file_name);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_particle_count);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_run_time_limit);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_seed);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_timestep);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_verbose);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_write_fequency);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_data_structure);
		s_sim_options &BOOST_SERIALIZATION_NVP (m_write_modes);
	}
};
#endif
