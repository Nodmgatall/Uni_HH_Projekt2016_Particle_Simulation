#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../Definitions.hpp"
#include "../IO/Options.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include "../Vec3.hpp"
#include "../algorithms/AlgorithmBase.hpp"
#include "../borders/ParticleBoundsCorrection.hpp"
#include <iostream>
#include <vector>

class ParticlesBase {
  protected:
    std::string               m_stucture_name;
    s_options&                m_options;
    ParticleBoundsCorrection& m_particle_bounds_correction;
    AlgorithmBase&            m_algorithm;
    ParticleFileWriter&       m_particle_writer;

  public:
    virtual ~ParticlesBase () {
    }
    ParticlesBase (s_options&                p_options,
                   ParticleBoundsCorrection& p_particle_bounds_correction,
                   AlgorithmBase&            p_algorithm,
                   ParticleFileWriter&       p_particle_writer);
    virtual void run_simulation_iteration (unsigned long p_iteration_number = 0);
    virtual void add_particle (Vec3f p_position);
    virtual void add_particle (Vec3f p_position, Vec3f p_velocity);
    std::string           get_structure_name ();
    virtual unsigned long get_particle_count ();
    virtual void          serialize ();
};
#endif
