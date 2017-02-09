#ifndef OPTIONS_SIMULATION_HPP
#define OPTIONS_SIMULATION_HPP
#include "../Definitions.hpp"
#include "../Vec3.hpp"
#include <map>
#include <vector>
struct s_options {
    /**
     * the algorithm to use for particle-interactions
     */
    e_algorithm_type m_algorithm_type;
    /**
     * if autotuning should be used for determineing which datastructure should be used.
     */
    bool m_autotuning;
    /**
     * the volume used by the particles.
     */
    Vec3f m_bounds;
    /**
     * if the distance of 2 particles is greather than this cut-offradius, then the interactions
     * between them is ignored
     */
    data_type m_cut_off_radius;
    /**
     * which datastructure should be used. it is defined by parameter or by autotuning
     */
    e_datastructure_type m_data_structure_type;
    /**
     * thesource, from which the particles come
     */
    e_input_type m_input_type;
    /**
     * if particles should be loaded from a file, this is the (base-)name
     */
    std::string m_in_file_name;
    /**
     * when the simulation should be terminated
     */
    unsigned long m_max_iterations;
    /**
     * speed at program startup if input is an generator type
     */
    float m_initial_speed;
    /**
     * how ofthen sould the datastucture reorganize itself. this is can be given as argument. it is
     * planned, that the datastructure modifys this variable based on current maximum speed
     */
    unsigned int m_max_iterations_between_datastructure_rebuild;
    /**
     * how the output should be stored
     */
    e_output_type m_output_type;
    /**
     * where the output should be stored, if it is file-based
     */
    std::string m_out_file_name;
    /**
     * if input is generated by an generator, this defines how many particles should be generated
     */
    unsigned long m_particle_count;
    /**
     * some generators which use random, need a seed to generate particles. if it is not defined,
     * the systemtime is used
     */
    unsigned int m_seed;
    /**
     * how much time is "skipped" between two iteration-steps
     */
    data_type m_timestep;
    /**
     * if the output should be verbose or not
     */
    bool m_verbose;
    /**
     * how ofthen the data should be outputted to the given output_type_class
     */
    int m_write_fequency;
    /**
     * if output is csv-based, then this defines which columns should be there
     */
    std::set<e_csv_column_type> m_write_modes;
    /**
     * the size the cuttoff is increased to avoid rebuilding the particles too ofthen
     */
    data_type m_cut_off_factor;
    s_options ()
    : m_algorithm_type (e_algorithm_type::LENNARD_JONES), m_autotuning (false), m_bounds (Vec3f (5.0f, 5.0f, 5.0f)), m_cut_off_radius (0.01),
      m_data_structure_type (e_datastructure_type::GRID), m_input_type (e_input_type::GENERATOR_GRID_DISTRIBUTION), m_in_file_name (""), m_max_iterations (0), m_initial_speed (0),
      m_max_iterations_between_datastructure_rebuild (50), m_output_type (e_output_type::FILE_CSV), m_out_file_name (""), m_particle_count (0), m_seed (123456789), m_timestep (1),
      m_verbose (false), m_write_fequency (1), m_write_modes ({ e_csv_column_type::ID, e_csv_column_type::POSITION, e_csv_column_type::VELOCITY }), m_cut_off_factor (1.2) {
        time_t     current_time;
        struct tm* time_info;
        time (&current_time);
        time_info = localtime (&current_time);
        char tmp_str[100];
        strftime (tmp_str, sizeof (log_folder), "logdata/%Y-%m-%d_%H-%M-%S", time_info);
        m_out_file_name = std::string (tmp_str);
    }
    inline friend std::ostream& operator<< (std::ostream& stream, const s_options& p_options) {
        stream << "options.algorithm_type                                       : " << p_options.m_algorithm_type << std::endl;
        stream << "options.autotuning                                          : " << p_options.m_autotuning << std::endl;
        stream << "options.bounds                                               : " << p_options.m_bounds << std::endl;
        stream << "options.cut_off_radius                                       : " << p_options.m_cut_off_radius << std::endl;
        stream << "options.data_structure_type                                  : " << p_options.m_data_structure_type << std::endl;
        stream << "options.input_type                                           : " << p_options.m_input_type << std::endl;
        stream << "options.in_file_name                                         : " << p_options.m_in_file_name << std::endl;
        stream << "options.max_iterations                                       : " << p_options.m_max_iterations << std::endl;
        stream << "options.initial_speed                                        : " << p_options.m_initial_speed << std::endl;
        stream << "options.max_iterations_between_datastructure_rebuild         : " << p_options.m_max_iterations_between_datastructure_rebuild << std::endl;
        stream << "options.output_type                                          : " << p_options.m_output_type << std::endl;
        stream << "options.out_file_name                                        : " << p_options.m_out_file_name << std::endl;
        stream << "options.particle_count                                       : " << p_options.m_particle_count << std::endl;
        stream << "options.seed                                                 : " << p_options.m_seed << std::endl;
        stream << "options.timestep                                             : " << p_options.m_timestep << std::endl;
        stream << "options.verbose                                              : " << p_options.m_verbose << std::endl;
        stream << "options.write_fequency                                       : " << p_options.m_write_fequency << std::endl;
        stream << "options.write_modes                                          : " << p_options.m_write_modes << std::endl;
        return stream;
    }
};
#endif
