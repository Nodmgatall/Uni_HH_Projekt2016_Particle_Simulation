/*
 * ParticleGenerator.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "ParticleGenerator.hpp"
#include "../IO/OptionsGenerator.hpp"

ParticleGenerator::ParticleGenerator (s_generator_options *p_gen_options)
: m_options (p_gen_options) {
}
void ParticleGenerator::generate (std::shared_ptr<ParticlesBase> p_particles,
                                  glm::vec3                      p_bounds,
                                  unsigned long                  p_particle_count) {
    DEBUG_BEGIN << "ParticleGenerator :: starting" << DEBUG_END;
    g_debug_stream.indent ();
    DEBUG_BEGIN << "method :: " << m_options->m_mode << DEBUG_END;
    switch (m_options->m_mode) {
        case MULTIPLE_OBJECTS:
            break;
        case RANDOM:
            generate_random (p_particles, p_bounds, p_particle_count);
            break;
        case RANDOM_UNIFORM:
            break;
        case SINGLE_OBJECT_MIDDLE:
            break;
        case UNIFORM_DISTRIBUTION:
            generate_uniform_distribution (p_particles, p_bounds, p_particle_count);
            break;
        default:
            DEBUG_BEGIN << "ParticleGenerator :: error" << DEBUG_END;
            exit (1);
    }
    g_debug_stream.unindent ();
    DEBUG_BEGIN << "ParticleGenerator :: finish" << DEBUG_END;
}
void ParticleGenerator::generate_uniform_distribution (std::shared_ptr<ParticlesBase> p_particles,
                                                       glm::vec3                      p_bounds,
                                                       unsigned long p_particle_count) {

    float     temp    = pow (p_particle_count, 1.0f / 3.0f);
    glm::vec3 delta   = (glm::vec3 (0, 0, 0) - p_bounds) / (temp - 1);
    int       tempInt = temp;
    for (int x = 0; x < tempInt; x++) {
        for (int y = 0; y < tempInt; y++) {
            for (int z = 0; z < tempInt; z++) {
                p_particles->add_particle (glm::vec3 (x, y, z) * delta, glm::vec3 (0, 0, 0), glm::vec3 (0, 0, 0));
            }
        }
    }
}

void ParticleGenerator::generate_random (std::shared_ptr<ParticlesBase> p_particles,
                                         glm::vec3                      p_bounds,
                                         unsigned long                  p_particle_count) {

    long seed = std::time (0);
    std::srand (seed); // TODO parameter bei programmstart
    for (unsigned long id = 0; id < p_particle_count; id++) {
        p_particles->add_particle (glm::vec3 (std::rand () / RAND_MAX, std::rand () / RAND_MAX, std::rand () / RAND_MAX) * p_bounds,
                                   glm::vec3 (0, 0, 0),
                                   glm::vec3 (0, 0, 0));
    }
}

e_generator_mode ParticleGenerator::get_generator_mode () {
    return m_options->m_mode;
}
