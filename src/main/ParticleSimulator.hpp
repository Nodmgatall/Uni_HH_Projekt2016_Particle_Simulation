#ifndef PARTICLE_SIMULATOR_HPP
#define PARTICLE_SIMULATOR_HPP

#include "Definitions.hpp"
#include "IO/OptionHandler.hpp"
#include "IO/ParticleFileWriter.hpp"
#include "borders/ParticleBoundsCorrectionWraparound.hpp"
#include "datastructures/ParticlesBase.hpp"
#include <functional>
#include <getopt.h>
#include <iostream>
#include <map>
#include <memory>

#include "generators/ParticleGeneratorFactory.hpp"

class ParticleSimulator {
    private:
    Vec3f                                  m_bounds;
    s_simulator_options &                  m_options;
    std::shared_ptr<ParticleFileWriter>    m_particle_file_writer;
    std::unique_ptr<ParticleGeneratorBase> m_particle_generator;
    std::shared_ptr<ParticlesBase>         m_particles;
    bool                                   m_save_config;

    public:
    ParticleSimulator (s_simulator_options &p_sim_options, s_generator_options &p_gen_options);
    void simulate ();
    void init_particle_data ();
};

#endif
