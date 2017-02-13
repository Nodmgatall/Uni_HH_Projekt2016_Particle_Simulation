/*
 * FileWriterCSV.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include <io/output/file/FileOutputCSV.hpp>
FileOutputCSV::FileOutputCSV (s_options& p_options) : OutputBase (), m_timestep (0), m_file_name_base (p_options.m_out_file_name + "/data"), m_options (p_options) {
    m_stucture_name = "FileOutputCSV";
    if (mkdir (p_options.m_out_file_name.c_str (), 0700)) {
        // don't care ... but return value is used
    }
}
void FileOutputCSV::start () {
    m_file = std::ofstream (m_file_name_base + "." + std::to_string (m_timestep) + ".csv");
    m_file << "\"" << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::ID)][0] << "\"";
    if (m_options.m_write_modes.find (e_csv_column_type::POSITION) != m_options.m_write_modes.end ()) {
        for (int i = 0; i < 3; i++) {
            m_file << ",\"" << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][i] << "\"";
        }
    }
    // absichtlich NICHT std::endl !!!!!
    m_file << "\n";
}
void FileOutputCSV::saveData (std::vector<data_type>& p_positions_x, std::vector<data_type>& p_positions_y, std::vector<data_type>& p_positions_z, std::vector<unsigned long>& p_ids) {
    unsigned long count = p_ids.size ();
    for (unsigned long i = 0; i < count; i++) {
        m_file << p_ids[i];
        if (m_options.m_write_modes.find (e_csv_column_type::POSITION) != m_options.m_write_modes.end ()) {
            m_file << "," << p_positions_x[i] << "," << p_positions_y[i] << "," << p_positions_z[i];
        }
        m_file << "\n";
    }
}
void FileOutputCSV::end () {
    m_file.close ();
    m_timestep++;
}
void FileOutputCSV::finalize () {
    if (m_options.m_output_type == e_output_type::FILE_CSV_AVI) {
        std::ofstream paraview_script_file (m_file_name_base + ".paraview_script.py");
        paraview_script_file << "from paraview.simple import *                                                   " << std::endl
                             << "#### disable automatic camera reset on 'Show'                                   " << std::endl
                             << "paraview.simple._DisableFirstRenderCameraReset()                                " << std::endl;
        paraview_script_file << "data = CSVReader(FileName=[";
        for (int i = 0; i < m_timestep; i++)
            paraview_script_file << (i > 0 ? ", " : "") << "'" << m_file_name_base << "." << i << ".csv"
                                 << "'";
        paraview_script_file << "])" << std::endl;
        paraview_script_file << "animationScene1 = GetAnimationScene()                                           " << std::endl
                             << "animationScene1.UpdateAnimationUsingDataTimeSteps()                             " << std::endl
                             << "renderView1 = GetActiveViewOrCreate('RenderView')                               " << std::endl
                             << "renderView1.ViewSize = [800, 600]                                               " << std::endl
                             << "tableToPoints1 = TableToPoints(Input=data)                                      " << std::endl
                             << "tableToPoints1.XColumn = '" << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][0] << "'" << std::endl
                             << "tableToPoints1.YColumn = '" << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][1] << "'" << std::endl
                             << "tableToPoints1.ZColumn = '" << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][2] << "'" << std::endl
                             << "SetActiveView(renderView1)                                                      " << std::endl
                             << "SetActiveSource(tableToPoints1)                                                 " << std::endl
                             << "tableToPoints1Display_1 = Show(tableToPoints1, renderView1)                     " << std::endl
                             << "tableToPoints1Display_1.ColorArrayName = [None, '']                             " << std::endl
                             << "tableToPoints1Display_1.DiffuseColor = [1.0, 0.0, 0.0]                          " << std::endl
                             << "tableToPoints1Display_1.PointSize = 20.0                                        " << std::endl
                             << "tableToPoints1Display_1.GlyphType = 'Arrow'                                     " << std::endl
                             << "renderView1.ResetCamera()                                                       " << std::endl
                             << "renderView1.CameraPosition = [2.5, 2.0, 6]                                      " << std::endl
                             << "renderView1.CameraFocalPoint = [2.5, 2.0, 2.0]                                  " << std::endl
                             << "renderView1.CameraParallelScale = 1.0                                           " << std::endl
                             << "WriteAnimation('" << m_file_name_base << ".avi', Magnification=1, FrameRate=15.0, Compression=True)                       " << std::endl;
        paraview_script_file.close ();
        if (system ((std::string ("pvpython ") + m_file_name_base + ".paraview_script.py").c_str ())) {
            // execute shell command -> output is printed to std::cout
        }
    }
}
