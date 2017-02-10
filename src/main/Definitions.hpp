/*
 * Definitions.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_
#define _USE_MATH_DEFINES
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef SGN
#define SGN(x) (((x) < 0) ? -1 : ((x) > 0))
#endif
#ifdef OMP_AVAILABLE
#include <omp.h>
#endif
#include "DataType.hpp"
#include "EnergyConservation.hpp"
#include "enums/EnumAlgorithmType.hpp"
#include "enums/EnumCSVColumnType.hpp"
#include "enums/EnumDatastructureType.hpp"
#include "enums/EnumInputType.hpp"
#include "enums/EnumOutputType.hpp"
#include "tools/Benchmark.hpp"
#include "tools/Debug.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <omp.h>
#include <set>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#endif /* DEFINITIONS_HPP_ */
