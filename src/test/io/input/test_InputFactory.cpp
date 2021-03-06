/*
 * test_InputFactory.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "AlgorithmFactory"
#include "io/input/InputFactory.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
class ParticleWriter : public OutputBase {
  public:
    bool             m_start_called;
    bool             m_end_called;
    std::vector<int> m_ids_saved;
    void saveData (std::vector<data_type>& p_positions_x, std::vector<data_type>& p_positions_y, std::vector<data_type>& p_positions_z, std::vector<unsigned long>& p_ids) {
        (void) p_positions_x;
        (void) p_positions_y;
        (void) p_positions_z;
        for (unsigned int i = 0; i < p_ids.size (); i++)
            m_ids_saved[p_ids[i]]++;
    }
    ParticleWriter (int p_expected_max_id) : m_start_called (false), m_end_called (true) {
        m_ids_saved.reserve (p_expected_max_id);
        for (int i = 0; i < p_expected_max_id; i++) {
            m_ids_saved.push_back (0);
        }
    }
    void start () {
        BOOST_CHECK_EQUAL (m_end_called, true);
        BOOST_CHECK_EQUAL (m_start_called, false);
        m_start_called = true;
        m_end_called   = false;
    }
    void end () {
        BOOST_CHECK_EQUAL (m_end_called, false);
        BOOST_CHECK_EQUAL (m_start_called, true);
        m_end_called   = true;
        m_start_called = false;
    }
    void finalize () {
    }
};
class Algorithm : public AlgorithmBase {
  public:
    std::vector<int>              m_step_1_helper;
    std::vector<std::vector<int>> m_step_2_helper;
    int                           m_count;
    Algorithm (s_options& p_options) : AlgorithmBase (p_options), m_count (0) {
    }
    void step_1 (const data_type& p_position_ax, const data_type& p_position_ay, const data_type& p_position_az, data_type& p_position_bx, data_type& p_position_by, data_type& p_position_bz) {
        int idx_i = p_position_bx;
        m_step_1_helper[idx_i]++;
        BOOST_CHECK_EQUAL (m_step_1_helper[idx_i], 1);
        m_count++;
        (void) p_position_ax;
        (void) p_position_ay;
        (void) p_position_az;
        (void) p_position_bx;
        (void) p_position_by;
        (void) p_position_bz;
    }
    void test_prepare (int p_count) {
        m_step_1_helper.clear ();
        m_step_1_helper.reserve (p_count);
        for (int i = 0; i < p_count; i++) {
            m_step_1_helper.push_back (0);
        }
        m_step_2_helper.clear ();
        m_step_2_helper.reserve (p_count);
        for (int i = 0; i < p_count; i++) {
            m_step_2_helper.push_back (std::vector<int> ());
            m_step_2_helper[i].reserve (p_count);
            for (int j = 0; j < p_count; j++) {
                m_step_2_helper[i].push_back (0);
            }
        }
    }
    void step_2_offset (const data_type&       p_offset_position_aix,
                        const data_type&       p_offset_position_aiy,
                        const data_type&       p_offset_position_aiz,
                        const data_type&       p_position_aix,
                        const data_type&       p_position_aiy,
                        const data_type&       p_position_aiz,
                        data_type&             p_position_bix,
                        data_type&             p_position_biy,
                        data_type&             p_position_biz,
                        const data_type* const p_position_ajx,
                        const data_type* const p_position_ajy,
                        const data_type* const p_position_ajz,
                        data_type* const       p_position_bjx,
                        data_type* const       p_position_bjy,
                        data_type* const       p_position_bjz,
                        const unsigned long    p_index_j_begin,
                        const unsigned long    p_index_j_end) {
        (void) p_offset_position_aix;
        (void) p_offset_position_aiy;
        (void) p_offset_position_aiz;
        (void) p_position_aix;
        (void) p_position_aiy;
        (void) p_position_aiz;
        (void) p_position_bix;
        (void) p_position_biy;
        (void) p_position_biz;
        (void) p_position_ajx;
        (void) p_position_ajy;
        (void) p_position_ajz;
        (void) p_position_bjx;
        (void) p_position_bjy;
        (void) p_position_bjz;
        int idx_i = p_position_bix;
        BOOST_CHECK_EQUAL (m_step_1_helper[idx_i], 1);
        for (unsigned long j = p_index_j_begin; j < p_index_j_end; j++) {
            int idx_j = p_position_bjx[j];
            m_step_2_helper[idx_i][idx_j]++;
            m_step_2_helper[idx_j][idx_i]++;
            BOOST_CHECK_EQUAL (m_step_1_helper[idx_j], 1);
        }
    }
    void step_2 (const data_type&       p_position_aix,
                 const data_type&       p_position_aiy,
                 const data_type&       p_position_aiz,
                 data_type&             p_position_bix,
                 data_type&             p_position_biy,
                 data_type&             p_position_biz,
                 const data_type* const p_position_ajx,
                 const data_type* const p_position_ajy,
                 const data_type* const p_position_ajz,
                 data_type* const       p_position_bjx,
                 data_type* const       p_position_bjy,
                 data_type* const       p_position_bjz,
                 const unsigned long    p_index_j_begin,
                 const unsigned long    p_index_j_end) {
        (void) p_position_aix;
        (void) p_position_aiy;
        (void) p_position_aiz;
        (void) p_position_bix;
        (void) p_position_biy;
        (void) p_position_biz;
        (void) p_position_ajx;
        (void) p_position_ajy;
        (void) p_position_ajz;
        (void) p_position_bjx;
        (void) p_position_bjy;
        (void) p_position_bjz;
        int idx_i = p_position_bix;
        BOOST_CHECK_EQUAL (m_step_1_helper[idx_i], 1);
        for (unsigned long j = p_index_j_begin; j < p_index_j_end; j++) {
            int idx_j = p_position_bjx[j];
            m_step_2_helper[idx_i][idx_j]++;
            m_step_2_helper[idx_j][idx_i]++;
            BOOST_CHECK_EQUAL (m_step_1_helper[idx_j], 1);
        }
    }
};
class BoundsCorrection : public BorderBase {
  public:
    int m_call_count;
    BoundsCorrection (Vec3f& p_bounds) : BorderBase (p_bounds), m_call_count (0) {
    }
    virtual ~BoundsCorrection () {
    }
    bool updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z, const Vec3f& m_corner000, const Vec3f& m_corner111) {
        (void) m_x;
        (void) m_y;
        (void) m_z;
        (void) m_other_x;
        (void) m_other_y;
        (void) m_other_z;
        (void) m_corner000;
        (void) m_corner111;
        return true;
    }
    bool updatePosition (data_type& m_x, data_type& m_y, data_type& m_z, data_type& m_other_x, data_type& m_other_y, data_type& m_other_z) {
        m_call_count++;
        (void) m_x;
        (void) m_y;
        (void) m_z;
        (void) m_other_x;
        (void) m_other_y;
        (void) m_other_z;
        return true;
    }
    bool updatePosition (ParticleGroup& p_cell, int p_idx_a, bool& p_error_happened) {
        (void) p_cell;
        (void) p_idx_a;
        (void) p_error_happened;
        return true;
    }
};
class Datastructure : public DatastructureBase {
  public:
    int m_particle_count;
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
        BOOST_CHECK_GE (p_current_position.x, 0);
        BOOST_CHECK_GE (p_current_position.y, 0);
        BOOST_CHECK_GE (p_current_position.z, 0);
        BOOST_CHECK_LE (p_current_position.x, m_options.m_bounds.x);
        BOOST_CHECK_LE (p_current_position.y, m_options.m_bounds.y);
        BOOST_CHECK_LE (p_current_position.z, m_options.m_bounds.z);
    }
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id = -1) {
        (void) p_current_velocity;
        (void) p_id;
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
    options.m_input_type = e_input_type::FILE_CSV;
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer    = ParticleWriter (0);
    Datastructure    particles = Datastructure (options, border, algorithm, writer);
    BOOST_CHECK_EQUAL (InputFactory::build (options, particles)->get_structure_name (), "FileInputCSV");
}
BOOST_AUTO_TEST_CASE (test2) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::GENERATOR_GRID_DISTRIBUTION;
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer    = ParticleWriter (0);
    Datastructure    particles = Datastructure (options, border, algorithm, writer);
    BOOST_CHECK_EQUAL (InputFactory::build (options, particles)->get_structure_name (), "GeneratorGridDistribution");
}
BOOST_AUTO_TEST_CASE (test4) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::GENERATOR_RANDOM;
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer    = ParticleWriter (0);
    Datastructure    particles = Datastructure (options, border, algorithm, writer);
    BOOST_CHECK_EQUAL (InputFactory::build (options, particles)->get_structure_name (), "GeneratorRandom");
}
BOOST_AUTO_TEST_CASE (test6) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_input_type = e_input_type::GENERATOR_SINGLE_OBJECT_MIDDLE;
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer    = ParticleWriter (0);
    Datastructure    particles = Datastructure (options, border, algorithm, writer);
    BOOST_CHECK_EQUAL (InputFactory::build (options, particles)->get_structure_name (), "GeneratorSingleObjectMiddle");
}
BOOST_AUTO_TEST_CASE (test7) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer    = ParticleWriter (0);
    Datastructure    particles = Datastructure (options, border, algorithm, writer);
    BOOST_CHECK_THROW (InputFactory::build (options, particles), InputTypeInvalidException);
}
