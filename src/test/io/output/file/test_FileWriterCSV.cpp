/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "FileWriterCSV"
#include "io/output/file/FileWriterCSV.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (test1) {
    std::map<e_csv_column_type, bool> write_modes = { { e_csv_column_type::ID, true },
                                                      { e_csv_column_type::POSITION, true },
                                                      { e_csv_column_type::VELOCITY, false },
                                                      { e_csv_column_type::ACCELERATION, false },
                                                      { e_csv_column_type::PARTICLE_TYPE, false } };
    FileWriterCSV writer (write_modes, "test_FileWriterCSV.test1.tmp.");
    writer.start ();
    writer.end ();
}
