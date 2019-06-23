/**
	RayTracing, main.cpp
	The main class to execute the program.

	@author: Vishwanath Raman
	@version: 1.0 Oct/23/2017

*/

#include "IncludesList.h"
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
		/* From File
		screenWidth = 64
		screenHeight = 48;
		*/
		
		screenWidth = 640;
		screenHeight = 480;
		maxDepth = 5;
		whichTR = 3;
	}

	/*Matrix4x4 mtest = Matrix4x4(1, 0, -5, 4, 1, 4, 3, 4, 8, 2, 1, 5, 7, 2, 3, 1);
	
	Matrix4x4 invM = mtest.Inverse();

	std::cout << invM;*/

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

	std::vector<ObjectClass*> trianglesForBruteForce;

	trianglesForBruteForce.push_back(new TriangleClass(VectorClass(0, 0, 0), VectorClass(1, 1, 0),
		VectorClass(0, 1, 0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0)));

	
#pragma region GLTraceRay
	std::vector<ObjectClass*> openGLTraceRay;

	//openGLTraceRay.push_back(new SphereClass(0.1, VectorClass(0, 0.5, 0), ColourClass(1.0, 0.5, 0.5)));

	openGLTraceRay.push_back(new TriangleClass(VectorClass(0, 0, 0), VectorClass(1, 1, 0),
		VectorClass(0, 1, 0), ColourClass(0.0, 1.0, 0.0)));
	//,		new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0)));


	std::vector<IlluminationClass*> illumOGLTraceRay;

	//illumOGLTraceRay.push_back(	new PhongModel(0.3, 0.6, 0.1, 12.5, 0.0, 0.0) );
	
	illumOGLTraceRay.push_back(new NoShadingModel(0,0)); // CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0)); //
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

	objFile.readObjFile("cubeStraight.obj");

	int noOfFaces = objFile.faces.size();

	std::vector<TriangleClass*> bunnyObjects;

	for (int i = 0; i < noOfFaces / 3; i++)
	{
		bunnyObjects.push_back(new TriangleClass(objFile.opVertices[objFile.faces[i] - 1],
			objFile.opVertices[objFile.faces[i + 1] - 1],
			objFile.opVertices[objFile.faces[i + 2] - 1],
			ColourClass(0.0, 1.0, 0.0),
			new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));
	}

	// std::vector<TriangleClass*> convObjects;	
#pragma endregion

	std::vector<TriangleClass*> openGLCoordKDtrees;

	openGLCoordKDtrees.push_back(new TriangleClass(VectorClass(0, 0, 0), VectorClass(0.5, 0.5, 0),
		VectorClass(0, 0.5, 0), ColourClass(0.0, 1.0, 0.0), new NoShadingModel(0, 0))); // new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0)));

	KDNode kdtree = KDNode();
	kdtree = *kdtree.build(openGLCoordKDtrees, 10);

	bool kdTreeChoice = 1;
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

	VectorClass camPosition = VectorClass(0, 0, 4);
	VectorClass camLookAt = VectorClass(0, 0, 0);
	double f = 1;

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

	// For multisampling
	//double pw2 = pixelW / 2;
	//double ph2 = pixelH / 2;

	int position = 0, testCounter = 0;
	int noOfSamples = 4;

	Tracing traceObject = Tracing();
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			ColourClass tmp = ColourClass(0, 0, 0);
			
			VectorClass val = VectorClass(startPixel.getX() + camU.getX() * (j + 0.5) * pixelW + camV.getX() * (i + 0.5) * pixelH,
										  startPixel.getY() + camU.getY() * (j + 0.5) * pixelW + camV.getY() * (i + 0.5) * pixelH,
										  -f);

			VectorClass direction = (val - originalCamera.GetPosition()).normalize();
			RayClass ray(originalCamera.GetPosition(), direction);
			
			/*
			 0 = Regular ray tracing. Brute Force.
			 1 = Use KD trees.
			 2 = Use any other integer to skip following conditions.
			*/


			

			if (kdTreeChoice == 0)
			{
				ColourClass debugTmpRemoveLater;

				if (i == 153 && j == 150)
					bool somethingTest = 0;
				//Working scene. For debugging.
				debugTmpRemoveLater = traceObject.TraceRay(ray, 0, 1.0, openGLTraceRay, lights, illumOGLTraceRay, background, pointCol, maxDepth);
								//debugTmpRemoveLater = traceObject.TraceRay(ray, 0, 1.0, objectsTraceRay, lights, illuminations, background, pointCol, maxDepth);

				if (debugTmpRemoveLater.GetGreen() == 1)
					bool testIfGreen = false;
				double rt = debugTmpRemoveLater.GetRed();
				double gt = debugTmpRemoveLater.GetGreen();
				double bt = debugTmpRemoveLater.GetBlue();
				tmp = tmp + debugTmpRemoveLater;
			}
			else if (kdTreeChoice == 1)
			{
				ColourClass debugTmpKDRemoveLater;
				debugTmpKDRemoveLater = traceObject.TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);;
				
				double rt = debugTmpKDRemoveLater.GetRed();
				double gt = debugTmpKDRemoveLater.GetGreen();
				double bt = debugTmpKDRemoveLater.GetBlue();
				tmp = tmp + debugTmpKDRemoveLater;
			}
			
#pragma region multisampling
			/*//Multisampling using 4 points for a pixel
			
			VectorClass val1 = VectorClass(val.getX() - pw2, val.getY() + ph2, val.getZ());
			VectorClass val2 = VectorClass(val.getX() + pw2, val.getY() + ph2, val.getZ());
			VectorClass val3 = VectorClass(val.getX() + pw2, val.getY() - ph2, val.getZ());
			VectorClass val4 = VectorClass(val.getX() - pw2, val.getY() - ph2, val.getZ());

			VectorClass direction1 = (val1 - originalCamera.GetPosition()).normalize();
			VectorClass direction2 = (val2 - originalCamera.GetPosition()).normalize();
			VectorClass direction3 = (val3 - originalCamera.GetPosition()).normalize();
			VectorClass direction4 = (val4 - originalCamera.GetPosition()).normalize();

			RayClass ray1(originalCamera.GetPosition(), direction1);
			RayClass ray2(originalCamera.GetPosition(), direction2);
			RayClass ray3(originalCamera.GetPosition(), direction3);
			RayClass ray4(originalCamera.GetPosition(), direction4);

			ColourClass debugTmpRemoveLater1 = TraceRay(ray1, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater1;
			ColourClass debugTmpRemoveLater2 = TraceRay(ray2, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater2;
			ColourClass debugTmpRemoveLater3 = TraceRay(ray3, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater3;
			ColourClass debugTmpRemoveLater4 = TraceRay(ray4, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater4;

			tmp = tmp / (noOfSamples);*/
#pragma endregion
						
			pixels[position].SetRed(tmp.GetRed());
			pixels[position].SetGreen(tmp.GetGreen());
			pixels[position].SetBlue(tmp.GetBlue());
			
			position++;
		}
	}
	SaveToFIle saveObject = SaveToFIle();
	saveObject.savebmp("C:/Users/Vishwanath/Desktop/scene_Vishwanath.bmp", screenWidth, screenHeight, 72, pixels, whichTR);

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