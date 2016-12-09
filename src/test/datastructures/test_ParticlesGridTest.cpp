/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticlesGrid"
#include "../../main/algorithms/AlgorithmBase.hpp"
#include "../../main/borders/ParticleBoundsCorrection.hpp"
#include "../../main/datastructures/ParticlesGrid.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

class Algorithm : public AlgorithmBase {
  public:
    Algorithm (const s_options &p_options) : AlgorithmBase (p_options) {
    }
    void step_1 (const data_type &p_position_ax,
                 const data_type &p_position_ay,
                 const data_type &p_position_az,
                 data_type &      p_position_bx,
                 data_type &      p_position_by,
                 data_type &      p_position_bz) {
        (void) p_position_ax;
        (void) p_position_ay;
        (void) p_position_az;
        (void) p_position_bx;
        (void) p_position_by;
        (void) p_position_bz;
    }
    void step_2 (const data_type &      p_position_aix,
                 const data_type &      p_position_aiy,
                 const data_type &      p_position_aiz,
                 data_type &            p_position_bix,
                 data_type &            p_position_biy,
                 data_type &            p_position_biz,
                 const data_type *const p_position_ajx,
                 const data_type *const p_position_ajy,
                 const data_type *const p_position_ajz,
                 data_type *const       p_position_bjx,
                 data_type *const       p_position_bjy,
                 data_type *const       p_position_bjz,
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
        (void) p_index_j_begin;
        (void) p_index_j_end;
    }
};
class BoundsCorrection : public ParticleBoundsCorrection {
  public:
    int m_call_count;
    BoundsCorrection (Vec3f &p_bounds) : ParticleBoundsCorrection (p_bounds), m_call_count (0) {
    }
    virtual ~BoundsCorrection () {
    }
    bool updatePosition (data_type &  m_x,
                         data_type &  m_y,
                         data_type &  m_z,
                         data_type &  m_other_x,
                         data_type &  m_other_y,
                         data_type &  m_other_z,
                         const Vec3f &m_corner000,
                         const Vec3f &m_corner111) {
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
    bool updatePosition (data_type &m_x, data_type &m_y, data_type &m_z, data_type &m_other_x, data_type &m_other_y, data_type &m_other_z) {
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
class ParticlesGridTestClass : public ParticlesGrid {
  public:
    unsigned long public_get_cell_index (long x, long y, long z) {
        return get_cell_index (x, y, z);
    }
    ParticleCell &public_get_cell_at (long x, long y, long z) {
        return get_cell_at (x, y, z);
    }
    ParticleCell &public_get_cell_for_particle (data_type x, data_type y, data_type z) {
        return get_cell_for_particle (x, y, z);
    }
    ParticleCell &public_get_cell_for_particle (Vec3f m_position) {
        return get_cell_for_particle (m_position);
    }
    void public_moveParticle (ParticleCell &p_cell_from, ParticleCell &p_cell_to, long p_index_from) {
        moveParticle (p_cell_from, p_cell_to, p_index_from);
    }
    void public_step_1_prepare_cell (ParticleCell &p_cell) {
        step_1_prepare_cell (p_cell);
    }
    void public_step_2a_calculate_inside_cell (ParticleCell &p_cell) {
        step_2a_calculate_inside_cell (p_cell);
    }
    void public_step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell &p_cell2) {
        step_2b_calculate_betweenCells (p_cell1, p_cell2);
    }
    void public_step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell) {
        step_3_remove_wrong_particles_from_cell (p_cell);
    }
    ParticlesGridTestClass (s_options &               p_options,
                            ParticleBoundsCorrection &p_particle_bounds_correction,
                            AlgorithmBase &           p_algorithm)
    : ParticlesGrid (p_options, p_particle_bounds_correction, p_algorithm) {
    }
    ~ParticlesGridTestClass () {
    }
    const std::vector<ParticleCell> &get_cells () {
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
    const Vec3l &get_size () {
        return m_size;
    }
    const Vec3f &get_size_per_cell () {
        return m_size_per_cell;
    }
};

BOOST_AUTO_TEST_CASE (test_add_particle_1) {
    unsigned int idx_x, idx_y, idx_z, idx_s, idx_t;
    s_options    options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticlesGridTestClass particlesGrid (options, border, algorithm);
    Vec3f                  particles[7];
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
                ParticleCell &cell = particlesGrid.public_get_cell_at (idx_x, idx_y, idx_z);
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
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticlesGridTestClass particlesGrid (options, border, algorithm);
    int                    counter = 0;
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
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticlesGridTestClass particlesGrid (options, border, algorithm);
    int                    counter = 0;
    for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
                ParticleCell &cell = particlesGrid.public_get_cell_at (idx_x, idx_y, idx_z);
                BOOST_CHECK_EQUAL (&cell, &particlesGrid.get_cells ()[counter++]);
            }
        }
    }
}
BOOST_AUTO_TEST_CASE (test_moveParticle) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds = Vec3f (5, 5, 5);
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticlesGridTestClass particlesGrid (options, border, algorithm);
    ParticleCell           cell1 = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
    ParticleCell           cell2 = ParticleCell (Vec3l (), Vec3l (), options.m_bounds);
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
    BoundsCorrection       border (options.m_bounds);
    Algorithm              algorithm (options);
    ParticlesGridTestClass particlesGrid (options, border, algorithm);
    int                    counter = 0;
    for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
                ParticleCell &cell = particlesGrid.public_get_cell_for_particle (
                    5.0 / particlesGrid.get_size ().x * (float) idx_x + 0.5,
                    5.0 / particlesGrid.get_size ().y * (float) idx_y + 0.5,
                    5.0 / particlesGrid.get_size ().z * (float) idx_z + 0.5);
                BOOST_CHECK_EQUAL (&cell - particlesGrid.get_cells ().data (), counter++);
            }
        }
    }
}
/*
 ParticleCell &get_cell_for_particle (data_type x, data_type y, data_type z);
 ParticleCell &get_cell_for_particle (Vec3f m_position);
 void step_1_prepare_cell (ParticleCell &p_cell);
 void step_2a_calculate_inside_cell (ParticleCell &p_cell);
 void step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell &p_cell2);
 void step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell);

 public:
 ParticlesGrid (s_options &p_options, ParticleBoundsCorrection &p_particle_bounds_correction,
 AlgorithmBase &p_algorithm);
 ~ParticlesGrid ();
 void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
 void run_simulation_iteration (unsigned long p_iteration_number = 0);
 void add_particle (Vec3f p_current_position);
 void add_particle (Vec3f p_current_position, Vec3f p_current_velocity);
 unsigned long get_particle_count (); */
