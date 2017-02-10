/*
 * test_FileReaderCSV.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "FileReaderCSV"
#include "borders/BorderWrapparound.hpp"
#include "string"
#include <algorithms/AlgorithmStoermerVerletLennardJones.hpp>
#include <boost/test/unit_test.hpp>
#include <io/input/file/FileInputCSV.hpp>
class ParticleWriter : public OutputBase {
  public:
    void saveData (std::vector<data_type>& p_positions_x, std::vector<data_type>& p_positions_y, std::vector<data_type>& p_positions_z, std::vector<unsigned long>& p_ids) {
        (void) p_positions_x;
        (void) p_positions_y;
        (void) p_positions_z;
        (void) p_ids;
    }
    ParticleWriter () {
    }
    void start () {
    }
    void end () {
    }
    void finalize () {
    }
};
class Datastructure : public DatastructureBase {
  public:
    std::vector<data_type>     positions_x;
    std::vector<data_type>     positions_y;
    std::vector<data_type>     positions_z;
    std::vector<data_type>     velocities_x;
    std::vector<data_type>     velocities_y;
    std::vector<data_type>     velocities_z;
    std::vector<unsigned long> ids;
    int                        m_particle_count;
    Datastructure (s_options& p_options, BorderBase& p_particle_bounds_correction, AlgorithmBase& p_algorithm, OutputBase& p_particle_file_writer)
    : DatastructureBase (p_options, p_particle_bounds_correction, p_algorithm, p_particle_file_writer), m_particle_count (0) {
    }
    ~Datastructure () {
    }
    void serialize () {
    }
    bool run_simulation_iteration (unsigned long p_iteration_number = 0) {
        (void) p_iteration_number;
        return true;
    }
    void add_particle (Vec3f p_current_position) {
        m_particle_count++;
        positions_x.push_back (p_current_position.x);
        positions_y.push_back (p_current_position.y);
        positions_z.push_back (p_current_position.z);
        velocities_x.push_back (-1);
        velocities_y.push_back (-1);
        velocities_z.push_back (-1);
        ids.push_back (-1);
    }
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id = -1) {
        m_particle_count++;
        positions_x.push_back (p_current_position.x);
        positions_y.push_back (p_current_position.y);
        positions_z.push_back (p_current_position.z);
        velocities_x.push_back (p_current_velocity.x);
        velocities_y.push_back (p_current_velocity.y);
        velocities_z.push_back (p_current_velocity.z);
        ids.push_back (p_id);
    }
    unsigned long get_particle_count () {
        return m_particle_count;
    }
};
BOOST_AUTO_TEST_CASE (test1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_particle_count = 10;
    options.m_bounds         = Vec3f (10, 10, 10);
    options.m_in_file_name   = "../Resources/test1.csv";
    BorderWrapparound                   border (options.m_bounds);
    AlgorithmStoermerVerletLennardJones algorithm (options);
    ParticleWriter                      writer        = ParticleWriter ();
    Datastructure                       datastructure = Datastructure (options, border, algorithm, writer);
    FileInputCSV                        reader (options, datastructure);
    reader.initialize_datastructure ();
    BOOST_CHECK_EQUAL (datastructure.get_particle_count (), 0);
}
BOOST_AUTO_TEST_CASE (test2) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_particle_count = 10;
    options.m_bounds         = Vec3f (10, 10, 10);
    options.m_in_file_name   = "../Resources/test2.csv";
    BorderWrapparound                   border (options.m_bounds);
    AlgorithmStoermerVerletLennardJones algorithm (options);
    ParticleWriter                      writer        = ParticleWriter ();
    Datastructure                       datastructure = Datastructure (options, border, algorithm, writer);
    FileInputCSV                        reader (options, datastructure);
    reader.initialize_datastructure ();
    BOOST_CHECK_EQUAL (datastructure.get_particle_count (), 10);
    for (int i = 0; i < 40; i += 4) {
        BOOST_CHECK_EQUAL (datastructure.positions_x[i / 4], i + 0.5);
        BOOST_CHECK_EQUAL (datastructure.positions_y[i / 4], i + 1.5);
        BOOST_CHECK_EQUAL (datastructure.positions_z[i / 4], i + 2.5);
        BOOST_CHECK_EQUAL (datastructure.velocities_x[i / 4], 0);
        BOOST_CHECK_EQUAL (datastructure.velocities_y[i / 4], 0);
        BOOST_CHECK_EQUAL (datastructure.velocities_z[i / 4], 0);
        BOOST_CHECK_EQUAL (datastructure.ids[i / 4], i + 3);
    }
}
