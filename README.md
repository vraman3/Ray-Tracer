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
1. - [ ] Comment all files with a consistent industry standard.
2. Debug k-d trees implementation.
- [x] Implemented Oct-trees. 
- [ ] Debug.
      Current output shows backside of a model. Check if kd tree issue
      or camera system.
- [ ] Runs.
- [ ] Extend to k-d trees.
3. - [ ] Refactor main.cpp to be more modular, mainly including:
   - [ ] Modularizing the camera controls.
   - [ ] Separating the TraceRay functions to another class/file.
4. - [ ] Add a way to see the output.
   - [ ] See the current output of the ray tracer.
   - [ ] See outputs for techniques already implemented and working.
5. - [ ] Improve the ReadME.
   - [ ] Make interactive with sections.
   - [ ] Add info about major techniques.
   - [ ] Index.
   
Files to be commented:

- [ ] KDNode.h and cpp. <br>
- [ ] lodepng.h and cpp. <br>
- [ ] ObjectClass.h and cpp. <br>
- [ ] ObjLoaderClass.h and cpp. <br>
- [ ] PlaneClass.h and cpp. <br>
- [ ] RayClass.h and cpp. <br>
- [ ] SaveToFile.h and cpp. <br>
- [ ] resource.h. <br>

Files needing additional comments/explanation:
- [ ] AABBClass.cpp. <br>
- [ ] CheckerBoardPattern.cpp <br>
- [ ] IlluminationClass.cpp <br>
- [ ] MatrixClass.cpp <br>

Techniques to be implemented:
2. Multi-threading.
3. Photon mapping.
