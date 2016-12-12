#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "Definitions.hpp"
#include "Vec3.hpp"
#if defined(BOOST_AVAILABLE)
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>
#endif
#include <map>
#include <vector>
struct s_options {
    e_algorithm_type     m_algorithm_type = e_algorithm_type::LENNARD_JONES;
    bool                 m_autotuneing    = false;
    e_output_type        m_output_type    = e_output_type::FILE_CSV;
    std::string          m_in_file_name   = "";
    std::string          m_out_file_name  = "";
    data_type            m_timestep       = 1;
    bool                 m_verbose        = false;
    int                  m_write_fequency = 1;
    data_type            m_cut_off_radius = 0.01;
    e_datastructure_type m_data_structure = e_datastructure_type::GRID;
    std::map<e_csv_column_type, bool> m_write_modes = { { e_csv_column_type::ID, true },
                                                        { e_csv_column_type::POSITION, true },
                                                        { e_csv_column_type::VELOCITY, true },
                                                        { e_csv_column_type::ACCELERATION, true },
                                                        { e_csv_column_type::PARTICLE_TYPE, false } };
    e_input_type  m_input_type     = e_input_type::GENERATOR_GRID_DISTRIBUTION;
    unsigned int  m_seed           = 123456789;
    unsigned long m_particle_count = 0;
    unsigned long m_max_iterations = 0;
    Vec3f         m_bounds         = Vec3f (5.0f, 5.0f, 5.0f);
    int           m_max_iterations_between_datastructure_rebuild = 20;
#if defined(BOOST_AVAILABLE)
    friend class boost::serialization::access;
    template <class Archive>
    void serialize (Archive& archive, const unsigned int version) {
        (void) version;
        archive& boost::serialization::make_nvp ("autotuneing", m_autotuneing);
        archive& boost::serialization::make_nvp ("output_type", m_output_type);
        archive& boost::serialization::make_nvp ("in_file_name", m_in_file_name);
        archive& boost::serialization::make_nvp ("out_file_name", m_out_file_name);
        archive& boost::serialization::make_nvp ("timestep", m_timestep);
        archive& boost::serialization::make_nvp ("verbose", m_verbose);
        archive& boost::serialization::make_nvp ("write_fequency", m_write_fequency);
        archive& boost::serialization::make_nvp ("cut_off_radius", m_cut_off_radius);
        archive& boost::serialization::make_nvp ("data_structure", m_data_structure);
        archive& boost::serialization::make_nvp ("write_modes", m_write_modes);
        archive& boost::serialization::make_nvp ("input_type", m_input_type);
        archive& boost::serialization::make_nvp ("seed", m_seed);
        archive& boost::serialization::make_nvp ("particle_count", m_particle_count);
        archive& boost::serialization::make_nvp ("max_iterations", m_max_iterations);
        archive& boost::serialization::make_nvp ("bounds", m_bounds);
        archive& boost::serialization::make_nvp ("max_iterations_between_datastructure_rebuild",
                                                 m_max_iterations_between_datastructure_rebuild);
    }
#endif
};
#endif
