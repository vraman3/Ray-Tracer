/**
	RayTracing, main.cpp
	The main class to execute the program.

	@author: Vishwanath Raman
	@version: 1.0 Oct/23/2017

*/

#include "IncludesList.h"
#include <chrono>

//typedef techsoft::matrix<double> Matrix;

int main(int argc, char *argv[])
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
	double worldWidth = 2 * 16 / 9, worldHeight = 2;

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
		screenHeight = 480;
		maxDepth = 5;
		whichTR = 3;
	}


#pragma region objects and their illumination models

	// The objects
	std::vector<TriangleClass*> objects;

	//objects.push_back(new SphereClass(0.9, VectorClass(2, 2.0, 12.0), ColourClass(1.0, 1.0, 1.0)));

	//objects.push_back(new SphereClass(0.8, VectorClass(3, 1.3, 13.9), ColourClass(1.0, 1.0, 1.0)));

	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300),
										VectorClass(5.5, 0.4, 22.0),
										VectorClass(0.2, 0.4, 22.0),
										ColourClass(0.0, 1.0, 0.0),
					  new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));

	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300),
										VectorClass(5.5, 0.4, 9.3),
										VectorClass(5.5, 0.4, 22.0),
										ColourClass(0.0, 1.0, 0.0),
					  new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));

	std::vector<ObjectClass*> objectsTraceRay;

	//objects.push_back(new SphereClass(0.9, VectorClass(2, 2.0, 12.0), ColourClass(1.0, 1.0, 1.0)));

	//objects.push_back(new SphereClass(0.8, VectorClass(3, 1.3, 13.9), ColourClass(1.0, 1.0, 1.0)));

	objectsTraceRay.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300),
										VectorClass(5.5, 0.4, 22.0),
										VectorClass(0.2, 0.4, 22.0),
										ColourClass(0.0, 1.0, 0.0),
					  new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));

	objectsTraceRay.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300),
										VectorClass(5.5, 0.4, 9.3),
										VectorClass(5.5, 0.4, 22.0),
										ColourClass(0.0, 1.0, 0.0),
					  new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));

	// The illuminations
	// The Lighting Models for the objects (has to be in SAME order as the objects)
	std::vector<IlluminationClass*> illuminations;

	//illuminations.push_back(	new PhongModel(0.3, 0.6, 0.1, 12.5, 0.0, 0.8) );

	//illuminations.push_back(	new PhongModel(0.3, 0.6, 0.3, 12.5, 0.5, 0.0) );

	illuminations.push_back(	new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0) );

	illuminations.push_back(	new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0) );
	
#pragma endregion

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

	cubeStraightObjects.push_back(new TriangleClass( cubeStraightPoints[1], cubeStraightPoints[3], cubeStraightPoints[0],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass( cubeStraightPoints[7], cubeStraightPoints[5], cubeStraightPoints[4],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[4], cubeStraightPoints[1], cubeStraightPoints[0],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[5], cubeStraightPoints[2], cubeStraightPoints[1],
		ColourClass(0.0, 1.0, 0.0)));

	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[2], cubeStraightPoints[7], cubeStraightPoints[3],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[0], cubeStraightPoints[7], cubeStraightPoints[4],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[1], cubeStraightPoints[2], cubeStraightPoints[3],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[7], cubeStraightPoints[6], cubeStraightPoints[5],
		ColourClass(0.0, 1.0, 0.0)));

	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[4], cubeStraightPoints[5], cubeStraightPoints[1],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[5], cubeStraightPoints[6], cubeStraightPoints[2],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[2], cubeStraightPoints[6], cubeStraightPoints[7],
		ColourClass(0.0, 1.0, 0.0)));
	cubeStraightObjects.push_back(new TriangleClass(cubeStraightPoints[0], cubeStraightPoints[3], cubeStraightPoints[7],
		ColourClass(0.0, 1.0, 0.0)));

#pragma endregion
	
