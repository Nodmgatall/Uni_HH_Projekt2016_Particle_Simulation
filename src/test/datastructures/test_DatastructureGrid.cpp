/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticlesGrid"
#include "../../main/IO/ParticleWriterBase.hpp"
#include "../../main/algorithms/AlgorithmBase.hpp"
#include "../../main/borders/BorderBase.hpp"
#include "../../main/datastructures/DatastructureGrid.hpp"
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

class Algorithm : public AlgorithmBase {
  public:
    std::vector<int>              m_step_1_helper;
    std::vector<std::vector<int>> m_step_2_helper;
    int                           m_count;

    Algorithm (s_options& p_options) : AlgorithmBase (p_options), m_count (0) {
    }
    void step_1 (const data_type& p_position_ax,
                 const data_type& p_position_ay,
                 const data_type& p_position_az,
                 data_type&       p_position_bx,
                 data_type&       p_position_by,
                 data_type&       p_position_bz) {
        BOOST_CHECK_EQUAL (p_position_ax, p_position_ay - 1);
        BOOST_CHECK_EQUAL (p_position_ay, p_position_az - 1);
        BOOST_CHECK_EQUAL (p_position_bx, p_position_by - 1);
        BOOST_CHECK_EQUAL (p_position_by, p_position_bz - 1);
        int idx_i = 0;
        if (p_position_ax > p_position_bx) {
            idx_i = (int) p_position_bx - 1;
            BOOST_CHECK_EQUAL (p_position_ax, p_position_bx + 10);
        } else {
            idx_i = (int) p_position_ax - 1;
            BOOST_CHECK_EQUAL (p_position_ax, p_position_bx - 10);
        }
        m_step_1_helper.push_back (idx_i);
        m_count++;
    }
    void test_prepare_step_2 (int p_count) {
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
        BOOST_CHECK_EQUAL (p_position_aix, p_position_aiy - 1);
        BOOST_CHECK_EQUAL (p_position_aiy, p_position_aiz - 1);
        BOOST_CHECK_EQUAL (p_position_bix, p_position_biy - 1);
        BOOST_CHECK_EQUAL (p_position_biy, p_position_biz - 1);
        int idx_i = 0;
        if (p_position_aix > p_position_bix) {
            idx_i = (int) p_position_bix - 1;
            BOOST_CHECK_EQUAL (p_position_aix, p_position_bix + 10);
        } else {
            idx_i = (int) p_position_aix - 1;
            BOOST_CHECK_EQUAL (p_position_aix, p_position_bix - 10);
        }
        for (unsigned long j = p_index_j_begin; j < p_index_j_end; j++) {
            BOOST_CHECK_EQUAL (p_position_ajx[j], p_position_ajy[j] - 1);
            BOOST_CHECK_EQUAL (p_position_ajy[j], p_position_ajz[j] - 1);
            BOOST_CHECK_EQUAL (p_position_bjx[j], p_position_bjy[j] - 1);
            BOOST_CHECK_EQUAL (p_position_bjy[j], p_position_bjz[j] - 1);
            int idx_j = 0;
            if (p_position_ajx[j] > p_position_bjx[j]) {
                idx_j = (int) p_position_bjx[j] - 1;
                BOOST_CHECK_EQUAL (p_position_ajx[j], p_position_bjx[j] + 10);
            } else {
                idx_j = (int) p_position_ajx[j] - 1;
                BOOST_CHECK_EQUAL (p_position_ajx[j], p_position_bjx[j] - 10);
            }
            m_step_2_helper[idx_i][idx_j]++;
            m_step_2_helper[idx_j][idx_i]++;
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
    bool updatePosition (data_type&   m_x,
                         data_type&   m_y,
                         data_type&   m_z,
                         data_type&   m_other_x,
                         data_type&   m_other_y,
                         data_type&   m_other_z,
                         const Vec3f& m_corner000,
                         const Vec3f& m_corner111) {
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
        if (m_x < 0) {
            m_x += m_bounds.x;
            m_other_x += m_bounds.x;
        }
        if (m_y < 0) {
            m_y += m_bounds.y;
            m_other_y += m_bounds.y;
        }
        if (m_z < 0) {
            m_z += m_bounds.z;
            m_other_z += m_bounds.z;
        }
        if (m_x > m_bounds.x) {
            m_x -= m_bounds.x;
            m_other_x -= m_bounds.x;
        }
        if (m_y > m_bounds.y) {
            m_y -= m_bounds.y;
            m_other_y -= m_bounds.y;
        }
        if (m_z > m_bounds.z) {
            m_z -= m_bounds.z;
            m_other_z -= m_bounds.z;
        }
        return true;
    }
};
class DatastructureGridTestClass : public DatastructureGrid {
  public:
    unsigned long public_get_cell_index (long x, long y, long z) {
        return get_cell_index (x, y, z);
    }
    ParticleCell& public_get_cell_at (long x, long y, long z) {
        return get_cell_at (x, y, z);
    }
    ParticleCell& public_get_cell_for_particle (data_type x, data_type y, data_type z) {
        return get_cell_for_particle (x, y, z);
    }
    ParticleCell& public_get_cell_for_particle (Vec3f m_position) {
        return get_cell_for_particle (m_position);
    }
    void public_moveParticle (ParticleCell& p_cell_from, ParticleCell& p_cell_to, long p_index_from) {
        moveParticle (p_cell_from, p_cell_to, p_index_from);
    }
    void public_step_1_prepare_cell (ParticleCell& p_cell) {
        step_1_prepare_cell (p_cell);
    }
    void public_step_2a_calculate_inside_cell (ParticleCell& p_cell) {
        step_2a_calculate_inside_cell (p_cell);
    }
    void public_step_2b_calculate_between_cells (ParticleCell& p_cell1, ParticleCell& p_cell2) {
        step_2b_calculate_between_cells (p_cell1, p_cell2);
    }
    void public_step_3_remove_wrong_particles_from_cell (ParticleCell& p_cell) {
        step_3_remove_wrong_particles_from_cell (p_cell);
    }
    DatastructureGridTestClass (s_options&          p_options,
                                BorderBase&         p_particle_bounds_correction,
                                AlgorithmBase&      p_algorithm,
                                ParticleWriterBase& p_particle_file_writer)
    : DatastructureGrid (p_options, p_particle_bounds_correction, p_algorithm, p_particle_file_writer) {
    }
    ~DatastructureGridTestClass () {
    }
    const std::vector<ParticleCell>& get_cells () {
        return m_cells;
    }
    unsigned int get_idx_a () {
        return m_idx_a;
    }
    unsigned int get_idx_b () {
        return m_idx_b;
    }
    unsigned long get_max_id () {
        return m_max_id;
    }
    const Vec3l& get_size () {
        return m_size;
    }
    const Vec3f& get_size_per_cell () {
        return m_size_per_cell;
    }
};

BOOST_AUTO_TEST_CASE (test_add_particle_1) {
    unsigned int idx_x, idx_y, idx_z, idx_s, idx_t;
    s_options    options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();

    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    Vec3f                      particles[7];
    particles[0] = Vec3f (1, 2, 3);
    particles[1] = Vec3f (-2, 2, 3);
    particles[2] = Vec3f (3, -3, 4);
    particles[3] = Vec3f (1, 2, -4);
    particles[4] = Vec3f (7, 4, 3);
    particles[5] = Vec3f (1, 8, 3);
    particles[6] = Vec3f (4, 2, 9);
    Vec3f particlesWrapped[7];
    particlesWrapped[0] = Vec3f (1, 2, 3);
    particlesWrapped[1] = Vec3f (3, 2, 3);
    particlesWrapped[2] = Vec3f (3, 2, 4);
    particlesWrapped[3] = Vec3f (1, 2, 1);
    particlesWrapped[4] = Vec3f (2, 4, 3);
    particlesWrapped[5] = Vec3f (1, 3, 3);
    particlesWrapped[6] = Vec3f (4, 2, 4);
    for (Vec3f p : particles) {
        particlesGrid.add_particle (p);
    }
    BOOST_CHECK_EQUAL (particlesGrid.get_particle_count (), 7);
    BOOST_CHECK_EQUAL (border.m_call_count, 7);
    int particlesFound[7];
    for (idx_t = 0; idx_t < 7; idx_t++) {
        particlesFound[idx_t] = 0;
    }
    for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
                ParticleCell& cell = particlesGrid.public_get_cell_at (idx_x, idx_y, idx_z);
                for (idx_s = 0; idx_s < cell.m_ids.size (); idx_s++) {
                    Vec3f position = Vec3f (cell.m_positions_x[particlesGrid.get_idx_a ()][idx_s],
                                            cell.m_positions_y[particlesGrid.get_idx_a ()][idx_s],
                                            cell.m_positions_z[particlesGrid.get_idx_a ()][idx_s]);
                    for (idx_t = 0; idx_t < 7; idx_t++) {
                        if (position == particlesWrapped[idx_t]) {
                            particlesFound[idx_t]++;
                        }
                    }
                }
            }
        }
    }
    for (idx_t = 0; idx_t < 7; idx_t++) {
        BOOST_CHECK_EQUAL (particlesFound[idx_t], 1);
    }
}
BOOST_AUTO_TEST_CASE (test_get_cell_index) {
    unsigned int idx_x, idx_y, idx_z;
    s_options    options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    int                        counter = 0;
    for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
                BOOST_CHECK_EQUAL (particlesGrid.public_get_cell_index (idx_x, idx_y, idx_z), counter++);
            }
        }
    }
}
BOOST_AUTO_TEST_CASE (test_get_cell_at) {
    unsigned int idx_x, idx_y, idx_z;
    s_options    options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    int                        counter = 0;
    for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
                ParticleCell& cell = particlesGrid.public_get_cell_at (idx_x, idx_y, idx_z);
                BOOST_CHECK_EQUAL (&cell, &particlesGrid.get_cells ()[counter++]);
            }
        }
    }
}
BOOST_AUTO_TEST_CASE (test_moveParticle) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    ParticleCell               cell1 = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
    ParticleCell               cell2 = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
    cell1.add_particle (Vec3f (1, 2, 3), Vec3f (11, 12, 13), 0, 0);
    cell1.add_particle (Vec3f (2, 3, 4), Vec3f (12, 13, 14), 0, 1);
    cell1.add_particle (Vec3f (3, 4, 5), Vec3f (13, 14, 15), 0, 2);
    particlesGrid.public_moveParticle (cell1, cell2, 1);
    BOOST_CHECK_EQUAL (cell1.m_ids.size (), 2);
    BOOST_CHECK_EQUAL (cell2.m_ids.size (), 1);
    BOOST_CHECK_EQUAL (cell1.m_positions_x[0][0], 1);
    BOOST_CHECK_EQUAL (cell1.m_positions_y[0][0], 2);
    BOOST_CHECK_EQUAL (cell1.m_positions_z[0][0], 3);
    BOOST_CHECK_EQUAL (cell1.m_positions_x[1][0], 11);
    BOOST_CHECK_EQUAL (cell1.m_positions_y[1][0], 12);
    BOOST_CHECK_EQUAL (cell1.m_positions_z[1][0], 13);
    BOOST_CHECK_EQUAL (cell1.m_ids[0], 0);
    BOOST_CHECK_EQUAL (cell1.m_positions_x[0][1], 3);
    BOOST_CHECK_EQUAL (cell1.m_positions_y[0][1], 4);
    BOOST_CHECK_EQUAL (cell1.m_positions_z[0][1], 5);
    BOOST_CHECK_EQUAL (cell1.m_positions_x[1][1], 13);
    BOOST_CHECK_EQUAL (cell1.m_positions_y[1][1], 14);
    BOOST_CHECK_EQUAL (cell1.m_positions_z[1][1], 15);
    BOOST_CHECK_EQUAL (cell1.m_ids[1], 2);
    BOOST_CHECK_EQUAL (cell2.m_positions_x[0][0], 2);
    BOOST_CHECK_EQUAL (cell2.m_positions_y[0][0], 3);
    BOOST_CHECK_EQUAL (cell2.m_positions_z[0][0], 4);
    BOOST_CHECK_EQUAL (cell2.m_positions_x[1][0], 12);
    BOOST_CHECK_EQUAL (cell2.m_positions_y[1][0], 13);
    BOOST_CHECK_EQUAL (cell2.m_positions_z[1][0], 14);
    BOOST_CHECK_EQUAL (cell2.m_ids[0], 1);
    particlesGrid.public_moveParticle (cell1, cell2, 1);
    BOOST_CHECK_EQUAL (cell1.m_ids.size (), 1);
    BOOST_CHECK_EQUAL (cell2.m_ids.size (), 2);
    BOOST_CHECK_EQUAL (cell1.m_positions_x[0][0], 1);
    BOOST_CHECK_EQUAL (cell1.m_positions_y[0][0], 2);
    BOOST_CHECK_EQUAL (cell1.m_positions_z[0][0], 3);
    BOOST_CHECK_EQUAL (cell1.m_positions_x[1][0], 11);
    BOOST_CHECK_EQUAL (cell1.m_positions_y[1][0], 12);
    BOOST_CHECK_EQUAL (cell1.m_positions_z[1][0], 13);
    BOOST_CHECK_EQUAL (cell1.m_ids[0], 0);
    BOOST_CHECK_EQUAL (cell2.m_positions_x[0][0], 2);
    BOOST_CHECK_EQUAL (cell2.m_positions_y[0][0], 3);
    BOOST_CHECK_EQUAL (cell2.m_positions_z[0][0], 4);
    BOOST_CHECK_EQUAL (cell2.m_positions_x[1][0], 12);
    BOOST_CHECK_EQUAL (cell2.m_positions_y[1][0], 13);
    BOOST_CHECK_EQUAL (cell2.m_positions_z[1][0], 14);
    BOOST_CHECK_EQUAL (cell2.m_ids[0], 1);
    BOOST_CHECK_EQUAL (cell2.m_positions_x[0][1], 3);
    BOOST_CHECK_EQUAL (cell2.m_positions_y[0][1], 4);
    BOOST_CHECK_EQUAL (cell2.m_positions_z[0][1], 5);
    BOOST_CHECK_EQUAL (cell2.m_positions_x[1][1], 13);
    BOOST_CHECK_EQUAL (cell2.m_positions_y[1][1], 14);
    BOOST_CHECK_EQUAL (cell2.m_positions_z[1][1], 15);
    BOOST_CHECK_EQUAL (cell2.m_ids[1], 2);
}
BOOST_AUTO_TEST_CASE (test_get_cell_for_particle_1) {
    unsigned int idx_x, idx_y, idx_z;
    s_options    options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    int                        counter = 0;
    for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
                ParticleCell& cell = particlesGrid.public_get_cell_for_particle (
                    5.0 / particlesGrid.get_size ().x * (float) idx_x + 0.5,
                    5.0 / particlesGrid.get_size ().y * (float) idx_y + 0.5,
                    5.0 / particlesGrid.get_size ().z * (float) idx_z + 0.5);
                BOOST_CHECK_EQUAL (&cell - particlesGrid.get_cells ().data (), counter++);
            }
        }
    }
}
BOOST_AUTO_TEST_CASE (test_get_cell_for_particle_2) {
    unsigned int idx_x, idx_y, idx_z;
    s_options    options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    int                        counter = 0;
    for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
                ParticleCell& cell = particlesGrid.public_get_cell_for_particle (
                    Vec3f (5.0 / particlesGrid.get_size ().x * (float) idx_x + 0.5,
                           5.0 / particlesGrid.get_size ().y * (float) idx_y + 0.5,
                           5.0 / particlesGrid.get_size ().z * (float) idx_z + 0.5));
                BOOST_CHECK_EQUAL (&cell - particlesGrid.get_cells ().data (), counter++);
            }
        }
    }
}
BOOST_AUTO_TEST_CASE (test_step_1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    ParticleCell               cell          = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
    const int                  particleCount = 4;
    for (int i = 0; i < particleCount; i++)
        cell.add_particle (Vec3f (i + 1, i + 2, i + 3), Vec3f (i + 11, i + 12, i + 13), 0, i);
    particlesGrid.public_step_1_prepare_cell (cell);
    BOOST_CHECK_EQUAL (algorithm.m_count, particleCount);
    int call_count[particleCount];
    for (int i = 0; i < particleCount; i++) {
        call_count[i] = 0;
    }
    for (int i = 0; i < particleCount; i++) {
        call_count[algorithm.m_step_1_helper[i]]++;
    }
    for (int i = 0; i < particleCount; i++) {
        BOOST_CHECK_EQUAL (call_count[i], 1);
    }
}
BOOST_AUTO_TEST_CASE (test_step_2a) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    ParticleCell               cell          = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
    const int                  particleCount = 4;
    for (int i = 0; i < particleCount; i++)
        cell.add_particle (Vec3f (i + 1, i + 2, i + 3), Vec3f (i + 11, i + 12, i + 13), 0, i);
    algorithm.test_prepare_step_2 (particleCount);
    particlesGrid.public_step_2a_calculate_inside_cell (cell);
    for (int i = 0; i < particleCount; i++) {
        for (int j = 0; j < particleCount; j++) {
            BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[i][j], i != j);
        }
    }
}
BOOST_AUTO_TEST_CASE (test_step_2b) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    ParticleWriter   writer = ParticleWriter ();
    ;
    DatastructureGridTestClass particlesGrid (options, border, algorithm, writer);
    ParticleCell               cell_i = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
    ParticleCell               cell_j = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
    const int                  particleCount_i = 4;
    const int                  particleCount_j = 3;
    for (int i = 0; i < particleCount_i; i++)
        cell_i.add_particle (Vec3f (i + 1, i + 2, i + 3), Vec3f (i + 11, i + 12, i + 13), 0, i);
    for (int i = particleCount_i; i < particleCount_i + particleCount_j; i++)
        cell_j.add_particle (Vec3f (i + 1, i + 2, i + 3), Vec3f (i + 11, i + 12, i + 13), 0, i);
    algorithm.test_prepare_step_2 (particleCount_i + particleCount_j);
    particlesGrid.public_step_2b_calculate_between_cells (cell_i, cell_j);
    int sum = 0;
    for (int i = 0; i < particleCount_i + particleCount_j; i++) {
        for (int j = 0; j < particleCount_i + particleCount_j; j++) {
            int cmp = 0;
            if ((i < particleCount_i) || (j < particleCount_i)) {
                if ((i >= particleCount_i) || (j >= particleCount_i)) {
                    cmp = 1;
                }
            }
            BOOST_CHECK_EQUAL (algorithm.m_step_2_helper[i][j], cmp);
            sum += algorithm.m_step_2_helper[i][j];
        }
    }
    BOOST_CHECK_EQUAL (sum, particleCount_i * particleCount_j * 2);
}

/*
 void step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell);

 public:
 ParticlesGrid (s_options &p_options, ParticleBoundsCorrection &p_particle_bounds_correction,
 AlgorithmBase &p_algorithm);

 */
