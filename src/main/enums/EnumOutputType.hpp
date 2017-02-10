/*
 * EnumOutputType.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_MAIN_ENUMS_ENUMOUTPUTTYPE_HPP_
#define SRC_MAIN_ENUMS_ENUMOUTPUTTYPE_HPP_
#include <cstring>
#include <exception>
#include <istream>
#include <ostream>
#include <vector>
/**
 * implemented or planned output types for simulation
 */
enum class e_output_type { VOID = 1, FILE_CSV = 2, FILE_LAMMPS = 3, FILE_ESPRESSO = 4, FILE_GROMACS = 5, FILE_VMD = 6, FILE_VTK = 7, FILE_CSV_AVI = 8 };
// CSV::ParaView	how to  -> http://www.paraview.org/Wiki/ParaView/Data_formats
/* visualisierungs software
 *
 http://lammps.sandia.gov/viz.html

 VMD
 AtomEye
 OVITO
 ParaView
 PyMol
 Raster3d
 RasMol
 *
 * */
std::ostream& operator<< (std::ostream& stream, const e_output_type& p_output_type);
std::istream& operator>> (std::istream& stream, e_output_type& p_output_type);
extern std::vector<const char*> g_output_names;
extern std::vector<bool>        g_output_implemented;
class OutputTypeInvalidException : public std::exception {
  private:
    char* m_what;

  public:
    OutputTypeInvalidException () {
        m_what = (char*) malloc (100);
        sprintf (m_what, "output type ( %s ) is invalid", g_output_names[0]);
    }
    OutputTypeInvalidException (e_output_type m_type) {
        m_what = (char*) malloc (100);
        sprintf (m_what, "output type ( %s ) is invalid", g_output_names[static_cast<int> (m_type)]);
    }
    ~OutputTypeInvalidException () {
        free (m_what);
    }
    const char* what () const throw () {
        return m_what;
    }
};
#endif /* SRC_MAIN_OPTIONS_ENUMOUTPUTFORMAT_HPP_ */
