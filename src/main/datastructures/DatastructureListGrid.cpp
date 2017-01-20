/*
 * DatastructureListGrid.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */

#include <datastructures/DatastructureListGrid.hpp>

DatastructureListGrid::DatastructureListGrid (s_options&     p_options,
                                              BorderBase&    p_border,
                                              AlgorithmBase& p_algorithm,
                                              WriterBase&    p_particle_writer)
: DatastructureBase (p_options, p_border, p_algorithm, p_particle_writer),
  DatastructureGrid (p_options, p_border, p_algorithm, p_particle_writer),
  DatastructureListBenjamin (p_options, p_border, p_algorithm, p_particle_writer) {
    m_stucture_name = "DatastructureListGrid";
}
DatastructureListGrid::~DatastructureListGrid () {
}
bool DatastructureListGrid::run_simulation_iteration (unsigned long p_iteration_number) {
    (void) p_iteration_number;
    bool result = DatastructureGrid::run_simulation_iteration ();
    if (m_iterations_until_rearange_particles == m_options.m_max_iterations_between_datastructure_rebuild) {
        for (ParticleGroup cell : m_particle_groups) {
            list_rebuild (cell);
        }
    }
    return result;
}
void DatastructureListGrid::add_particle (Vec3f p_position) {
    DatastructureGrid::add_particle (p_position);
}
void DatastructureListGrid::add_particle (Vec3f p_current_position, Vec3f p_current_velocity, int p_id) {
    DatastructureGrid::add_particle (p_current_position, p_current_velocity, p_id);
}
