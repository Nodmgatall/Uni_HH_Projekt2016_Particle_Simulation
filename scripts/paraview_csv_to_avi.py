#### import the simple module from the paraview
from paraview.simple import *
#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

# create a new 'CSV Reader'
data = CSVReader(FileName=['/home/benjamin/workspace/Uni_HH_Projekt2016_Particle_Simulation/logdata/latest/data.0.csv', '/home/benjamin/workspace/Uni_HH_Projekt2016_Particle_Simulation/logdata/latest/data.1.csv'])

# get animation scene
animationScene1 = GetAnimationScene()

# update animation scene based on data timesteps
animationScene1.UpdateAnimationUsingDataTimeSteps()

# get active view
renderView1 = GetActiveViewOrCreate('RenderView')
# uncomment following to set a specific view size
# renderView1.ViewSize = [2386, 777]

# get layout
viewLayout1 = GetLayout()

# Create a new 'SpreadSheet View'
spreadSheetView1 = CreateView('SpreadSheetView')
spreadSheetView1.BlockSize = 1024L
spreadSheetView1.ViewSize = [800, 600]

# place view in the layout
viewLayout1.AssignView(2, spreadSheetView1)

# show data in view
dataDisplay = Show(data, spreadSheetView1)
# trace defaults for the display properties.
dataDisplay.FieldAssociation = 'Row Data'

# create a new 'Table To Points'
tableToPoints1 = TableToPoints(Input=data)
tableToPoints1.XColumn = 'PositionX'
tableToPoints1.YColumn = 'PositionY'
tableToPoints1.ZColumn = 'PositionZ'

# Properties modified on tableToPoints1

# show data in view
tableToPoints1Display = Show(tableToPoints1, spreadSheetView1)

# hide data in view
Hide(data, spreadSheetView1)

# set active view
SetActiveView(renderView1)

# set active source
SetActiveSource(tableToPoints1)

# show data in view
tableToPoints1Display_1 = Show(tableToPoints1, renderView1)
# trace defaults for the display properties.
tableToPoints1Display_1.ColorArrayName = [None, '']
tableToPoints1Display_1.DiffuseColor = [1.0, 0.0, 0.0]
tableToPoints1Display_1.PointSize = 20.0
tableToPoints1Display_1.GlyphType = 'Arrow'

# reset view to fit data
renderView1.ResetCamera()

# current camera placement for renderView1
renderView1.CameraPosition = [2.5, 2.0, 6]
renderView1.CameraFocalPoint = [2.5, 2.0, 2.0]
renderView1.CameraParallelScale = 1.0

# save animation images/movie
WriteAnimation('/home/benjamin/workspace/Uni_HH_Projekt2016_Particle_Simulation/logdata/latest/data.avi', Magnification=1, FrameRate=15.0, Compression=True)

#### uncomment the following to render all views
# RenderAllViews()
# alternatively, if you want to write images, you can use SaveScreenshot(...).