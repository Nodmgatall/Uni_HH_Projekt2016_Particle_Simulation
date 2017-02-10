/*
 * test_FileWriterCSV.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "FileWriterCSV"
#include "io/output/file/FileWriterCSV.hpp"
#include "options/Options.hpp"
#include "string"
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_CASE (test1) {
    s_options options_test;
    options_test.m_write_modes = { e_csv_column_type::ID, e_csv_column_type::POSITION, e_csv_column_type::VELOCITY };
    FileWriterCSV writer (options_test, "../Temporary/test_FileWriterCSV.test1.tmp.");
    writer.start ();
    writer.end ();
    //
    std::ifstream               ifs1 ("../Temporary/test1.csv");
    std::ifstream               ifs2 ("../Resources/test_FileWriterCSV.test1.tmp.0.csv");
    std::istream_iterator<char> b1 (ifs1), e1;
    std::istream_iterator<char> b2 (ifs2), e2;
    BOOST_CHECK_EQUAL_COLLECTIONS (b1, e1, b2, e2);
}
BOOST_AUTO_TEST_CASE (test2) {
    s_options options_test;
    options_test.m_write_modes = { e_csv_column_type::ID, e_csv_column_type::POSITION, e_csv_column_type::VELOCITY };
    FileWriterCSV writer (options_test, "../Temporary/test_FileWriterCSV.test2.tmp.");
    writer.start ();
    std::vector<data_type>     positions_x;
    std::vector<data_type>     positions_y;
    std::vector<data_type>     positions_z;
    std::vector<unsigned long> ids;
    for (int i = 0; i < 40; i += 4) {
        positions_x.push_back (i + 0.5);
        positions_y.push_back (i + 1.5);
        positions_z.push_back (i + 2.5);
        ids.push_back (i + 3);
    }
    writer.saveData (positions_x, positions_y, positions_z, ids);
    writer.end ();
    //
    std::ifstream               ifs1 ("../Temporary/test2.csv");
    std::ifstream               ifs2 ("../Resources/test_FileWriterCSV.test2.tmp.0.csv");
    std::istream_iterator<char> b1 (ifs1), e1;
    std::istream_iterator<char> b2 (ifs2), e2;
    BOOST_CHECK_EQUAL_COLLECTIONS (b1, e1, b2, e2);
}
