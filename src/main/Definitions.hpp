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
#include "options/EnumAlgorithmType.hpp"
#include "options/EnumGeneratorMode.hpp"
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define ENUM_TO_STRING_ENTRY(enum_name, enum_member) \
    std::pair<enum_name, const char*> (enum_name::enum_member, #enum_member)
/////////////////////////////////////////////////////////////////////////////////////////////
enum e_data_format {
    CSV,      //
    LAMMPS,   //
    ESPRESSO, //
    GROMACS,  //
    VMD,      //
    VTK
};
static std::map<e_data_format, const char*> g_enum_data_format_to_string_map = {
    ENUM_TO_STRING_ENTRY (e_data_format, CSV),      //
    ENUM_TO_STRING_ENTRY (e_data_format, LAMMPS),   //
    ENUM_TO_STRING_ENTRY (e_data_format, ESPRESSO), //
    ENUM_TO_STRING_ENTRY (e_data_format, GROMACS),  //
    ENUM_TO_STRING_ENTRY (e_data_format, VMD),      //
    ENUM_TO_STRING_ENTRY (e_data_format, VTK),
};

/////////////////////////////////////////////////////////////////////////////////////////////
enum e_particle_variable {
    ID,           //
    VELOCITY,     //
    POSITION,     //
    ACCELERATION, //
    PARTICLE_TYPE
};
static std::map<e_particle_variable, const char*> g_enum_particle_variable_to_string_map = {
    ENUM_TO_STRING_ENTRY (e_particle_variable, VELOCITY),
    ENUM_TO_STRING_ENTRY (e_particle_variable, POSITION),
    ENUM_TO_STRING_ENTRY (e_particle_variable, ACCELERATION),
    ENUM_TO_STRING_ENTRY (e_particle_variable, PARTICLE_TYPE),
};

enum e_data_structure { GRID, LIST, LISTEDGIRD };

static std::map<e_data_structure, const char*> g_enum_data_structure_variable_to_string_map =
    { ENUM_TO_STRING_ENTRY (e_data_structure, GRID),
      ENUM_TO_STRING_ENTRY (e_data_structure, LIST),
      ENUM_TO_STRING_ENTRY (e_data_structure, LISTEDGIRD) };

#include "tools/Benchmark.hpp"
#include "tools/Debug.hpp"
#endif /* DEFINITIONS_HPP_ */
