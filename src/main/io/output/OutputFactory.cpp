/*
 * OutputFactory.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include <io/output/OutputFactory.hpp>
OutputBase* OutputFactory::build (s_options& p_options) {
    switch (p_options.m_output_type) {
        case e_output_type::FILE_CSV:
        case e_output_type::FILE_CSV_AVI:
            return new FileOutputCSV (p_options, p_options.m_out_file_name + "/data");
        case e_output_type::VOID:
            return new VoidWriter ();
        default:
            throw OutputTypeInvalidException (p_options.m_output_type);
    }
}
