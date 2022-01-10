/**
	RayTracing, main.cpp
	The main class to execute the program.

	@author: Vishwanath Raman
	@version: 1.0 Oct/23/2017

*/

#include "IncludesList.h"
#include <chrono>

//typedef techsoft::matrix<double> Matrix;

int main(int argc, char* argv[])
{
#pragma region start
	//  Choose Tone Reproduction Operator
	//
	//  1 - Ward 
	//  2 - Reinhard
	//  3 - Adaptive Logarithmic
	//  0 - No Tone Reproduction (By Default)
	int whichTR, maxDepth;
	int screenWidth, screenHeight;
	double aspectRatio = 16.0 / 9.0;
	double worldHeight = 2.0;
	double worldWidth = aspectRatio * worldHeight;

	// Get command line arguments if any
	if (argc == 5)
	{
		screenWidth = std::atoi(argv[1]);
		screenHeight = std::atoi(argv[2]);
		maxDepth = std::atoi(argv[3]);
		whichTR = std::atoi(argv[4]);
		std::cout << " Width:" << argv[1] << "  Height:" << argv[2] << " Max Depth:" << argv[3] << " ToneReproduction:" << argv[4] << std::endl;
	}
	else
	{
		screenWidth = 640;
		screenHeight = static_cast<int>(screenWidth / aspectRatio);
		maxDepth = 5;
		whichTR = 3;
	}

#pragma region cubeStraightObjectsAndIlluminations

#pragma region cubeStraightObjects
	std::vector<ObjectClass*> cubeStraightObjects;

	std::vector<VectorClass> cubeStraightPoints;

	cubeStraightPoints.push_back(VectorClass(1.0, -1.0, -1.0));
	cubeStraightPoints.push_back(VectorClass(1.0, -1.0, 1.0));
	cubeStraightPoints.push_back(VectorClass(-1.0, -1.0, 1.0));
	cubeStraightPoints.push_back(VectorClass(-1.0, -1.0, -1.0));

	cubeStraightPoints.push_back(VectorClass(1.0, 1.0, -0.999999));
	cubeStraightPoints.push_back(VectorClass(0.999999, 1.0, 1.000001));
	cubeStraightPoints.push_back(VectorClass(-1.0, 1.0, 1.0));
	cubeStraightPoints.push_back(VectorClass(-1.0, 1.0, -1.0));

	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[1], cubeStraightPoints[3], cubeStraightPoints[0],
		ColourClass(1.0, 0.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[7], cubeStraightPoints[5], cubeStraightPoints[4],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[4], cubeStraightPoints[1], cubeStraightPoints[0],
		ColourClass(0.0, 117.0, 220.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[5], cubeStraightPoints[2], cubeStraightPoints[1],
		ColourClass(165.0, 42.0, 42.0)));

	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[2], cubeStraightPoints[7], cubeStraightPoints[3],
		ColourClass(128.0, 128.0, 128.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[0], cubeStraightPoints[7], cubeStraightPoints[4],
		ColourClass(255.0, 165.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[1], cubeStraightPoints[2], cubeStraightPoints[3],
		ColourClass(255.0, 255.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[7], cubeStraightPoints[6], cubeStraightPoints[5],
		ColourClass(194.0, 0.0, 136.0)));

	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[4], cubeStraightPoints[5], cubeStraightPoints[1],
		ColourClass(255.0, 168.0, 187.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[5], cubeStraightPoints[6], cubeStraightPoints[2],
		ColourClass(157.0, 204.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[2], cubeStraightPoints[6], cubeStraightPoints[7],
		ColourClass(153.0, 0.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[0], cubeStraightPoints[3], cubeStraightPoints[7],
		ColourClass(143.0, 124.0, 0.0)));

#pragma endregion

#pragma region cubeStraightIllum
	std::vector<IlluminationClass*> cubeStraightIllum;

	for (int i = 0; i < cubeStraightObjects.size(); i++)
	{
		cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	}
#pragma endregion

#pragma endregion

#pragma region CustomRaytracerObjects
	std::vector<ObjectClass*> customObjects;

	//customObjects.push_back(new SphereClass(0.9, VectorClass(0, 0, -1), ColourClass(0.0, 1.0, 0.0)));

	customObjects.push_back(new TriangleClass(VectorClass(0, 0, 0), VectorClass(0, 0, 0), VectorClass(0, 0, 0), 
		ColourClass(0, 1, 0)));
	/*customObjects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300),
		VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0),
		ColourClass(0.0, 1.0, 0.0),
		new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));*/

	std::vector<IlluminationClass*> customObjectsIllum;

	//customObjectsIllum.push_back(new PhongModel(0.3, 0.6, 0.1, 12.5, 0.0, 0.2));

	customObjectsIllum.push_back(new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0));
#pragma endregion

#pragma region KdTreeAndBruteForceObjectLoading
#pragma region KDTreesObjectLoading
	ObjLoaderClass objFile = ObjLoaderClass();

	//objFile.readObjFile("icosphereObj.obj");
	objFile.readObjFile("cubeStraight.obj");
	///objFile.readObjFile("bunnyBlender_v2.obj");

	int noOfFaces = objFile.faces.size();

	std::vector<TriangleClass*> parsedObject;

	int objectCount = 0;


	// To test each triangle individually
	/*parsedObject.push_back(new TriangleClass(objFile.opVertices[objFile.faces[0] - 1],
				objFile.opVertices[objFile.faces[1] - 1],
				objFile.opVertices[objFile.faces[2] - 1],
				ColourClass(0.0, 1.0, 0.0),
				new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0), ++objectCount));*/
	
	parsedObject.push_back(new TriangleClass(VectorClass(-1,-1,1),
		VectorClass(1, 1, -1),
		VectorClass(1, -1, 1),
		ColourClass(0.0, 1.0, 0.0),
		new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0), ++objectCount));

	//for (int i = 0; i < noOfFaces; i += 3)
	//{
	//	parsedObject.push_back(new TriangleClass(objFile.opVertices[objFile.faces[i] - 1],
	//		objFile.opVertices[objFile.faces[i + 1] - 1],
	//		objFile.opVertices[objFile.faces[i + 2] - 1],
	//		ColourClass(0.0, 1.0, 0.0),
	//		new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0), ++objectCount)); // new NoShadingModel(0, 0))); // 
	//}

#pragma endregion

#pragma endregion
	std::vector<TriangleClass*> openGLCoordKDtrees;

	auto start = std::chrono::high_resolution_clock::now();

	KDNode kdtree = KDNode();
	kdtree = *kdtree.build(parsedObject, 3);

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> kdBuild_time = finish - start;

	SaveToFIle kdtreeTxtFile = SaveToFIle();
	kdtreeTxtFile.savetxtkdtree(kdtree);

#pragma region Lights
	std::vector<VectorClass*> lights;

	lights.push_back(new VectorClass(5, 7.4, 9));
#pragma endregion

#pragma endregion


#pragma region background,screensize,camera
	ColourClass background(0.3, 0.8, 1.0);
	ColourClass pointCol(1.0, 1.0, 1.0);

	int filesize = screenWidth * screenHeight;
	ColourClass* pixels = new ColourClass[filesize];
	ColourClass* pixelsBruteForce = new ColourClass[filesize];
	//ColourClass* pixels_debug = new ColourClass[filesize];

	VectorClass camPosition = VectorClass(0, 0, 8);
	VectorClass camLookAt = VectorClass(0, 0, 2);
	double f = 0.1;

	// Calculate the Camera parameters
	//VectorClass camRight = camLookAt.normalize().crossProd(VectorClass(0, 1, 0));
	//VectorClass camUp = camRight.crossProd(camLookAt);
	CameraClass originalCamera = CameraClass(camPosition, camLookAt, VectorClass(0, 1, 0), f);

	// RHS
	//
	// N = Eye - LookAt
	// U = Up x N
	// V = N x U
	//
	VectorClass camN = (originalCamera.GetPosition() - originalCamera.GetLookAt()).normalize();
	VectorClass camU = (originalCamera.GetUpVector().crossProd(camN)).normalize();
	VectorClass camV = camN.crossProd(camU);

	// LHS
	//
	// N = LookAt - Eye
	// U = N x Up
	// V = U x N
	//
	// VectorClass camN = ( originalCamera.GetLookAt() - originalCamera.GetPosition() ).normalize();
	// VectorClass camU = ( camN.crossProd(originalCamera.GetUpVector()) ).normalize();
	// VectorClass camV = camU.crossProd(camN);

	// Calculate center pixel of image plane
	// Should subtract f for RHS, and add f for LHS system.
	VectorClass center(originalCamera.GetPosition().getX() - f * camN.getX(),
		originalCamera.GetPosition().getY() - f * camN.getY(),
		originalCamera.GetPosition().getZ() - f * camN.getZ());

	// The bottom leftmost point of the image plane
	VectorClass startPixel;

	startPixel.setX(center.getX() - ((worldWidth * camU.getX())
		+ (worldHeight * camV.getX())) / 2.0);
	startPixel.setY(center.getY() - ((worldWidth * camU.getY())
		+ (worldHeight * camV.getY())) / 2.0);
	startPixel.setZ(center.getZ() - ((worldWidth * camU.getZ())
		+ (worldHeight * camV.getZ())) / 2.0);

	double pixelW = worldWidth / screenWidth;
	double pixelH = worldHeight / screenHeight;
#pragma endregion 

	Render renderObject = Render();

	// Temp remove later, 1 to enable either method.
	int choiceBrute = 0;
	int choicekdtree = 0;
	int choiceDebug = 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// For debugRender				TEMPORARY DEBUGGING
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	if (choiceDebug)
	{
		int position_debug = 0;

		
		// before camera abstraction
		double focalLength_debug = 1.0;
		VectorClass origin_debug = VectorClass(0.0, 0.0, 0.0);
		VectorClass horizontal_debug = VectorClass(worldWidth, 0, 0);
		VectorClass vertical_debug = VectorClass(0, worldHeight, 0);
		auto lowerLeftCorner_debug = origin_debug - horizontal_debug / 2 - vertical_debug / 2 - VectorClass(0, 0, focalLength_debug);

		// After camera abstraction
		//double aspectRatio = 16.0 / 9.0;
		int imageWidth = 640;
		int imageHeight = static_cast<int>(imageWidth / aspectRatio);

		int filesize_debug = imageWidth * imageHeight;
		ColourClass* pixels_debug = new ColourClass[filesize_debug];

		start = std::chrono::high_resolution_clock::now();

		std::vector<ObjectClass*> objects_debug;

		ColourClass material_ground = ColourClass(0.8, 0.8, 0.0);
		ColourClass material_center = ColourClass(0.1, 0.2, 0.5);
		ColourClass material_left = ColourClass(0.0, 0.0, 0.0);
		ColourClass material_right = ColourClass(0.8, 0.6, 0.2);

		//objects_debug.push_back(new SphereClass(100, VectorClass(0.0, -100.5, -1.0), material_ground));
		//objects_debug.push_back(new SphereClass(0.5, VectorClass(0.0, 0.0, -1.0), material_center));
		//objects_debug.push_back(new SphereClass(0.5, VectorClass(-1.0, 0.0, -1.0), material_left));
		////objects_debug.push_back(new SphereClass(-0.45, VectorClass(-1, 0, -1), material_left));
		//objects_debug.push_back(new SphereClass(0.5, VectorClass(1.0, 0.0, -1.0), material_right));

		objects_debug.push_back(new SphereClass(0.5, VectorClass(0, 0, -1), ColourClass(1.0, 0.0, 0.0)));
		objects_debug.push_back(new SphereClass(100, VectorClass(0, -100.5, -1), ColourClass(0.0, 1.0, 0.0)));

		/*auto R = cos(3.1415926535897932385 / 4);

		objects_debug.push_back(new SphereClass(R, VectorClass(-R, 0, -1), ColourClass(0.0, 0.0, 1.0)));
		objects_debug.push_back(new SphereClass(R, VectorClass(R, 0, -1), ColourClass(1.0, 0.0, 0.0)));*/

		/*SphereClass sphere_debug = SphereClass(0.5, VectorClass(0, 0, -1), ColourClass(1.0, 0.0, 0.0));
		SphereClass sphere_debug = SphereClass(100, VectorClass(0, -100.5, -1), ColourClass(0.0, 1.0, 0.0));*/

		Tracing traceObject_debug = Tracing();
		
		CameraClass cam_debug = CameraClass(1, VectorClass(0, 0, 1), VectorClass(0, 0, -1), VectorClass(0, 1, 0),
			90.0, aspectRatio);
		// This is how the book does it, but it reverts image here...why?
		for (int j = imageHeight - 1; j >= 0; --j)
		{
			for (int i = 0; i < imageWidth; ++i)
			{

		/*for (int j = 0 ; j < imageHeight; ++j)
		{
			for (int i = 0; i < imageWidth; ++i)
			{*/
				auto u = (double)i / ((double)imageWidth - 1);
				auto v = (double)j / ((double)imageHeight - 1);

				/*VectorClass direction_debug = lowerLeftCorner_debug + (horizontal_debug * u) + (vertical_debug * v) - origin_debug;
				RayClass ray_debug = RayClass(origin_debug, direction_debug);*/
				RayClass ray_debug = cam_debug.getRay(u, v);

				// Trace across any objects
				ColourClass pixelColour_debug = traceObject_debug.TraceRay_debug(ray_debug, objects_debug);

				/*if (i == 316 && j == 170)
				{
					pixelColour_debug = ColourClass(0.0, 0.0, 0.0);
				}*/
				int breakpoint = 1;
				// Store the colour value
				pixels_debug[position_debug].SetRed(pixelColour_debug.GetRed());
				pixels_debug[position_debug].SetGreen(pixelColour_debug.GetGreen());
				pixels_debug[position_debug].SetBlue(pixelColour_debug.GetBlue());

				position_debug++;
			}
		}

		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> renderTime_debug = finish - start;

		SaveToFIle saveObject_debug = SaveToFIle();
		saveObject_debug.savebmp("scene_debug.bmp", imageWidth, imageHeight, 72, pixels_debug, whichTR);

		std::cout << "debug render: " << renderTime_debug.count() << "seconds" << std::endl;

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (choiceBrute) //brute-force
	{
		start = std::chrono::high_resolution_clock::now();

		renderObject.render(screenHeight, screenWidth, pixelW, pixelH, f, startPixel,
			camU, camV, originalCamera, parsedObject, lights, background, pointCol, pixelsBruteForce, maxDepth);

		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> bruteRender_time = finish - start;

		SaveToFIle saveObjectBruteForce = SaveToFIle();
		saveObjectBruteForce.savebmp("scene_Vishwanath_brute.bmp", screenWidth, screenHeight, 72, pixelsBruteForce, whichTR);

		std::cout << "brute force render: " << bruteRender_time.count() << "seconds" << std::endl;

		
	}


	if(choicekdtree) //kdtree
	{
		start = std::chrono::high_resolution_clock::now();

		renderObject.render(screenHeight, screenWidth, pixelW, pixelH, f, startPixel,
		camU, camV, originalCamera, kdtree, lights, background, pointCol, pixels, maxDepth);

		finish = std::chrono::high_resolution_clock::now();
 		std::chrono::duration<double> kdRender_time = finish - start;

		SaveToFIle saveObject = SaveToFIle();
		saveObject.savebmp("scene_Vishwanath.bmp", screenWidth, screenHeight, 72, pixels, whichTR);

		std::cout << "kd tree build: " << kdBuild_time.count() << "seconds" << std::endl;
		std::cout << "kd tree render: " << kdRender_time.count() << "seconds" << std::endl;
	}
	
	return 0;
}