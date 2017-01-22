#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "Definitions.hpp"
#include "Vec3.hpp"
#include "algorithms/AlgorithmBase.hpp"
#include "borders/BorderBase.hpp"
#include "helper/ParticleGroup.hpp"
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
    bool           m_error_happened;
    /**
     * the number of iterations until next test that all particles stay within the given bounds
     */
    int m_iterations_until_rearange_particles;
    /**
     * the current position of particles is stored in the array with this index
     * m_idx_a != m_idx_b
     */
    unsigned int m_idx_a;
    /**
     * the last/next position of particles is stored in the array with this index
     * m_idx_a != m_idx_b
     */
    unsigned int m_idx_b;
    /**
     * the index for the "next" inserted particle
     */
    long m_max_id;
    /**
         * first step in each iteration. Calculates the new particle position based on
         * its own speed
         * @param p_cell the cell contains the particles which are calculated
         */
    void step_1_prepare_cell (ParticleGroup& p_cell);
    /**
     * the cells in which the particles are stored
     */
    std::vector<ParticleGroup> m_particle_groups;
    /**
         * verify that all particles in cell are inside the given bounds, if they are not, they are
         * moved
         * @param p_cell
         */
    void step_3_fit_into_borders (ParticleGroup& p_cell);
  public:
    /**
     *destructor
     */
    virtual ~DatastructureBase () {
    }
    /**
     * constructor
     */
    DatastructureBase (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, WriterBase& p_writer)
    : m_options (p_options), m_border (p_border), m_algorithm (p_algorithm), m_writer (p_writer), m_error_happened (false), m_iterations_until_rearange_particles (0), m_idx_a (0),
      m_idx_b (1), m_max_id (0) {
    }
    /**
     * @return returns a string form of the name of this datastructure. Can be used to verify the
     * class.
     */
    std::string get_structure_name () {
        return m_stucture_name;
    }
    /**
     * runs a complete timestep simulation on all particles contained in this
     * datastructure
     * @return true if an error happened and the simulation must be stopped after this iteration
     * 		   false if everything is ok with the simulation
     * @param p_iteration_number unused? TODO remove?!?
     */
    virtual bool run_simulation_iteration (unsigned long p_iteration_number = 0);
    /**
     * adds an particle to the current simulation
     * @param p_position the position of the new particle
     */
    virtual void add_particle (Vec3f p_position);
    /**
     *
     * adds an particle to the current simulation
     * @param p_position the position of the new particle
     * @param p_velocity the initial velocity
     */
    virtual void add_particle (Vec3f p_position, Vec3f p_velocity, int p_id = -1);
    // TODO delete particle hinzufügen
    /**
     * @return the total number of particles in all cells
     */
    unsigned long get_particle_count ();
    /**
     * saves all particles to an file
     */
    void serialize ();
};
// TODO phillip erinnern geschwindigkeitsinitialisierung
#endif
