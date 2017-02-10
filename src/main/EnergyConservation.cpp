/*
 * EnergyConservation.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "EnergyConservation.hpp"

#ifdef CALCULATE_ENERGY_CONSERVATION
data_type g_sum_energy       = 0;
bool      g_sum_energy_valid = false;
#endif
