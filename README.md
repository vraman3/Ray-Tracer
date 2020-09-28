# Ray-Tracer
Ray Tracer

@author: Vishwanath Raman

@version: 1.0 started on Oct 19 2017

@last-update: 1.0 - 28th September 2020

Hello! Thank you for checking out my Ray Tracer.
This project was started in Visual Studio 2013 and has recently been ported to Visual Studio 2019.
Future projects will have additional support.

What is going on now?
Quite a few things that need to be done. This project was started before I had an idea of proper commenting and coding practices, let alone architecture of the whole project.
Currently there is an issue with my kdtree; it takes the same time, or even longer, as the brute force method of cycling through the objects. This is the main thing that needs to be fixed before I move on.
Following that, I need to work on increasing the readability of the code before moving onto anything else.
The output is seen in the scene_Vishwanath.bmp file. Currently run on the bunnyBlender_v2.obj.

Things to do:
1. - [ ] Comment all files with a consistent industry standard.
2. - [ ] Add issue/feature/bug tracking in github.
     - [ ] Clean up all the stray/unused branches.
     - [ ] Add the features written in readme to a trackable system in github.
3. - [ ] Debug k-d trees implementation.
     - [x] Implemented Oct-trees. 
     - [x] Debug.
     - [x] Runs.
     - [x] Extend to k-d trees
       - [ ] Current running time for kdtrees and the brute force method is the same. Need to debug the kdtree implementation.
4. - [ ] Refactor main.cpp to be more modular, mainly including:
   - [x] Modularizing the camera controls.
   - [x] Separating the TraceRay functions to another class/file.
   - [x] Separated the rendering into a separate class. This includes looping over the pixels.
   - [ ] There is a lot of calculation logic in main that needs to be removed.
     - [ ] Refactor or remove the creation of all the different objects for debugging.
5. - [ ] Refactor the way illumination is used.
     - [ ] Remove the need to add a separate illumination array for the brute force method.
     - [ ] Check the overhead of having all or more elements to a single object.
6. - [ ] Add a way to see the output.
   - [ ] See the current output of the ray tracer.
   - [ ] See outputs for techniques already implemented and working.
7. - [ ] Improve the ReadME.
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
1. Multi-threading.
2. Photon mapping.
