#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../Definitions.hpp"
#include "../IO/Options.hpp"
#include "../IO/ParticleFileLoader.hpp"
#include "../IO/ParticleWriterBase.hpp"
#include "../Vec3.hpp"
#include "../algorithms/AlgorithmBase.hpp"
#include "../borders/BorderBase.hpp"
#include <iostream>
#include <vector>

class DatastructureBase {
  protected:
    std::string         m_stucture_name;
    s_options&          m_options;
    BorderBase&         m_border;
    AlgorithmBase&      m_algorithm;
    ParticleWriterBase& m_particle_writer;

  public:
    virtual ~DatastructureBase () {
    }
    DatastructureBase (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, ParticleWriterBase& p_particle_writer);
    std::string  get_structure_name ();
    virtual void run_simulation_iteration (unsigned long p_iteration_number = 0) = 0;
    virtual void add_particle (Vec3f p_position)                                 = 0;
    virtual void add_particle (Vec3f p_position, Vec3f p_velocity) = 0;
    virtual unsigned long get_particle_count () = 0;
    virtual void          serialize ()          = 0;
};
#endif
