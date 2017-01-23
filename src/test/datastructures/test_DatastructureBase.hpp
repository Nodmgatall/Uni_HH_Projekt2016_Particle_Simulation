/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */
#ifndef BOOST_TEST_DYN_LINK
// this code is never executed !! -->>
#include "datastructures/DatastructureGrid.hpp"
typedef DatastructureGrid DatastructureUnderTest;
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "DatastructureBaseGrid"
//<<-- this code is never executed !!
#endif
#include "algorithms/AlgorithmBase.hpp"
#include "borders/BorderBase.hpp"
#include "io/output/WriterBase.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
class ParticleWriter : public WriterBase {
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
};
BOOST_AUTO_TEST_CASE (test_run_simulation_iteration_1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_particle_count = 999999999;
    options.m_bounds         = Vec3f (3, 3, 3);
    options.m_cut_off_radius = 1;
    options.m_timestep       = 1;
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticleWriter         writer = ParticleWriter (0);
    DatastructureUnderTest particlesGrid (options, border, algorithm, writer);
    std::vector<Vec3f>     allParticles;
    int                    count = 0;
    {
        Vec3f vec = Vec3f (0.5, 0.5, 0.5);
        allParticles.push_back (vec);
        particlesGrid.add_particle (vec, Vec3f (count--, 0, 0) + vec, 0);
    }
    {
        Vec3f vec = Vec3f (0.6, 0.5, 0.5);
        allParticles.push_back (vec);
        particlesGrid.add_particle (vec, Vec3f (count--, 0, 0) + vec, 1);
    }
    {
        Vec3f vec = Vec3f (0.76, 0.5, 0.5);
        allParticles.push_back (vec);
        particlesGrid.add_particle (vec, Vec3f (count--, 0, 0) + vec, 2);
    }
    {
        Vec3f vec = Vec3f (2.8, 0.5, 0.5);
        allParticles.push_back (vec);
        particlesGrid.add_particle (vec, Vec3f (count--, 0, 0) + vec, 3);
    }
    algorithm.test_prepare (-count);
    BOOST_CHECK_EQUAL (particlesGrid.get_particle_count (), -count);
    particlesGrid.run_simulation_iteration (0);
    for (unsigned int i = 0; i < allParticles.size (); i++) {
        BOOST_CHECK_EQUAL (algorithm.m_step_1_helper[i], 1);
        BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[i][i], 0);
        for (unsigned int j = i + 1; j < allParticles.size (); j++) {
            float distance = (allParticles[i] - allParticles[j]).length ();
            if (distance < options.m_cut_off_radius) {
                BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[i][j], 1);
                BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[j][i], 1);
            }
        }
    }
    printf ("target\n");
    for (unsigned int i = 0; i < allParticles.size (); i++) {
        for (unsigned int j = 0; j < allParticles.size (); j++) {
            float distance = (allParticles[i] - allParticles[j]).length ();
            int   current  = (distance < options.m_cut_off_radius) && (i != j);
            printf ("%d", current);
        }
        printf ("\n");
    }
    printf ("current\n");
    for (unsigned int i = 0; i < allParticles.size (); i++) {
        for (unsigned int j = 0; j < allParticles.size (); j++) {
            int current = algorithm.m_step_2_helper[i][j] != 0;
            printf ("%d", current);
        }
        printf ("\n");
    }
}
BOOST_AUTO_TEST_CASE (test_run_simulation_iteration_2) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    int size                 = 3;
    options.m_particle_count = 999999999;
    options.m_bounds         = Vec3f (size, size, size);
    options.m_cut_off_radius = 1;
    options.m_timestep       = 1;
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticleWriter         writer = ParticleWriter (0);
    DatastructureUnderTest particlesGrid (options, border, algorithm, writer);
    std::vector<Vec3f>     allParticles;
    int                    count = 0;
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            for (int z = 0; z < 5; z++) {
                Vec3f vec = (Vec3f (x, y, z) / 4.0 * (size - 0.05)) + 0.0025;
                allParticles.push_back (vec);
                particlesGrid.add_particle (vec, Vec3f (count--, 0, 0) + vec);
            }
        }
    }
    algorithm.test_prepare (-count);
    particlesGrid.run_simulation_iteration (0);
    BOOST_CHECK_EQUAL (particlesGrid.get_particle_count (), -count);
    for (unsigned int i = 0; i < allParticles.size (); i++) {
        BOOST_CHECK_EQUAL (algorithm.m_step_1_helper[i], 1);
        BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[i][i], 0);
        for (unsigned int j = i + 1; j < allParticles.size (); j++) {
            float distance = (allParticles[i] - allParticles[j]).length ();
            BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[i][j], algorithm.m_step_2_helper[j][i]);
            if (distance < options.m_cut_off_radius) {
                if (algorithm.m_step_2_helper[i][j] != 1) { // error
                    BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[i][j], 1);
                    std::stringstream tmp;
                    tmp << DEBUG_VAR (i);
                    tmp << DEBUG_VAR (j);
                    tmp << DEBUG_VAR (allParticles[i]);
                    tmp << DEBUG_VAR (allParticles[j]);
                    tmp << DEBUG_VAR (algorithm.m_step_2_helper[i][j]);
                    BOOST_CHECK_MESSAGE (0, tmp.str ().c_str ());
                }
            } else {
                BOOST_CHECK_GE (algorithm.m_step_2_helper[i][j], 0); // this should really never
                                                                     // fail
                BOOST_CHECK_LE (algorithm.m_step_2_helper[i][j], 1); // interactions between
                                                                     // particles must not be
                                                                     // calculated more than once
            }
        }
    }
    printf ("target\n");
    for (unsigned int i = 0; i < allParticles.size (); i++) {
        for (unsigned int j = 0; j < allParticles.size (); j++) {
            float distance = (allParticles[i] - allParticles[j]).length ();
            int   target   = (distance < options.m_cut_off_radius) && (i != j);
            printf ("%d", target);
        }
        printf ("\n");
    }
    printf ("current\n");
    for (unsigned int i = 0; i < allParticles.size (); i++) {
        for (unsigned int j = 0; j < allParticles.size (); j++) {
            int current = algorithm.m_step_2_helper[i][j];
            printf ("%d", current);
        }
        printf ("\n");
    }
}
BOOST_AUTO_TEST_CASE (test_serialize) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    int size                 = 4;
    int count_3              = 5;
    options.m_bounds         = Vec3f (size, size, size);
    options.m_cut_off_radius = 1;
    options.m_timestep       = 1;
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticleWriter         writer = ParticleWriter (count_3 * count_3 * count_3);
    DatastructureUnderTest particlesGrid (options, border, algorithm, writer);
    std::vector<Vec3f>     allParticles;
    std::vector<Vec3l>     allParticlesIndicees;
    int                    count = 0;
    for (int x = 0; x < count_3; x++) {
        for (int y = 0; y < count_3; y++) {
            for (int z = 0; z < count_3; z++) {
                Vec3f vec = Vec3f (x, y, z) * 0.5;
                allParticles.push_back (vec);
                allParticlesIndicees.push_back (Vec3l ());
                particlesGrid.add_particle (vec, Vec3f (count--, 0, 0) + vec);
            }
        }
    }
    particlesGrid.serialize ();
    for (int i = 0; i < count_3 * count_3 * count_3; i++) {
        BOOST_CHECK_EQUAL (writer.m_ids_saved[i], 1);
    }
}
