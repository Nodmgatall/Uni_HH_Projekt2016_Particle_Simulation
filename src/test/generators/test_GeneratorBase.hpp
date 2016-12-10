/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#ifndef BOOST_TEST_DYN_LINK
// this code is never executed !! -->>
#include "../../main/io/input/generators/GeneratorRandom.hpp"
typedef GeneratorRandom GeneratorUnderTest;
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "GeneratorRandom"
//<<-- this code is never executed !!
#endif
#include "../../main/algorithms/AlgorithmLennardJones.hpp"
#include "../../main/borders/BorderWrapparound.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

class ParticleWriter : public ParticleWriterBase {
  public:
    void saveData (std::vector<data_type>&     p_positions_x,
                   std::vector<data_type>&     p_positions_y,
                   std::vector<data_type>&     p_positions_z,
                   std::vector<unsigned long>& p_ids) {
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
};

class Particles : public DatastructureBase {
  public:
    int m_particle_count;
    Particles (s_options&          p_options,
               BorderBase&         p_particle_bounds_correction,
               AlgorithmBase&      p_algorithm,
               ParticleWriterBase& p_particle_file_writer)
    : DatastructureBase (p_options, p_particle_bounds_correction, p_algorithm, p_particle_file_writer),
      m_particle_count (0) {
    }
    ~Particles () {
    }
    void serialize () {
    }
    void run_simulation_iteration (unsigned long p_iteration_number = 0) {
        (void) p_iteration_number;
    }
    void add_particle (Vec3f p_current_position) {
        m_particle_count++;
        BOOST_CHECK_GE (p_current_position.x, 0);
        BOOST_CHECK_GE (p_current_position.y, 0);
        BOOST_CHECK_GE (p_current_position.z, 0);
        BOOST_CHECK_LE (p_current_position.x, m_options.m_bounds.x);
        BOOST_CHECK_LE (p_current_position.y, m_options.m_bounds.y);
        BOOST_CHECK_LE (p_current_position.z, m_options.m_bounds.z);
    }
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity) {
        (void) p_current_velocity;
        m_particle_count++;
        BOOST_CHECK_GE (p_current_position.x, 0);
        BOOST_CHECK_GE (p_current_position.y, 0);
        BOOST_CHECK_GE (p_current_position.z, 0);
        BOOST_CHECK_LE (p_current_position.x, m_options.m_bounds.x);
        BOOST_CHECK_LE (p_current_position.y, m_options.m_bounds.y);
        BOOST_CHECK_LE (p_current_position.z, m_options.m_bounds.z);
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
    GeneratorUnderTest    generator (options);
    BorderWrapparound     border (options.m_bounds);
    AlgorithmLennardJones algorithm (options);
    ParticleWriter        writer    = ParticleWriter ();
    Particles*            particles = new Particles (options, border, algorithm, writer);
    generator.generate (particles);
    BOOST_CHECK_EQUAL (particles->get_particle_count (), 10L);
}