#pragma region cubeStraightIllum
	std::vector<IlluminationClass*> cubeStraightIllum;

	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));

	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));

	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
	cubeStraightIllum.push_back(new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0));
#pragma endregion

#pragma region GLTraceRay
	std::vector<ObjectClass*> openGLTraceRay;

	//openGLTraceRay.push_back(new SphereClass(0.5, VectorClass(0, 0, 0), ColourClass(1.0, 0.5, 0.5)));

	openGLTraceRay.push_back(new TriangleClass(VectorClass(0, 0, 0), VectorClass(0.75, 0.75, 0),
		VectorClass(0, 0.75, 0), ColourClass(0.0, 1.0, 0.0)));
	//,		new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0)));


	std::vector<IlluminationClass*> illumOGLTraceRay;

	illumOGLTraceRay.push_back(	new PhongModel(0.3, 0.6, 0.1, 12.5, 0.0, 0.0) );
	
	//illumOGLTraceRay.push_back(new NoShadingModel(0,0)); // CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0)); //
# pragma endregion

#pragma region bruteForce

	
	// Objects
	std::vector<ObjectClass*> objectsForBruteForce;
	//objectsForBruteForce.push_back(new SphereClass(0.9, VectorClass(2, 2.0, 12.0), ColourClass(1.0, 1.0, 1.0)));
	//objectsForBruteForce.push_back(new SphereClass(0.8, VectorClass(3, 1.3, 13.9), ColourClass(1.0, 1.0, 1.0)));
	objectsForBruteForce.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));
	//objectsForBruteForce.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
		//VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));

	// Illuminations
	// The Lighting Models for the objects (has to be in SAME order as the objects)
	std::vector<IlluminationClass*> illuminationsForBruteForce;
	//illuminationsForBruteForce.push_back(new PhongModel(0.3, 0.6, 0.1, 12.5, 0.0, 0.8));
	//illuminationsForBruteForce.push_back(new PhongModel(0.3, 0.6, 0.3, 12.5, 0.5, 0.0));
	illuminationsForBruteForce.push_back(new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0));
	//illuminationsForBruteForce.push_back(new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0));
#pragma endregion

#pragma region KDTrees Object Loading
	ObjLoaderClass objFile = ObjLoaderClass();
	
	//objFile.readObjFile("icosphereObj.obj");
	objFile.readObjFile("cubeStraight.obj");
	//objFile.readObjFile("bunnyBlender_v2.obj");

	int noOfFaces = objFile.faces.size();

	std::vector<TriangleClass*> parsedObject;

	for (int i = 0; i < noOfFaces; i += 3)
	{
		//int tempVert1 = objFile.faces[i] - 1 ;
		//int tempVert2 = objFile.faces[i + 1] - 1;
		//int tempVert3 = objFile.faces[i + 2] - 1;

		parsedObject.push_back(new TriangleClass(objFile.opVertices[objFile.faces[i] - 1],
			objFile.opVertices[objFile.faces[i + 1] - 1],
			objFile.opVertices[objFile.faces[i + 2] - 1],
			ColourClass(0.0, 1.0, 0.0),
			new PhongModel(0.3, 0.6, 0.0, 12.5, 0.1, 0.0))); // new NoShadingModel(0, 0))); // 
	}

#pragma endregion

	std::vector<TriangleClass*> openGLCoordKDtrees;

	auto start = std::chrono::high_resolution_clock::now();

	KDNode kdtree = KDNode();
	kdtree = *kdtree.build(parsedObject, 3);

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> kdBuild_time = finish - start;
#pragma region Lights
	std::vector<VectorClass*> lights;

	lights.push_back(new VectorClass(5, 7.4, 9));
