# Ray-Tracer
Ray Tracer

@author: Vishwanath Raman

@version: 1.0 started on Oct 19 2017

@last-update: 1.0 - 14th January 2022

Hello! Thank you for checking out my Ray Tracer.
The goal of this project is to implement a fully fledged renderer capable of rendering simple scenes. I wish to eventually focus on fluid simulation at the beginning, and see where I can go from there!

What is going on now?
Quite a ~~few~~ LOT of things that need to be done. This project was started before I had an idea of proper commenting and coding practices, let alone architecture of the whole project.
So I thought I had an issue with my kdtree as it took the same time or longer than the brute force method. However upon inspection there were many minor issues that caused a whole range of issues. Ever since I started this project I struggled with camera. I thought it was my ineptitude causing the problems but after spending quite a bit of time I found out that the camera system, like dielectrics, is a pain to debug. So my list of tasks to make the raytracer usable became even longer.

I was finally able to figure out the issues with the camera system but it led to another issue which was a complete surprise to me. The creation of the image file. Who would've thought it would cause such issues? I implemented an alternative .ppm image writer to the original .bmp, but even the .ppm had issues. Debug debug debug.

So the following list has been revised (and extended) compared to the earlier one.
Things to do:
1. Write regular blog posts detailing the progress of the raytracer, rather than writing a story in this Readme.md file everytime. 
2. [ ] Comment all files with a consistent industry standard.
3. [ ] Spend time to automatically send issues finished to a tracking system. This will involve religiously using the issue/milestone/bug features inbuilt in github.
4. [ ] Implement a clean no-artifact simple scene with no shading/illumination model
   - [ ] for Spheres
   - [ ] for Triangles
   - [ ] for Planes
   - [ ] for parsedObjects
6. [ ] Refactor main.cpp to be more modular, mainly including:
   - [x] Modularizing the camera controls.
   - [ ] There is a lot of calculation logic in main that needs to be removed.
     - [ ] Refactor or remove the creation of all the different objects for debugging.
7. - [ ] Refactor the way illumination is used.
     - [x] Remove the need to add a separate illumination array for the brute force method.
     - [ ] Check the overhead of having all or more elements to a single object.
8. - [ ] Add a way to see the output.
   - [ ] See the current output of the ray tracer.
   - [ ] See outputs for techniques already implemented and working.
9. - [ ] Improve the ReadME.
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
