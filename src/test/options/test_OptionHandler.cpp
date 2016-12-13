/*
 * test_ParticleBoundsCorrectionWraparound.cpp
 *
 *  Created on: 08.12.2016
 *      Author: benjamin
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "OptionHandler"
#include "options/OptionHandler.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_CASE (test_algorithmLENNARD_JONES) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_algorithm_type = e_algorithm_type::LENNARD_JONES;
    std::vector<const char*> args    = { "./particle_simulation.x", "--algorithm=LENNARD_JONES" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_algorithmDISSIPATIVE_PARTICLE_DYNAMICS) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_algorithm_type = e_algorithm_type::DISSIPATIVE_PARTICLE_DYNAMICS;
    std::vector<const char*> args    = { "./particle_simulation.x",
                                      "--algorithm=DISSIPATIVE_PARTICLE_DYNAMICS" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_algorithmSMOTHED_PARTICLE_HYDRODYNAMICS) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_algorithm_type = e_algorithm_type::SMOTHED_PARTICLE_HYDRODYNAMICS;
    std::vector<const char*> args    = { "./particle_simulation.x",
                                      "--algorithm=SMOTHED_PARTICLE_HYDRODYNAMICS" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_datastructureGRID) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_data_structure_type = e_datastructure_type::GRID;
    std::vector<const char*> args         = { "./particle_simulation.x", "--data_structure=GRID" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_datastructureLIST) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_data_structure_type = e_datastructure_type::LIST;
    std::vector<const char*> args         = { "./particle_simulation.x", "--data_structure=LIST" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_datastructureLISTEDGIRD) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_data_structure_type = e_datastructure_type::LISTEDGIRD;
    std::vector<const char*> args = { "./particle_simulation.x", "--data_structure=LISTEDGIRD" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_inputFILE_CSV) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_input_type  = e_input_type::FILE_CSV;
    std::vector<const char*> args = { "./particle_simulation.x", "--input=FILE_CSV" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_inputGENERATOR_GRID_DISTRIBUTION) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_input_type  = e_input_type::GENERATOR_GRID_DISTRIBUTION;
    std::vector<const char*> args = { "./particle_simulation.x",
                                      "--input=GENERATOR_GRID_DISTRIBUTION" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_inputGENERATOR_MULTIPLE_OBJECTS) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_input_type  = e_input_type::GENERATOR_MULTIPLE_OBJECTS;
    std::vector<const char*> args = { "./particle_simulation.x",
                                      "--input=GENERATOR_MULTIPLE_OBJECTS" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_inputGENERATOR_RANDOM) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_input_type  = e_input_type::GENERATOR_RANDOM;
    std::vector<const char*> args = { "./particle_simulation.x", "--input=GENERATOR_RANDOM" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_inputGENERATOR_RANDOM_UNIFORM) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_input_type  = e_input_type::GENERATOR_RANDOM_UNIFORM;
    std::vector<const char*> args = { "./particle_simulation.x",
                                      "--input=GENERATOR_RANDOM_UNIFORM" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_inputGENERATOR_SINGLE_OBJECT_MIDDLE) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_input_type  = e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE;
    std::vector<const char*> args = { "./particle_simulation.x",
                                      "--input=GENERATOR_SINGLE_OBJECT_MIDDLE" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_outputFILE_CSV) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_output_type = e_output_type::FILE_CSV;
    std::vector<const char*> args = { "./particle_simulation.x", "--output=FILE_CSV" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_outputFILE_ESPRESSO) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_output_type = e_output_type::FILE_ESPRESSO;
    std::vector<const char*> args = { "./particle_simulation.x", "--output=FILE_ESPRESSO" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_outputFILE_GROMACS) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_output_type = e_output_type::FILE_GROMACS;
    std::vector<const char*> args = { "./particle_simulation.x", "--output=FILE_GROMACS" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_outputFILE_LAMMPS) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_output_type = e_output_type::FILE_LAMMPS;
    std::vector<const char*> args = { "./particle_simulation.x", "--output=FILE_LAMMPS" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_outputFILE_VMD) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_output_type = e_output_type::FILE_VMD;
    std::vector<const char*> args = { "./particle_simulation.x", "--output=FILE_VMD" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_outputFILE_VTK) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_output_type = e_output_type::FILE_VTK;
    std::vector<const char*> args = { "./particle_simulation.x", "--output=FILE_VTK" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_autotuneing) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_autotuneing = true;
    std::vector<const char*> args = { "./particle_simulation.x", "--autotuneing" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_bounds) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_bounds      = Vec3f (1, 2, 3);
    std::vector<const char*> args = { "./particle_simulation.x", "--bounds=(1/2/3)" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_count) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_particle_count = 543;
    std::vector<const char*> args    = { "./particle_simulation.x", "--count=543" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_write_fequency) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_write_fequency = 543;
    std::vector<const char*> args    = { "./particle_simulation.x", "--write_fequency=543" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_in_file_name) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_in_file_name = std::string ("abc.csv");
    std::vector<const char*> args  = { "./particle_simulation.x", "--in_file_name=abc.csv" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (options_compare.m_in_file_name, options_test.m_in_file_name);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_out_file_name) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_out_file_name = std::string ("abc.csv");
    std::vector<const char*> args   = { "./particle_simulation.x", "--out_file_name=abc.csv" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (options_compare.m_out_file_name, options_test.m_out_file_name);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_run_time_limit) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_max_iterations = 401;
    options_compare.m_timestep       = 0.5;
    std::vector<const char*> args    = { "./particle_simulation.x",
                                      "--run_time_limit=200.5",
                                      "--timestep=0.5" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_max_iterations) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_max_iterations = 543;
    std::vector<const char*> args    = { "./particle_simulation.x", "--max_iterations=543" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_cut_off_radius) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_cut_off_radius = 543.4;
    std::vector<const char*> args    = { "./particle_simulation.x", "--cut_off_radius=543.4" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_seed) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_seed        = 543;
    std::vector<const char*> args = { "./particle_simulation.x", "--seed=543" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_timestep) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_timestep    = 543;
    std::vector<const char*> args = { "./particle_simulation.x", "--timestep=543" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_verbose) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_verbose     = true;
    std::vector<const char*> args = { "./particle_simulation.x", "--verbose" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_max_iterations_between_datastructure_rebuild) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_max_iterations_between_datastructure_rebuild = 543;
    std::vector<const char*> args                                  = { "./particle_simulation.x",
                                      "--max_iterations_between_datastructure_rebuild=543" };
    int res = handler.handle_options ((int) args.size (),
                                      const_cast<char**> (const_cast<char**> (args.data ())),
                                      options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_help1) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    std::vector<const char*> args = { "./particle_simulation.x", "--help" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (res, 1);
}
BOOST_AUTO_TEST_CASE (test_help2) {
    OptionHandler            handler;
    s_options                options_test;
    std::vector<const char*> args = { "./particle_simulation.x",
                                      "--help=algorithm",
                                      "--help=data_structure",
                                      "--help=input",
                                      "--help=output",
                                      "--help=autotuneing",
                                      "--help=bounds",
                                      "--help=count",
                                      "--help=write_fequency",
                                      "--help=in_file_name",
                                      "--help=run_time_limit",
                                      "--help=max_iterations",
                                      "--help=out_file_name",
                                      "--help=cut_off_radius",
                                      "--help=seed",
                                      "--help=timestep",
                                      "--help=verbose",
                                      "--help=max_iterations_between_datastructure_rebuild",
                                      "--help=load_config",
                                      "--help=save_config",
                                      "--help=print_config"
                                      "--help=this_option_does_not_exist",
                                      "--help=print_config" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (res, 1);
}
BOOST_AUTO_TEST_CASE (test_print_config) {
    OptionHandler            handler;
    s_options                options_test;
    std::vector<const char*> args = { "./particle_simulation.x",
                                      "--algorithm=LENNARD_JONES",
                                      "--data_structure=GRID",
                                      "--output=FILE_CSV",
                                      "--input=GENERATOR_SINGLE_OBJECT_MIDDLE",
                                      "--WRITE_ID",
                                      "--WRITE_VELOCITY",
                                      "--WRITE_POSITION",
                                      "--WRITE_ACCELERATION",
                                      "--WRITE_PARTICLE_TYPE",
                                      "--print_config" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (res, 0);
}
BOOST_AUTO_TEST_CASE (test_invalid_value) {
    OptionHandler handler;
    s_options     options_test;
    memset (&options_test, 0, sizeof (s_options));
    s_options options_compare;
    memset (&options_compare, 0, sizeof (s_options));
    options_compare.m_algorithm_type=static_cast<e_algorithm_type>(-1);
    std::vector<const char*> args    = { "./particle_simulation.x", "--algorithm=this_value_does_not_exist" };
    int res = handler.handle_options ((int) args.size (), const_cast<char**> (args.data ()), options_test);
    BOOST_CHECK_EQUAL (memcmp (&options_test, &options_compare, sizeof (s_options)), 0);
    BOOST_CHECK_EQUAL (res, 0);
}
