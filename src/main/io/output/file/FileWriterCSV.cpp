/*
 * ParticleFileWriter.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#include "FileWriterCSV.hpp"

FileWriterCSV::FileWriterCSV (s_options& p_options, const std::string& p_file_name_base)
: WriterBase (), m_timestep (0), m_file_name_base (p_file_name_base), m_options (p_options) {
    m_stucture_name = "FileWriterCSV";
}
void FileWriterCSV::start () {
    m_file = std::ofstream (m_file_name_base + "." + std::to_string (m_timestep) + ".csv");
    m_file << "\"" << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::ID)][0] << "\"";
    if (m_options.m_write_modes.find (e_csv_column_type::POSITION) != m_options.m_write_modes.end ()) {
        for (int i = 0; i < 3; i++) {
            m_file << ",\""
                   << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][i] << "\"";
        }
    }
    // absichtlich NICHT std::endl !!!!!
    m_file << "\n";
}
void FileWriterCSV::saveData (std::vector<data_type>&     p_positions_x,
                              std::vector<data_type>&     p_positions_y,
                              std::vector<data_type>&     p_positions_z,
                              std::vector<unsigned long>& p_ids) {
    unsigned long count = p_ids.size ();
    for (unsigned long i = 0; i < count; i++) {
        m_file << p_ids[i];
        if (m_options.m_write_modes.find (e_csv_column_type::POSITION) != m_options.m_write_modes.end ()) {
            m_file << "," << p_positions_x[i] << "," << p_positions_y[i] << "," << p_positions_z[i];
        }
        m_file << "\n";
    }
}
void FileWriterCSV::end () {
    m_file.close ();
    m_timestep++;
}
void FileWriterCSV::finalize () {
    if (m_options.m_output_type == e_output_type::FILE_CSV_AVI) {
        std::ofstream paraview_script_file (m_file_name_base + ".paraview_script.py");
        paraview_script_file << "#### import the simple module from the paraview" << std::endl
                             << "from paraview.simple import *" << std::endl
                             << "#### disable automatic camera reset on 'Show'" << std::endl
                             << "paraview.simple._DisableFirstRenderCameraReset()" << std::endl
                             << "# create a new 'CSV Reader'" << std::endl;
        paraview_script_file << "data = CSVReader(FileName=[";
        for (int i = 0; i < m_timestep; i++)
            paraview_script_file << (i > 0 ? ", " : "") << "'" << m_file_name_base << "." << i << ".csv"
                                 << "'";
        paraview_script_file << "])" << std::endl;
        paraview_script_file
            << "# get animation scene" << std::endl
            << "animationScene1 = GetAnimationScene()" << std::endl
            << "# update animation scene based on data timesteps" << std::endl
            << "animationScene1.UpdateAnimationUsingDataTimeSteps()" << std::endl
            << "# get active view" << std::endl
            << "renderView1 = GetActiveViewOrCreate('RenderView')" << std::endl
            << "# uncomment following to set a specific view size" << std::endl
            << "# renderView1.ViewSize = [2386, 777]" << std::endl
            << "# get layout" << std::endl
            << "viewLayout1 = GetLayout()" << std::endl
            << "# Create a new 'SpreadSheet View'" << std::endl
            << "spreadSheetView1 = CreateView('SpreadSheetView')" << std::endl
            << "spreadSheetView1.BlockSize = 1024L" << std::endl
            << "spreadSheetView1.ViewSize = [800, 600]" << std::endl
            << "# place view in the layout" << std::endl
            << "viewLayout1.AssignView(2, spreadSheetView1)" << std::endl
            << "# show data in view" << std::endl
            << "dataDisplay = Show(data, spreadSheetView1)" << std::endl
            << "# trace defaults for the display properties." << std::endl
            << "dataDisplay.FieldAssociation = 'Row Data'" << std::endl
            << "# create a new 'Table To Points'" << std::endl
            << "tableToPoints1 = TableToPoints(Input=data)" << std::endl
            << "tableToPoints1.XColumn = '"
            << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][0] << "'"
            << std::endl
            << "tableToPoints1.YColumn = '"
            << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][1] << "'"
            << std::endl
            << "tableToPoints1.ZColumn = '"
            << g_printed_csv_column_names[static_cast<int> (e_csv_column_type::POSITION)][2] << "'"
            << std::endl
            << "# Properties modified on tableToPoints1" << std::endl
            << "# show data in view" << std::endl
            << "tableToPoints1Display = Show(tableToPoints1, spreadSheetView1)" << std::endl
            << "# hide data in view" << std::endl
            << "Hide(data, spreadSheetView1)" << std::endl
            << "# set active view" << std::endl
            << "SetActiveView(renderView1)" << std::endl
            << "# set active source" << std::endl
            << "SetActiveSource(tableToPoints1)" << std::endl
            << "# show data in view" << std::endl
            << "tableToPoints1Display_1 = Show(tableToPoints1, renderView1)" << std::endl
            << "# trace defaults for the display properties." << std::endl
            << "tableToPoints1Display_1.ColorArrayName = [None, '']" << std::endl
            << "tableToPoints1Display_1.DiffuseColor = [1.0, 0.0, 0.0]" << std::endl
            << "tableToPoints1Display_1.PointSize = 20.0" << std::endl
            << "tableToPoints1Display_1.GlyphType = 'Arrow'" << std::endl
            << "# reset view to fit data" << std::endl
            << "renderView1.ResetCamera()" << std::endl
            << "# current camera placement for renderView1" << std::endl
            << "renderView1.CameraPosition = [2.5, 2.0, 6]" << std::endl
            << "renderView1.CameraFocalPoint = [2.5, 2.0, 2.0]" << std::endl
            << "renderView1.CameraParallelScale = 1.0" << std::endl
            << "# save animation images/movie" << std::endl
            << "WriteAnimation('" << m_file_name_base
            << ".avi', Magnification=1, FrameRate=15.0, Compression=True)" << std::endl
            << "#### uncomment the following to render all views" << std::endl
            << "# RenderAllViews()" << std::endl
            << "# alternatively, if you want to write images, you can use SaveScreenshot(...)."
            << std::endl;
        paraview_script_file.close ();

        if (system ((std::string ("pvpython ") + m_file_name_base + ".paraview_script.py").c_str ())) {
        }
    }
}
