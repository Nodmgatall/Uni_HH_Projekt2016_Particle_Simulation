#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../Definitions.hpp"
#include "../IO/Options.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleFileWriter.hpp"
#include "../Vec3.hpp"
#include "../algorithms/LennardJonesAlgorithm.hpp"
#include "../borders/ParticleBoundsCorrection.hpp"
#include <iostream>
#include <vector>

class ParticlesBase {
    protected:
    std::string               m_stucture_name;
    s_options &               m_options;
    ParticleBoundsCorrection &m_particle_bounds_correction;

    public:
    virtual ~ParticlesBase () {
    }
    ParticlesBase (s_options &p_options, ParticleBoundsCorrection &p_particle_bounds_correction);
    virtual void run_simulation_iteration (unsigned long p_iteration_number = 0) = 0;
    virtual void add_particle (Vec3f p_position)                                 = 0;
    virtual void add_particle (Vec3f p_position, Vec3f p_velocity) = 0;
    void        print_structure_name ();
    std::string get_structure_name ();

    virtual unsigned long get_particle_count ()                           = 0;
    virtual void serialize (std::shared_ptr<ParticleFileWriter> p_writer) = 0;
};
#endif
