/*
 * ParticleWriterBase.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */

#include "WriterBase.hpp"

WriterBase::WriterBase () {
}
WriterBase::~WriterBase () {
}

void WriterBase::saveData (std::vector<data_type>&     p_positions_x,
                           std::vector<data_type>&     p_positions_y,
                           std::vector<data_type>&     p_positions_z,
                           std::vector<unsigned long>& p_ids) {
    (void) p_positions_x;
    (void) p_positions_y;
    (void) p_positions_z;
    (void) p_ids;
}

void WriterBase::start () {
}

void WriterBase::end () {
}
