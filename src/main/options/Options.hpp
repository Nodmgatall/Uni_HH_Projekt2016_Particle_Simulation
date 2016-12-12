#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "Definitions.hpp"
#include "Vec3.hpp"
#include <map>
#include <vector>
struct s_options {
    e_algorithm_type     m_algorithm_type      = e_algorithm_type::LENNARD_JONES;
    bool                 m_autotuneing         = false;
    e_output_type        m_output_type         = e_output_type::FILE_CSV;
    std::string          m_in_file_name        = "";
    std::string          m_out_file_name       = "";
    data_type            m_timestep            = 1;
    bool                 m_verbose             = false;
    int                  m_write_fequency      = 1;
    data_type            m_cut_off_radius      = 0.01;
    e_datastructure_type m_data_structure_type = e_datastructure_type::GRID;
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

    inline friend std::ostream& operator<< (std::ostream& stream, const s_options& options) {
        stream
            << "algorithm_type                               : " << options.m_algorithm_type << std::endl //
            << "autotuneing                                  : " << options.m_autotuneing << std::endl //
            << "output_type                                  : " << options.m_output_type << std::endl //
            << "in_file_name                                 : " << options.m_in_file_name << std::endl //
            << "out_file_name                                : " << options.m_out_file_name << std::endl //
            << "timestep                                     : " << options.m_timestep << std::endl //
            << "verbose                                      : " << options.m_verbose << std::endl //
            << "write_fequency                               : " << options.m_write_fequency << std::endl //
            << "cut_off_radius                               : " << options.m_cut_off_radius << std::endl //
            << "data_structure_type                          : " << options.m_data_structure_type
            << std::endl //
            << "input_type                                   : " << options.m_input_type << std::endl //
            << "seed                                         : " << options.m_seed << std::endl //
            << "particle_count                               : " << options.m_particle_count << std::endl //
            << "max_iterations                               : " << options.m_max_iterations << std::endl //
            << "bounds                                       : " << options.m_bounds << std::endl //
            << "max_iterations_between_datastructure_rebuild : " << options.m_max_iterations_between_datastructure_rebuild
            << std::endl;

        // "write_modes" << m_write_modes  << std::endl; TODO

        return stream;
    }
    inline friend std::istream& operator>> (std::istream& stream, s_options& options) {
        int         count = 0;
        std::string name;
        std::string value;
        for (count = 0; count < 16; count++) {
            while ((stream.peek () == ' ') || (stream.peek () == ':') || (stream.peek () == '\n')) {
                stream.ignore ();
            }
            stream >> name;
            while ((stream.peek () == ' ') || (stream.peek () == ':') || (stream.peek () == '\n')) {
                stream.ignore ();
            }
            stream >> value;
            std::stringstream valuestream (value);
            if (name.compare ("algorithm_type")) {
                count++;
                valuestream >> options.m_algorithm_type;
            } else if (name.compare ("autotuneing")) {
                count++;
                valuestream >> options.m_autotuneing;
            } else if (name.compare ("output_type")) {
                count++;
                valuestream >> options.m_output_type;
            } else if (name.compare ("in_file_name")) {
                count++;
                valuestream >> options.m_in_file_name;
            } else if (name.compare ("out_file_name")) {
                count++;
                valuestream >> options.m_out_file_name;
            } else if (name.compare ("timestep")) {
                count++;
                valuestream >> options.m_timestep;
            } else if (name.compare ("verbose")) {
                count++;
                valuestream >> options.m_verbose;
            } else if (name.compare ("write_fequency")) {
                count++;
                valuestream >> options.m_write_fequency;
            } else if (name.compare ("cut_off_radius")) {
                count++;
                valuestream >> options.m_cut_off_radius;
            } else if (name.compare ("data_structure_type")) {
                count++;
                valuestream >> options.m_data_structure_type;
            } else if (name.compare ("input_type")) {
                count++;
                valuestream >> options.m_input_type;
            } else if (name.compare ("seed")) {
                count++;
                valuestream >> options.m_seed;
            } else if (name.compare ("particle_count")) {
                count++;
                valuestream >> options.m_particle_count;
            } else if (name.compare ("max_iterations")) {
                count++;
                valuestream >> options.m_max_iterations;
            } else if (name.compare ("bounds")) {
                count++;
                valuestream >> options.m_bounds;
            } else if (name.compare ("max_iterations_between_datastructure_rebuild")) {
                count++;
                valuestream >> options.m_max_iterations_between_datastructure_rebuild;
            }
        }
        return stream;
    }
};
#endif
