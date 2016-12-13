#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "Definitions.hpp"
#include "Vec3.hpp"
#include "algorithms/AlgorithmBase.hpp"
#include "borders/BorderBase.hpp"
#include "io/output/file/FileWriterCSV.hpp"
#include "options/Options.hpp"
#include <iostream>
#include <vector>

class DatastructureBase {
  protected:
    std::string    m_stucture_name;
    s_options&     m_options;
    BorderBase&    m_border;
    AlgorithmBase& m_algorithm;
    WriterBase&    m_writer;

  public:
    virtual ~DatastructureBase () {
    }
    DatastructureBase (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_writer)
    : m_options (p_options), m_border (p_border), m_algorithm (p_algorithm), m_writer (p_writer) {
    }
    /**
     * @return returns a string form of the name of this datastructure. Can be used to verify the class.
     */
    std::string get_structure_name () {
        return m_stucture_name;
    }
    /**
     * runs a complete timestep simulation on all particles contained in this
     * datastructure
     * @param p_iteration_number unused? TODO remove?!?
     */
    virtual void run_simulation_iteration (unsigned long p_iteration_number = 0) = 0;
    /**
     * adds an particle to the current simulation
     * @param p_position the position of the new particle
     */
    virtual void add_particle (Vec3f p_position) = 0;
    /**
     *
     * adds an particle to the current simulation
     * @param p_position the position of the new particle
     * @param p_velocity the initial velocity
     */
    virtual void add_particle (Vec3f p_position, Vec3f p_velocity, int p_id = -1) = 0;
    /**
     * @return the total number of particles in all cells
     */
    virtual unsigned long get_particle_count () = 0;
    /**
     * saves all particles to an file
     */
    virtual void serialize () = 0;
};
#endif
