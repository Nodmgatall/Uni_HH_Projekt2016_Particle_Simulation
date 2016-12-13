#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "DatastructureList"

#include "algorithms/AlgorithmLennardJones.hpp"
#include "borders/BorderWrapparound.hpp"
#include "datastructures/DatastructureList.hpp"
#include "io/output/file/FileWriterCSV.hpp"
#include <boost/test/unit_test.hpp>
void generate_test_particle_list () {
}
BOOST_AUTO_TEST_CASE (calculate_distance_vectors) {
    std::vector<data_type> x_positions = { 1.5, 1.5, 1.5, 0.75 };
    std::vector<data_type> y_positions = { 1.5, 2.0, 2.5, 0.75 };
    std::vector<data_type> z_positions = { 1.5, 1.5, 1.5, 1.5 };

    std::vector<data_type> x_distances (6);
    std::vector<data_type> y_distances (6);
    std::vector<data_type> z_distances (6);
    std::vector<data_type> expected_x_distances = { 0, 0, 0.75, 0, 0.75, 0.75 };
    std::vector<data_type> expected_y_distances = { -0.5, -1, 0.75, -0.5, 1.25, 1.75 };
    std::vector<data_type> expected_z_distances = { 0, 0, 0, 0, 0, 0 };
    Vec3f                  bounds (3, 3, 3);

    s_options options = {
        e_algorithm_type::LENNARD_JONES, false, e_output_type::FILE_CSV, "", "", 1000, 1, false, 1,
        e_datastructure_type::GRID,      {}
    };
    BorderWrapparound     border (bounds);
    AlgorithmLennardJones algorithm (options);
    FileWriterCSV         writer (options, "");
    DatastructureList     particle_list (options, border, algorithm, writer);

    unsigned long start_pos      = 0;
    unsigned long particle_count = 4;
    for (unsigned long i = 0, range = particle_count - 1; i < particle_count - 1; i++, range--) {
        particle_list.calculate_distance_vectors (i,
                                                  &x_distances[0],
                                                  &y_distances[0],
                                                  &z_distances[0],
                                                  &x_positions[0],
                                                  &y_positions[0],
                                                  &z_positions[0],
                                                  start_pos,
                                                  range);
        start_pos += (4 - (i + 1));
    }
    for (unsigned long i = 0; i < 6; i++) {
        m_standard_stream << x_distances[i] << " " << expected_x_distances[i] << std::endl;
        m_standard_stream << y_distances[i] << " " << expected_y_distances[i] << std::endl;
        m_standard_stream << z_distances[i] << " " << expected_z_distances[i] << std::endl;
        BOOST_CHECK_EQUAL (x_distances[i], expected_x_distances[i]);
        BOOST_CHECK_EQUAL (y_distances[i], expected_y_distances[i]);
        BOOST_CHECK_EQUAL (z_distances[i], expected_z_distances[i]);
        m_standard_stream << "====" << std::endl;
    }
}
BOOST_AUTO_TEST_CASE (calculate_distances_squared) {
    std::vector<data_type> x_distances = { 0, 0, 0.75, 0, 0.75, 0.75 };
    std::vector<data_type> y_distances = { -0.5, -1, 0.75, -0.5, 1.25, 1.75 };
    std::vector<data_type> z_distances = { 0, 0, 0, 0, 0, 0 };
    Vec3f                  bounds (3, 3, 3);

    s_options options = {
        e_algorithm_type::LENNARD_JONES, false, e_output_type::FILE_CSV, "", "", 1000, 1, false, 1,
        e_datastructure_type::GRID,      {}
    };
    BorderWrapparound     border (bounds);
    AlgorithmLennardJones algorithm (options);
    FileWriterCSV         writer (options, "");
    DatastructureList     particle_list (options, border, algorithm, writer);

    unsigned long          distances_count = 6;
    std::vector<data_type> distances_squared (6);
    std::vector<data_type> expected_distances_squared = { 0.25, 1, 1.125, 0.25, 2.125, 3.625 };
    particle_list.calculate_distances_squared (
        &distances_squared[0], &x_distances[0], &y_distances[0], &z_distances[0], distances_count);

    for (unsigned long i = 0; i < 6; i++) {
        BOOST_CHECK_EQUAL (distances_squared[i], expected_distances_squared[i]);
    }
}

BOOST_AUTO_TEST_CASE (build_lists) {
    std::vector<data_type> x_distances = { 0, 0, 0.75, 0, 0.75, 0.75 };
    std::vector<data_type> y_distances = { -0.5, -1, 0.75, -0.5, 1.25, 1.75 };
    std::vector<data_type> z_distances = { 0, 0, 0, 0, 0, 0 };
    Vec3f                  bounds (3, 3, 3);

    s_options options = {
        e_algorithm_type::LENNARD_JONES, false, e_output_type::FILE_CSV, "", "", 1000, 1, false, 1,
        e_datastructure_type::GRID,      {}
    };
    BorderWrapparound     border (bounds);
    AlgorithmLennardJones algorithm (options);
    FileWriterCSV         writer (options, "");
    DatastructureList     particle_list (options, border, algorithm, writer);

    particle_list.m_positions_x            = { 1.5, 1.5, 1.5, 0.75 };
    particle_list.m_positions_y            = { 1.5, 2.0, 2.5, 0.75 };
    particle_list.m_positions_z            = { 1.5, 1.5, 1.5, 1.5 };
    unsigned long          distances_count = 6;
    std::vector<data_type> distances_squared (6);
    particle_list.build_lists_smarter (&x_distances[0], &y_distances[0], &z_distances[0], &distances_squared[0], distances_count);

    BOOST_CHECK_EQUAL (particle_list.m_mat_positions_x.size (), 4);
    BOOST_CHECK_EQUAL (particle_list.m_mat_positions_y.size (), 4);
    BOOST_CHECK_EQUAL (particle_list.m_mat_positions_z.size (), 4);

    BOOST_CHECK_EQUAL (particle_list.m_mat_positions_x[0].size (), 1);
    BOOST_CHECK_EQUAL (particle_list.m_mat_positions_x[1].size (), 2);
    BOOST_CHECK_EQUAL (particle_list.m_mat_positions_x[2].size (), 1);
    BOOST_CHECK_EQUAL (particle_list.m_mat_positions_x[3].size (), 0);
}
