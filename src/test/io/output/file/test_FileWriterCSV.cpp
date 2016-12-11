/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "FileWriterCSV"
#include "io/output/file/FileWriterCSV.hpp"
#include "string"
#include <boost/test/unit_test.hpp>
void compareFiles (std::string name) {
    std::ifstream               ifs1 ("../Temporary/" + name);
    std::ifstream               ifs2 ("../Resources/" + name);
    std::istream_iterator<char> b1 (ifs1), e1;
    std::istream_iterator<char> b2 (ifs2), e2;
    BOOST_CHECK_EQUAL_COLLECTIONS (b1, e1, b2, e2);
}

BOOST_AUTO_TEST_CASE (test1) {
    std::map<e_csv_column_type, bool> write_modes = { { e_csv_column_type::ID, true },
                                                      { e_csv_column_type::POSITION, true },
                                                      { e_csv_column_type::VELOCITY, false },
                                                      { e_csv_column_type::ACCELERATION, false },
                                                      { e_csv_column_type::PARTICLE_TYPE, false } };
    FileWriterCSV writer (write_modes, "../Temporary/test_FileWriterCSV.test1.tmp.");
    writer.start ();
    writer.end ();
    compareFiles ("test_FileWriterCSV.test1.tmp.0.csv");
}
