# Ray-Tracer
Ray Tracer

@author: Vishwanath Raman
@version: 1.0 Oct 19 2017

Hello! Thank you for checking out my Ray Tracer.
This project is currently run on Visual Studio 2013.
Future projects will have additional support.

What is going on now?
Currently in the process of beautifying the code, especially main.cpp

Things to do:
1. Comment all files with a consistent industry standard.
2. Refactor main.cpp to be more modular, mainly including:
   - Modularizing the camera controls.
   - Separating the TraceRay functions to another class/file.
3. Add a way to see the output.
   - See the current output of the ray tracer.
   - See outputs for techniques already implemented and working.
   
   
Files to be commented:

KDNode.h and cpp.
lodepng.h and cpp.
ObjectClass.h and cpp.
ObjLoaderClass.h and cpp.
PlaneClass.h and cpp.
RayClass.h and cpp.
SaveToFile.h and cpp.
resource.h.

Files needing additional comments/explanation:
AABBClass.cpp.
CheckerBoardPattern.cpp
IlluminationClass.cpp
MatrixClass.cpp

Near future techniques to be implemented:
1. K-d Trees.
The implementation is in place. Need to debug. Output shows backside of a model.

2. Multi-threading.
3. Photon mapping.
