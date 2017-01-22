/*
 * definitions.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
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
#ifdef OMP_AVAILABLE
#include <omp.h>
#endif
#include "DataType.hpp"
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
#include <set>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#endif /* DEFINITIONS_HPP_ */
