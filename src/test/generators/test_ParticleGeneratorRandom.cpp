/*
 * test_ParticleGeneratorRandom.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: benjamin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParticleGeneratorRandom"
#include "../../main/borders/ParticleBoundsCorrectionWraparound.hpp"
#include "../../main/generators/ParticleGeneratorRandom.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>

class Particles : public ParticlesBase {

    public:
    Particles (s_options &p_options, Vec3f &p_bounds, ParticleBoundsCorrection &p_particle_bounds_correction)
    : ParticlesBase (p_options, p_bounds, p_particle_bounds_correction) {
    }
    ~Particles () {
    }
    void serialize (std::shared_ptr<ParticleFileWriter> p_writer) {
        (void) p_writer;
    }
    void run_simulation_iteration (unsigned long p_iteration_number = 0) {
        (void) p_iteration_number;
    }
    void add_particle (Vec3f p_current_position) {
        (void) p_current_position;
    }
    void add_particle (Vec3f p_current_position, Vec3f p_current_velocity) {
        (void) p_current_position;
        (void) p_current_velocity;
    }
    unsigned long get_particle_count () {
        return 0;
    }
};

BOOST_AUTO_TEST_CASE (step1) {
    s_options options;
    memset (&options, 0, sizeof (s_options));
    ParticleGeneratorRandom            generator (options);
    Vec3f                              bounds;
    ParticleBoundsCorrectionWraparound particleBoundsCorrectionWraparound (bounds);
    std::shared_ptr<ParticlesBase>     particles =
        std::make_shared<Particles> (options, bounds, particleBoundsCorrectionWraparound);
    generator.generate (particles, bounds);
    // TODO
}
