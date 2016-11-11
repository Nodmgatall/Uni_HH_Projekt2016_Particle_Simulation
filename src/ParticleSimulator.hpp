#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/OptionHandler.hpp"
#include "IO/ParticleFileWriter.hpp"
#include "datastructures/ParticlesBase.hpp"
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

#include "generators/ParticleGeneratorFactoryFactory.hpp"

class ParticleSimulator {
    private:
    std::function<bool(glm::vec3 &position1, glm::vec3 &velocity1, glm::vec3 &acceleration1, glm::vec3 &position2, glm::vec3 &velocity2, glm::vec3 &acceleration2)> m_algorithm;
    glm::vec3                              m_bounds;
    float                                  m_delta_t;
    s_simulator_options *                  m_options;
    std::unique_ptr<ParticleFileWriter>    m_particle_file_writer;
    std::unique_ptr<ParticleGeneratorBase> m_particle_generator;
    std::shared_ptr<ParticlesBase>         m_particles;
    bool                                   m_save_config;
    void                                   print_header ();

    public:
    ParticleSimulator (s_simulator_options *p_sim_options, s_generator_options *p_gen_options);
    void simulate ();
    void init_particle_data ();
    void find_simulation_algorithm ();
};

#endif
