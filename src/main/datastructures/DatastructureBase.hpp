/*
 * DatastructureBase.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREBASE_HPP_
#define SRC_MAIN_DATASTRUCTURES_DATASTRUCTUREBASE_HPP_
#include "Definitions.hpp"
#include "Vec3.hpp"
#include "algorithms/AlgorithmBase.hpp"
#include "borders/BorderBase.hpp"
#include "helper/ParticleGroup.hpp"
#include "options/Options.hpp"
#include <Statistics.hpp>
#include <io/output/file/FileOutputCSV.hpp>
#include <iostream>
#include <vector>
class DatastructureBase {
  protected:
    /**
     * the structure name to verify, which subclass is used
     */
    std::string m_stucture_name;
    /**
     * the border-helper-functions
     */
    BorderBase& m_border;
    /**
     * the algorithm to use to calculate the forces
     */
    AlgorithmBase& m_algorithm;
    /**
     * how the data should be saved
     */
    OutputBase& m_writer;
    /**
     * true if an error happened, and the simulation should be stopped
     */
    bool m_error_happened;
    /**
     * the factor for the current max speed to calculate the iteration count to next rebuild
     */
    data_type m_speed_factor;
    /**
     * the number of iterations until next test that all particles stay within the given bounds
     */
    int m_iterations_until_rearange_particles;
    /**
     * the number of iterations calculated since last rebuild
     */
    int m_iterations_since_rearange_particles;
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
     * flag indicates if the datastructure was rebuild in the last iteration. used for linked cells and neighbor list combination
     */
    bool m_datastructure_rebuild_last_iteration_flag;
    /**
     * first step in each iteration. Calculates the new particle position based on
     * its own speed
     * @param p_cell the cell contains the particles which are calculated
     */

    void step_1_prepare_cell (ParticleGroup& p_cell);
    /**
     * the cells in which the particles are stored
     */
    ParticleGroup* m_particle_groups;
    /**
     * the count of cells in which the particles are stored
     */
    size_t m_particle_groups_count;
    /**
     * verify that all particles in cell are inside the given bounds, if they are not, they are
     * moved
     * @param p_cell
     */
    void step_3_fit_into_borders (ParticleGroup& p_cell);
    void add_particle_internal (Vec3f p_current_position, Vec3f p_last_position, int p_id);

  public:
    /**
     * the options passed to the program
     */
    s_options& m_options;
    /**
     *destructor
     */
    virtual ~DatastructureBase () {
    }
    /**
     * constructor
     */
    DatastructureBase (s_options& p_options, BorderBase& p_border, AlgorithmBase& p_algorithm, OutputBase& p_writer)
    : m_border (p_border), m_algorithm (p_algorithm), m_writer (p_writer), m_error_happened (false), m_iterations_until_rearange_particles (1),
      m_iterations_since_rearange_particles (0), m_idx_a (0), m_idx_b (1), m_max_id (0),
      m_datastructure_rebuild_last_iteration_flag (true /*list MUST rebuild in first iteration*/), m_particle_groups (0), m_particle_groups_count (0), m_options (p_options) {
        m_iterations_until_rearange_particles = p_options.m_max_iterations_between_datastructure_rebuild;
        m_iterations_since_rearange_particles = p_options.m_max_iterations_between_datastructure_rebuild;
        // -1 because only the additional bonus space is mesured
        m_speed_factor = MAX (m_options.m_cut_off_radius * (p_options.m_cut_off_radius_extra_factor - 1.0), 0);
    }
    /**
     * @return returns a string form of the name of this datastructure. Can be used to verify the
     * class.
     */
    std::string get_structure_name () {
        return m_stucture_name;
    }
    /**
     * @return returns a enum representing this datastructure. Can be used to verify the
     * class.
     */
    virtual e_datastructure_type get_structure_type ();
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
    /**
     * calculates, based on particlespeed when the datastructure should berebuild the next time
     */
    void calculate_next_datastructure_rebuild ();
    /**
     * transfers the internally stored particles to another datastructure.
     */
    void transfer_particles_to (DatastructureBase* p_datastructure);
    /**
     * analyses the already given particles and returns which datastructure would be the fastest.
     * this function modifies p_options.m_initial_speed and p_options.m_input_type
     */
    void analyse ();
};
// TODO phillip erinnern geschwindigkeitsinitialisierung
#endif
