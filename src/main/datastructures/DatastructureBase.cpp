/*
 * DatastructureBase.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: benjamin
 */

#include "DatastructureListBenjamin.hpp"

void DatastructureBase::step_1_prepare_cell (ParticleGroup& p_cell) {
    unsigned int       i;
    const unsigned int max = p_cell.m_ids.size ();
    for (i = 0; i < max; i++) {
        m_algorithm.step_1 (p_cell.m_positions_x[m_idx_a][i],
                            p_cell.m_positions_y[m_idx_a][i],
                            p_cell.m_positions_z[m_idx_a][i],
                            p_cell.m_positions_x[m_idx_b][i],
                            p_cell.m_positions_y[m_idx_b][i],
                            p_cell.m_positions_z[m_idx_b][i]);
    }
}
void DatastructureBase::step_3_fit_into_borders (ParticleGroup& p_cell) {
    int i, j;
    for (i = p_cell.m_ids.size () - 1; i >= 0; i--) {
        Vec3l idx;
        while (p_cell.m_positions_x[m_idx_a][i] < 0) {
            if (!(p_cell.m_positions_x[m_idx_a][i] >=
                  -m_options.m_bounds.x * 1000)) { // Comparisons with NaN (except!=)return false
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_x[j][i] += m_options.m_bounds.x;
            }
        }
        while (p_cell.m_positions_x[m_idx_a][i] >= m_options.m_bounds.x) {
            if (!(p_cell.m_positions_x[m_idx_a][i] <= m_options.m_bounds.x * 1000)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_x[j][i] -= m_options.m_bounds.x;
            }
        }
        while (p_cell.m_positions_y[m_idx_a][i] < 0) {
            if (!(p_cell.m_positions_y[m_idx_a][i] >= -m_options.m_bounds.y * 1000)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_y[j][i] += m_options.m_bounds.y;
            }
        }
        while (p_cell.m_positions_y[m_idx_a][i] > m_options.m_bounds.y) {
            if (!(p_cell.m_positions_y[m_idx_a][i] <= m_options.m_bounds.y * 1000)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_y[j][i] -= m_options.m_bounds.y;
            }
        }
        while (p_cell.m_positions_z[m_idx_a][i] < 0) {
            if (!(p_cell.m_positions_z[m_idx_a][i] >= -m_options.m_bounds.z * 1000)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_z[j][i] += m_options.m_bounds.z;
            }
        }
        while (p_cell.m_positions_z[m_idx_a][i] >= m_options.m_bounds.z) {
            if (!(p_cell.m_positions_z[m_idx_a][i] <= m_options.m_bounds.z * 1000)) {
                m_error_stream << "something went badly wrong" << std::endl << p_cell << std::endl;
                m_error_happened = true;
                return;
            }
            for (j = 0; j <= 1; j++) {
                p_cell.m_positions_z[j][i] -= m_options.m_bounds.z;
            }
        }
    }
}

void DatastructureBase::serialize () {
    Benchmark::begin ("saving the data", false);
    m_writer.start ();
    for (ParticleGroup cell : m_particle_groups) {
        if (!(cell.m_ids.empty ())) {
            m_writer.saveData (cell.m_positions_x[m_idx_a],
                               cell.m_positions_y[m_idx_a],
                               cell.m_positions_z[m_idx_a],
                               cell.m_ids);
        }
    }
    m_writer.end ();
    Benchmark::end ();
}
void DatastructureBase::add_particle (Vec3f p_position) {
    add_particle (p_position, Vec3f (0));
}
unsigned long DatastructureBase::get_particle_count () {
    unsigned long particle_count = 0;
    for (ParticleGroup cell : m_particle_groups) {
        particle_count += cell.m_ids.size ();
    }
    return particle_count;
}
