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
    std::function<bool(int &position1x,
                       int &position1y,
                       int &position1z,
                       int &velocity1x,
                       int &velocity1y,
                       int &velocity1z,
                       int &acceleration1x,
                       int &acceleration1y,
                       int &acceleration1z,
                       int &position2x,
                       int &position2y,
                       int &position2z,
                       int &velocity2x,
                       int &velocity2y,
                       int &velocity2z,
                       int &acceleration2x,
                       int &acceleration2y,
                       int &acceleration2z)>
                                           m_algorithm;
    glm::vec3                              m_bounds;
    s_simulator_options *                  m_options;
    std::shared_ptr<ParticleFileWriter>    m_particle_file_writer;
    std::unique_ptr<ParticleGeneratorBase> m_particle_generator;
    std::shared_ptr<ParticlesBase>         m_particles;
    bool                                   m_save_config;

    public:
    ParticleSimulator (s_simulator_options *p_sim_options, s_generator_options *p_gen_options);
    void simulate ();
    void init_particle_data ();
    void find_simulation_algorithm ();
};

#endif
