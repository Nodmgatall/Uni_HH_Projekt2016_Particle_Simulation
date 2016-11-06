#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "../Definitions.hpp"
#include <map>
#include <vector>

struct s_simulator_options {
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
};

#endif
