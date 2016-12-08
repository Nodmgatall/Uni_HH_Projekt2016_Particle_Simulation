#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "../Definitions.hpp"
#include <map>
#include <vector>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

struct s_options {
    friend class boost::serialization::access;
    e_algorithm_type m_algorithm_type = LENNARD_JONES;
    bool             m_autotuneing    = false;
    e_data_format    m_data_format    = CSV;
    std::string      m_in_file_name   = "";
    std::string      m_out_file_name  = "";
    data_type        m_run_time_limit = 1000;
    data_type        m_timestep       = 1;
    bool             m_verbose        = false;
    int              m_write_fequency = 1;
    data_type        m_cut_off_radius = 0.01;
    e_data_structure m_data_structure = GRID;
    std::map<e_particle_variable, bool> m_write_modes = { { ID, true },
                                                          { POSITION, true },
                                                          { VELOCITY, true },
                                                          { ACCELERATION, true },
                                                          { PARTICLE_TYPE, false } };
    e_generator_mode m_mode           = GRID_DISTRIBUTION;
    unsigned int     m_seed           = 123456789;
    unsigned long    m_particle_count = 0;
    unsigned long    m_max_iterations = 0;
	Vec3f m_bounds = Vec3f(5.0f, 5.0f, 5.0f);

    template <class Archive>
    void serialize (Archive &archive, const unsigned int version) {
        (void) version;
        archive &BOOST_SERIALIZATION_NVP (m_algorithm_type);
        archive &BOOST_SERIALIZATION_NVP (m_autotuneing);
        archive &BOOST_SERIALIZATION_NVP (m_data_format);
        archive &BOOST_SERIALIZATION_NVP (m_in_file_name);
        archive &BOOST_SERIALIZATION_NVP (m_out_file_name);
        archive &BOOST_SERIALIZATION_NVP (m_run_time_limit);
        archive &BOOST_SERIALIZATION_NVP (m_timestep);
        archive &BOOST_SERIALIZATION_NVP (m_verbose);
        archive &BOOST_SERIALIZATION_NVP (m_write_fequency);
        archive &BOOST_SERIALIZATION_NVP (m_cut_off_radius);
        archive &BOOST_SERIALIZATION_NVP (m_data_structure);
        archive &BOOST_SERIALIZATION_NVP (m_write_modes);
        archive &BOOST_SERIALIZATION_NVP (m_mode);
        archive &BOOST_SERIALIZATION_NVP (m_seed);
        archive &BOOST_SERIALIZATION_NVP (m_particle_count);
        archive &BOOST_SERIALIZATION_NVP (m_max_iterations);
		archive & BOOST_SERIALIZATION_NVP(m_bounds.x);
		archive & BOOST_SERIALIZATION_NVP(m_bounds.y);
		archive & BOOST_SERIALIZATION_NVP(m_bounds.z);
    }
};
#endif
