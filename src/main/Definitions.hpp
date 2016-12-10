/*
 * definitions.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_
#include "DataType.hpp"
#ifdef OMP_AVAILABLE
#include <omp.h>
#endif
#include "enums/EnumAlgorithmType.hpp"
#include "enums/EnumCSVColumnType.hpp"
#include "enums/EnumDatastructureType.hpp"
#include "enums/EnumInputType.hpp"
#include "enums/EnumOutputType.hpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <memory>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <vector>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include "tools/Benchmark.hpp"
#include "tools/Debug.hpp"
#endif /* DEFINITIONS_HPP_ */
