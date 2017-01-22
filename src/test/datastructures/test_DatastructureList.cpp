
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "DatastructureList"
#include "borders/BorderWrapparound.hpp"
#include "datastructures/DatastructureList.hpp"
#include "io/output/file/FileWriterCSV.hpp"
#include <algorithms/AlgorithmStoermerVerletLennardJones.hpp>
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_CASE (calculate_distances_squared) {
    Vec3f     bounds (3, 3, 3);
    s_options options;
    options.m_algorithm_type      = e_algorithm_type::LENNARD_JONES;
    options.m_autotuneing         = false;
    options.m_output_type         = e_output_type::FILE_CSV;
    options.m_in_file_name        = "";
    options.m_out_file_name       = "";
    options.m_timestep            = 1000;
    options.m_verbose             = 1;
    options.m_write_fequency      = false;
    options.m_cut_off_radius      = 1;
    options.m_data_structure_type = e_datastructure_type::GRID;
    options.m_write_modes         = {};
    BorderWrapparound                   border (bounds);
    AlgorithmStoermerVerletLennardJones algorithm (options);
    FileWriterCSV                       writer (options, "");
    DatastructureList                   particle_list (options, border, algorithm, writer);
    particle_list.m_positions_x_now                    = { 1.5, 1.5, 1.5, 0.75 };
    particle_list.m_positions_y_now                    = { 1.5, 2.0, 2.5, 0.75 };
    particle_list.m_positions_z_now                    = { 1.5, 1.5, 1.5, 1.5 };
    unsigned long                       particle_count = 4;
    std::vector<data_type>              distances_squared;
    std::vector<std::vector<data_type>> expected_distances_squared = { { 0.25, 1, 1.125 }, { 0.25, 2.125 }, { 3.625 } };
    for (unsigned long j = 0; j < particle_count - 1; j++) {
        unsigned long required_distance_calculations = particle_count - 1 - j;
        distances_squared.clear ();
        distances_squared.resize (required_distance_calculations);
        particle_list.calculate_distances_squared (j, &distances_squared[0]);
        for (unsigned long i = 0; i < required_distance_calculations; i++) {
            BOOST_CHECK_EQUAL (distances_squared[i], expected_distances_squared[j][i]);
        }
    }
}
BOOST_AUTO_TEST_CASE (build_lists) {
    Vec3f     bounds (3, 3, 3);
    s_options options;
    options.m_algorithm_type      = e_algorithm_type::LENNARD_JONES;
    options.m_autotuneing         = false;
    options.m_output_type         = e_output_type::FILE_CSV;
    options.m_in_file_name        = "";
    options.m_out_file_name       = "";
    options.m_timestep            = 1000;
    options.m_verbose             = 1;
    options.m_write_fequency      = false;
    options.m_cut_off_radius      = 1;
    options.m_data_structure_type = e_datastructure_type::GRID;
    options.m_write_modes         = {};
    BorderWrapparound                   border (bounds);
    AlgorithmStoermerVerletLennardJones algorithm (options);
    FileWriterCSV                       writer (options, "");
    DatastructureList                   particle_list (options, border, algorithm, writer);
    particle_list.m_positions_x_now = { 1.5, 1.5, 1.5, 0.75, 1, 1.5 };
    particle_list.m_positions_y_now = { 1.5, 2.0, 2.5, 0.75, 1.5, 3 };
    particle_list.m_positions_z_now = { 1.5, 1.5, 1.5, 1.5, 1.5, 1.5 };
    unsigned long particle_count    = 6;
    particle_list.build_lists ();
    std::vector<unsigned long> expectet_section_list = { 0, 2, 4, 5, 6, 6 };
    std::vector<unsigned long> expected_list         = { 1, 4, 2, 4, 5, 4 };
    BOOST_CHECK_EQUAL (6, particle_list.m_neighbour_idxs_list.size ());
    BOOST_CHECK_EQUAL (6, particle_list.m_neighbour_section_idxs.size ());
    for (unsigned int i = 0; i < particle_count - 1; i++) {
        BOOST_CHECK_EQUAL (expectet_section_list[i], particle_list.m_neighbour_section_idxs[i]);
        for (unsigned long j = particle_list.m_neighbour_section_idxs[i]; j < particle_list.m_neighbour_section_idxs[i + 1]; j++) {
            BOOST_CHECK_EQUAL (expected_list[j], particle_list.m_neighbour_idxs_list[j]);
        }
    }
}
