/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticleGeneratorRandom"
#include "../../main/algorithms/AlgorithmBase.hpp"
#include "../../main/borders/ParticleBoundsCorrection.hpp"
#include "../../main/generators/ParticleGeneratorRandom.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

class Algorithm : public AlgorithmBase {
    Algorithm (const s_options &p_options) : AlgorithmBase (p_options) {
    }
    void step_1 (const data_type &p_position_ax,
                 const data_type &p_position_ay,
                 const data_type &p_position_az,
                 data_type &      p_position_bx,
                 data_type &      p_position_by,
                 data_type &      p_position_bz) {
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
    }
};
class BoundsCorrection : public ParticleBoundsCorrection {
    BoundsCorrection (Vec3f &p_bounds) : ParticleBoundsCorrection (p_bounds) {
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
        return true;
    }
    bool updatePosition (data_type &m_x, data_type &m_y, data_type &m_z, data_type &m_other_x, data_type &m_other_y, data_type &m_other_z) {
        return true;
    }
};
class Particles : public ParticlesGrid {
  public:
    unsigned long test_get_cell_index (long x, long y, long z) {
        return get_cell_index (x, y, z);
    }
    ParticleCell &test_get_cell_at (long x, long y, long z) {
        return get_cell_at (x, y, z);
    }
    ParticleCell &test_get_cell_for_particle (data_type x, data_type y, data_type z) {
        return get_cell_for_particle (x, y, z);
    }
    ParticleCell &test_get_cell_for_particle (Vec3f m_position) {
        return get_cell_for_particle (m_position);
    }
    void test_moveParticle (ParticleCell &p_cell_from, ParticleCell &p_cell_to, long p_index_from) {
        moveParticle (p_cell_from, p_cell_to, p_index_from);
    }
    void test_step_1_prepare_cell (ParticleCell &p_cell) {
        step_1_prepare_cell (p_cell);
    }
    void test_step_2a_calculate_inside_cell (ParticleCell &p_cell) {
        step_2a_calculate_inside_cell (p_cell);
    }
    void test_step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell &p_cell2) {
        step_2b_calculate_betweenCells (p_cell1, p_cell2);
    }
    void test_step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell) {
        step_3_remove_wrong_particles_from_cell (p_cell);
    }
    Particles (s_options &p_options, ParticleBoundsCorrection &p_particle_bounds_correction, AlgorithmBase &p_algorithm)
    : ParticlesGrid (p_options, p_particle_bounds_correction, p_algorithm) {
    }
    ~Particles () {
    }
    const std::vector<ParticleCell> &get_cells () const {
        return m_cells;
    }
    unsigned int get_idx_a () const {
        return m_idx_a;
    }
    unsigned int get_idx_b () const {
        return m_idx_b;
    }
    const unsigned int get_iterations_between_rearange_particles () const {
        return m_iterations_between_rearange_particles;
    }
    unsigned int get_iterations_until_rearange_particles () const {
        return m_iterations_until_rearange_particles;
    }
    unsigned long get_max_id () const {
        return m_max_id;
    }
    const Vec3l &get_size () const {
        return m_size;
    }
    const Vec3f &get_size_per_cell () const {
        return m_size_per_cell;
    }
};

BOOST_AUTO_TEST_CASE (test_add_particle_1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    options.m_bounds (5, 5, 5);
    BoundsCorrection border (options.m_bounds);
    Algorithm        algorithm (options);
    Particles        particlesGrid (options, border, algorithm);
    const Vec3f      particles[] = { (1, 2, 3), (-2, 2, 3), (1, -3, 4), (1, 2, -4),
                                (7, 4, 3), (1, 8, 3),  (1, 2, 9) };
    const Vec3f particlesWrapped[] = { (1, 2, 3), (2, 2, 3), (1, 3, 4), (1, 2, 4),
                                       (2, 4, 3), (1, 3, 3), (1, 2, 4) };
    for (Vec3f p : particles) {
        particlesGrid.add_particle (p);
    }
    BOOST_CHECK_EQUAL (particlesGrid.get_particle_count (), 7);
    unsigned int idx_x, idx_y, idx_z, parallel_offset;
    for (idx_x = 0; idx_x < particlesGrid.get_size ().x; idx_x++) {
        for (idx_y = 0; idx_y < particlesGrid.get_size ().y; idx_y++) {
            for (idx_z = 0; idx_z < particlesGrid.get_size ().z; idx_z++) {
                ParticleCell &cell = particlesGrid.test_get_cell_at (idx_x, idx_y, idx_z);
            }
        }
    }
}

/*inline unsigned long get_cell_index (long x, long y, long z);
 inline ParticleCell &get_cell_at (long x, long y, long z);
 ParticleCell &get_cell_for_particle (data_type x, data_type y, data_type z);
 ParticleCell &get_cell_for_particle (Vec3f m_position);
 inline void moveParticle (ParticleCell &p_cell_from, ParticleCell &p_cell_to,
 long p_index_from);
 inline void step_1_prepare_cell (ParticleCell &p_cell);
 inline void step_2a_calculate_inside_cell (ParticleCell &p_cell);
 inline void step_2b_calculate_betweenCells (ParticleCell &p_cell1, ParticleCell
 &p_cell2);
 inline void step_3_remove_wrong_particles_from_cell (ParticleCell &p_cell);

 public:
 ParticlesGrid (s_options &p_options, ParticleBoundsCorrection
 &p_particle_bounds_correction,
 AlgorithmBase &p_algorithm);
 ~ParticlesGrid ();
 void serialize (std::shared_ptr<ParticleFileWriter> p_writer);
 void run_simulation_iteration (unsigned long p_iteration_number = 0);
 void add_particle (Vec3f p_current_position, Vec3f p_current_velocity);
 */
