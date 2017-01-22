/*
 * DataType.hpp
 *
 *  Created on: 08.12.2016
 *      Author: benjamin
 */
#ifndef ENERGY_CONSERVATION_DEFINED
#define ENERGY_CONSERVATION_DEFINED
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