#pragma endregion

	
#pragma endregion

	
#pragma region background,screensize,camera
	ColourClass background(0.3, 0.8, 1.0);
	ColourClass pointCol(1.0, 1.0, 1.0);

	int filesize = screenWidth * screenHeight;
	ColourClass *pixels = new ColourClass[filesize];
	ColourClass* debugPixels = new ColourClass[filesize];

	VectorClass camPosition = VectorClass(0, 0, 8);
	VectorClass camLookAt = VectorClass(0, 0, 0);
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
	VectorClass camN = ( originalCamera.GetPosition() - originalCamera.GetLookAt() ).normalize();
	VectorClass camU = ( originalCamera.GetUpVector().crossProd(camN) ).normalize();
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
	VectorClass center( originalCamera.GetPosition().getX() - f * camN.getX(),
						originalCamera.GetPosition().getY() - f * camN.getY(),
						originalCamera.GetPosition().getZ() - f * camN.getZ());

	// The bottom leftmost point of the image plane
	VectorClass startPixel;

	startPixel.setX ( center.getX() - ( ( worldWidth * camU.getX() ) 
		+ ( worldHeight * camV.getX() ) ) / 2.0);
	startPixel.setY ( center.getY() - ( ( worldWidth * camU.getY() ) 
		+ ( worldHeight * camV.getY() ) ) / 2.0);
	startPixel.setZ ( center.getZ() - ( ( worldWidth * camU.getZ() )
		+ ( worldHeight * camV.getZ() ) ) / 2.0);

	double pixelW = worldWidth / screenWidth;
	double pixelH = worldHeight / screenHeight;
#pragma endregion 

	Render renderObject = Render();
	
	//renderObject.render(screenHeight, screenWidth, pixelW, pixelH, f, startPixel,
	//	camU, camV, originalCamera, openGLTraceRay, lights, illumOGLTraceRay, background, pointCol, pixels, maxDepth);

	start = std::chrono::high_resolution_clock::now();

	renderObject.render(screenHeight, screenWidth, pixelW, pixelH, f, startPixel,
		camU, camV, originalCamera, kdtree, lights, background, pointCol, pixels, maxDepth);
	
	finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> kdRender_time = finish - start;

	SaveToFIle saveObject = SaveToFIle();
	saveObject.savebmp("scene_Vishwanath.bmp", screenWidth, screenHeight, 72, pixels, whichTR);

	start = std::chrono::high_resolution_clock::now();

	renderObject.render(screenHeight, screenWidth, pixelW, pixelH, f, startPixel,
		camU, camV, originalCamera, cubeStraightObjects, lights, cubeStraightIllum, background, pointCol, debugPixels, maxDepth);

	finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> bruteRender_time = finish - start;

	SaveToFIle saveObjectDebug = SaveToFIle();
	saveObjectDebug.savebmp("scene_Vishwanath_brute.bmp", screenWidth, screenHeight, 72, debugPixels, whichTR);
	
	std::cout << "kd tree build: " << kdBuild_time.count() << "seconds" << std::endl;
	std::cout << "kd tree render: " << kdRender_time.count() << "seconds" << std::endl;
	std::cout << "brute force render: " << bruteRender_time.count() << "seconds" << std::endl;
	// Read and write from a bmp file
	//////ReadFromFile *readObj = new ReadFromFile();
	//////int start = 0, testCounter1 = 0;
	//////
	//////ColourClass *testwrite;
	//////testwrite = readObj->ReadBMP("Texturemaps/24-640x480.bmp");
	//////for (int i = 0; i < 512; i++)
	//////{
	//////	for (int j = 0; j < 384; j++)
	//////	{
	//////		if (testCounter1 < 20)
	//////		{
	//////			//std::cout << testwrite[start].GetRed() << " " << testwrite[start].GetGreen() << " " << testwrite[start].GetBlue() << std::endl;
	//////			testCounter1++;
	//////		}
	//////		start++;
	//////	}
	//////}
	////////std::cout << readObj->GetWidth() << std::endl;
	//////savebmp("testwrite.bmp", readObj->GetWidth(), readObj->GetHeight(), 72, testwrite);
	//delete testwrite;
	return 0;
}