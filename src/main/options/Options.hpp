#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "Definitions.hpp"
#include "Vec3.hpp"
#include <map>
#include <vector>
struct s_options {
    e_algorithm_type            m_algorithm_type;
    bool                        m_autotuneing;
    Vec3f                       m_bounds;
    data_type                   m_cut_off_radius;
    e_datastructure_type        m_data_structure_type;
    e_input_type                m_input_type;
    std::string                 m_in_file_name;
    unsigned long               m_max_iterations;
    int                         m_max_iterations_between_datastructure_rebuild;
    e_output_type               m_output_type;
    std::string                 m_out_file_name;
    unsigned long               m_particle_count;
    unsigned int                m_seed;
    data_type                   m_timestep;
    bool                        m_verbose;
    int                         m_write_fequency;
    std::set<e_csv_column_type> m_write_modes;
    s_options ()
    : m_algorithm_type (e_algorithm_type::LENNARD_JONES), m_autotuneing (false),
      m_bounds (Vec3f (5.0f, 5.0f, 5.0f)), m_cut_off_radius (0.01),
      m_data_structure_type (e_datastructure_type::GRID),
      m_input_type (e_input_type::GENERATOR_GRID_DISTRIBUTION), m_in_file_name (""),
      m_max_iterations (0), m_max_iterations_between_datastructure_rebuild (20),
      m_output_type (e_output_type::FILE_CSV), m_out_file_name (""), m_particle_count (0),
      m_seed (123456789), m_timestep (1), m_verbose (false), m_write_fequency (1),
      m_write_modes ({ e_csv_column_type::ID, e_csv_column_type::POSITION, e_csv_column_type::VELOCITY }) {
    }
};
#endif
