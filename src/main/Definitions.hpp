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
    std::pair<enum_name, const char *> (enum_name::enum_member, #enum_member)

/////////////////////////////////////////////////////////////////////////////////////////////
enum e_generator_mode {
    MULTIPLE_OBJECTS,     // mehrere Kugeln gleichmäßig verteilt
    RANDOM,               // komplett zufällig
    RANDOM_UNIFORM,       // zufällig ungefähr gleichmäßig
    SINGLE_OBJECT_MIDDLE, // eine Kugel in der Mitte des Volumens
    GRID_DISTRIBUTION,    // komplett gleichmäßig
};
static std::map<e_generator_mode, const char *> g_enum_generator_mode_to_string_map = {
    ENUM_TO_STRING_ENTRY (e_generator_mode, MULTIPLE_OBJECTS),
    ENUM_TO_STRING_ENTRY (e_generator_mode, RANDOM),
    ENUM_TO_STRING_ENTRY (e_generator_mode, RANDOM_UNIFORM),
    ENUM_TO_STRING_ENTRY (e_generator_mode, SINGLE_OBJECT_MIDDLE),
    ENUM_TO_STRING_ENTRY (e_generator_mode, GRID_DISTRIBUTION),
};
class GeneratorInvalidException : public std::exception {
    private:
    int  m_generator_mode;
    bool m_reason_not_implemented;

    public:
    GeneratorInvalidException () : m_generator_mode (-1), m_reason_not_implemented (false) {
    }

    virtual const char *what () const throw () {
        if (m_reason_not_implemented) {
            return (std::string ("generator mode ( ") + std::to_string (m_generator_mode) +
                    " ) is not (fully) implemented")
                .c_str ();
        } else {
            return (std::string ("generator mode ( ") + std::to_string (m_generator_mode) +
                    " ) is undefined")
                .c_str ();
        }
    }

    void set_generator_mode (int generator_mode) {
        m_generator_mode = generator_mode;
    }

    void reason_not_implemented () {
        m_reason_not_implemented = true;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////////
enum e_algorithm_type {
    LENNARD_JONES,                  //
    SMOTHED_PARTICLE_HYDRODYNAMICS, //
    DISSIPATIVE_PARTICLE_DYNAMICS
};
static std::map<e_algorithm_type, const char *> g_enum_algorithm_type_to_string_map = {
    ENUM_TO_STRING_ENTRY (e_algorithm_type, LENNARD_JONES),
    ENUM_TO_STRING_ENTRY (e_algorithm_type, SMOTHED_PARTICLE_HYDRODYNAMICS),
    ENUM_TO_STRING_ENTRY (e_algorithm_type, DISSIPATIVE_PARTICLE_DYNAMICS),
};

/////////////////////////////////////////////////////////////////////////////////////////////
enum e_data_format {
    CSV,      //
    LAMMPS,   //
    ESPRESSO, //
    GROMACS,  //
    VMD,      //
    VTK
};
static std::map<e_data_format, const char *> g_enum_data_format_to_string_map = {
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
static std::map<e_particle_variable, const char *> g_enum_particle_variable_to_string_map = {
    ENUM_TO_STRING_ENTRY (e_particle_variable, VELOCITY),
    ENUM_TO_STRING_ENTRY (e_particle_variable, POSITION),
    ENUM_TO_STRING_ENTRY (e_particle_variable, ACCELERATION),
    ENUM_TO_STRING_ENTRY (e_particle_variable, PARTICLE_TYPE),
};

enum e_data_structure { GRID, LIST, LISTEDGIRD };

static std::map<e_data_structure, const char *> g_enum_data_structure_variable_to_string_map =
    { ENUM_TO_STRING_ENTRY (e_data_structure, GRID),
      ENUM_TO_STRING_ENTRY (e_data_structure, LIST),
      ENUM_TO_STRING_ENTRY (e_data_structure, LISTEDGIRD) };

#include "tools/Benchmark.hpp"
#include "tools/Debug.hpp"
#endif /* DEFINITIONS_HPP_ */
