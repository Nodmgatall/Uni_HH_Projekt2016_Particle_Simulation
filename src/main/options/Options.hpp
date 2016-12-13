#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "Definitions.hpp"
#include "Vec3.hpp"
#include <map>
#include <vector>
struct s_options {
    e_algorithm_type            m_algorithm_type      = e_algorithm_type::LENNARD_JONES;
    bool                        m_autotuneing         = false;
    Vec3f                       m_bounds              = Vec3f (5.0f, 5.0f, 5.0f);
    data_type                   m_cut_off_radius      = 0.01;
    e_datastructure_type        m_data_structure_type = e_datastructure_type::GRID;
    e_input_type                m_input_type          = e_input_type::GENERATOR_GRID_DISTRIBUTION;
    std::string                 m_in_file_name        = "";
    unsigned long               m_max_iterations      = 0;
    int                         m_max_iterations_between_datastructure_rebuild = 20;
    e_output_type               m_output_type    = e_output_type::FILE_CSV;
    std::string                 m_out_file_name  = "";
    unsigned long               m_particle_count = 0;
    unsigned int                m_seed           = 123456789;
    data_type                   m_timestep       = 1;
    bool                        m_verbose        = false;
    int                         m_write_fequency = 1;
    std::set<e_csv_column_type> m_write_modes    = { e_csv_column_type::ID,
                                                  e_csv_column_type::POSITION,
                                                  e_csv_column_type::VELOCITY };
};
#endif
