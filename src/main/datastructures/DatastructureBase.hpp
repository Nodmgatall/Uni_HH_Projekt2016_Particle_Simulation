#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "../Definitions.hpp"
#include "../Vec3.hpp"
#include "../algorithms/AlgorithmBase.hpp"
#include "../borders/BorderBase.hpp"
#include "../io/output/ParticleWriterBase.hpp"
#include "../options/Options.hpp"
#include <iostream>
#include <vector>

class DatastructureBase {
  protected:
    std::string         m_stucture_name;
    s_options&          m_options;
    BorderBase&         m_border;
    AlgorithmBase&      m_algorithm;
    ParticleWriterBase& m_writer;

  public:
    virtual ~DatastructureBase () {
    }
    DatastructureBase (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, ParticleWriterBase& p_writer)
    : m_options (p_options), m_border (p_border), m_algorithm (p_algorithm), m_writer (p_writer) {
    }
    std::string get_structure_name () {
        return m_stucture_name;
    }
    virtual void run_simulation_iteration (unsigned long p_iteration_number = 0) {
        (void) p_iteration_number;
    }
    virtual void add_particle (Vec3f p_position) {
        (void) p_position;
    }
    virtual void add_particle (Vec3f p_position, Vec3f p_velocity) {
        (void) p_position;
        (void) p_velocity;
    }
    virtual unsigned long get_particle_count () {
        return 0;
    }
    virtual void serialize () {
    }
};
#endif
