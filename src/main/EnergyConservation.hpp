/*
 * EnergyConservation.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_ENERGYCONSERVATION_HPP_
#define SRC_MAIN_ENERGYCONSERVATION_HPP_
#include "DataType.hpp"

/**
 * to disable the calculation of energy conservation just undefine the makro
 */

#define CALCULATE_ENERGY_CONSERVATION

#ifdef CALCULATE_ENERGY_CONSERVATION
extern data_type g_sum_energy;
extern bool      g_sum_energy_valid;
#endif
#endif
