/*
 * ParticleGroup.hpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */
#ifndef SRC_MAIN_DATASTRUCTURES_HELPER_PARTICLEGROUP_HPP_
#define SRC_MAIN_DATASTRUCTURES_HELPER_PARTICLEGROUP_HPP_
#include "Definitions.hpp"
#include "ParticleIndexRange.hpp"
#include "Vec3.hpp"
struct ParticleGroup {
  public:
    /**
     * this array hold the x Coordinate part of the Particle-position for current and last position
     */
    std::vector<data_type> m_positions_x[2];
    /**
     * this array hold the y Coordinate part of the Particle-position for current and last position
     */
    std::vector<data_type> m_positions_y[2];
    /**
     * this array hold the z Coordinate part of the Particle-position for current and last position
     */
    std::vector<data_type> m_positions_z[2];
    /**
     * this array hold the id for the given particle to be able to trac these particles in the
     * visualisation
     */
    std::vector<unsigned long> m_ids;
    /**
     * the boundarys for this cell. important for grid datastructure
     */
    Vec3f m_corner000, m_corner111;
    /**
     * the index in the cell array. important for grid-datastructure
     */
    Vec3l m_idx;
    /**
     * list of neighbors to calculate the interaction with
     */
    std::vector<std::vector<ParticleIndexRange>> m_neighbors[27];
    /**
     * constructor
     */
    ParticleGroup (Vec3l p_idx, Vec3f p_size_per_cell);
    /**
     * adds an particle to this cell
     * @param p_current_position the current position of the particle to add
     * @param p_old_position the position which the particle had the last timestep
     * @param p_current_index in which array should the current value be stored
     * @param p_id the id for the added particle
     */
    void add_particle (Vec3f p_current_position, Vec3f p_old_position, int p_current_index, int p_id);
    /**
     * Debug only!!
     * @param stream
     * @param group
     * @return
     */
    friend std::ostream& operator<< (std::ostream& stream, const ParticleGroup& group) {
        stream << DEBUG_VAR (group.m_corner000) << std::endl;
        stream << DEBUG_VAR (group.m_corner111) << std::endl;
        stream << DEBUG_VAR (group.m_idx) << std::endl;
        stream << DEBUG_VAR (group.m_ids) << std::endl;
        stream << DEBUG_VAR (group.m_positions_x) << std::endl;
        stream << DEBUG_VAR (group.m_positions_y) << std::endl;
        stream << DEBUG_VAR (group.m_positions_z) << std::endl;
        return stream;
    }
    std::vector<int>   testing;
    std::vector<float> testingx;
    std::vector<float> testingy;
    std::vector<float> testingz;
};
#endif /* SRC_MAIN_DATASTRUCTURES_HELPER_PARTICLEGROUP_HPP_ */
