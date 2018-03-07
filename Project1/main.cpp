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
		
		screenWidth = 1400;
		screenHeight = 900;
		maxDepth = 5;
		whichTR = 3;
	}
	//  Tone Reproduction Operator
	//
	//  1 - Ward 
	//  2 - Reinhard
	//  3 - Adaptive Logarithmic
	//  0 - No Tone Reproduction (By Default)

	//int screenWidth = 1400, screenHeight = 900;
	//int screenWidth = 640, screenHeight = 480;
	//int screenWidth = 320, screenHeight = 240;
	//int screenWidth = 64, screenHeight = 48;

	// The list of objects
	std::vector<TriangleClass*> objects;
	//objects.push_back(new SphereClass(0.9, VectorClass(2, 2.0, 12.0), ColourClass(1.0, 1.0, 1.0)));
	//objects.push_back(new SphereClass(0.8, VectorClass(3, 1.3, 13.9), ColourClass(1.0, 1.0, 1.0)));
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
		VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));

	std::vector<ObjectClass*> objectsForBruteForce;
	//objects.push_back(new SphereClass(0.9, VectorClass(2, 2.0, 12.0), ColourClass(1.0, 1.0, 1.0)));
	//objects.push_back(new SphereClass(0.8, VectorClass(3, 1.3, 13.9), ColourClass(1.0, 1.0, 1.0)));
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
		VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0)));

	/*
	From file
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0)));
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
		VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0)));
	*/
	std::vector<TriangleClass*> testObjects;
	testObjects.push_back(new TriangleClass(VectorClass(1.2, 0.4, 3.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0)));
	/*testObjects.push_back(new TriangleClass(VectorClass(0.0, 0.5, 0.0), VectorClass(1.5, 0.5, 1.5),
	VectorClass(1.5,0.5,0.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)));*/
	/*testObjects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
	VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)));*/

	
#pragma region illuminations
	// The Lighting Models for the objects (has to be in SAME order as the objects)
	std::vector<IlluminationClass*> illuminations;
	//illuminations.push_back(
	//	/*new StraussModel(0.3, 0.3, 0.1, 0.0, 0.0, 0.0)*/
	//	new PhongModel(0.3, 0.6, 0.1, 12.5, 0.0, 0.8, 0.98)
	//	/*new NoShadingModel(0.0, 0.0, 1.0)*/ );
	//illuminations.push_back(
	//	new PhongModel(0.3, 0.6, 0.3, 12.5, 0.5, 0.0, 1.0)
	//	/*new NoShadingModel(0.0, 0.0, 1.0)*/);
	illuminations.push_back(
		new CheckerboardPattern(320, 240, 0.0, 0.0)
		/*new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0, 1.0)*/
		/*new NoShadingModel(0.0, 0.0, 1.0)*/);
	illuminations.push_back(
		new CheckerboardPattern(320, 240, 0.0, 0.0)
		/*new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0, 1.0)*/
		/*new NoShadingModel(0.0, 0.0, 1.0)*/);

	/* From File
	illuminations.push_back(
		new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0, 1.0)
		/*new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0, 1.0));
		//new NoShadingModel(0.0, 0.0, 1.0));
	illuminations.push_back(
		new CheckerboardPattern(screenWidth, screenHeight, 0.0, 0.0, 1.0));
		//new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0, 1.0)
		//new NoShadingModel(0.0, 0.0, 1.0)/
	
	*/
#pragma endregion

	ObjLoaderClass objFile = ObjLoaderClass();

	objFile.readObjFile("bunny.obj");

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

	std::vector<TriangleClass*> convObjects;



	std::vector<VectorClass*> lights;

	lights.push_back(new VectorClass(5, 7.4, 9));

	ColourClass background(0.3, 0.8, 1.0);
	ColourClass pointCol(1.0, 1.0, 1.0);
#pragma endregion


	int filesize = screenWidth * screenHeight;
	ColourClass *pixels = new ColourClass[filesize];

	VectorClass eye(0,0,-1);//(1.0, 1.0, 3.0);
	VectorClass centreNew(2,2,120);

	//VectorClass camPosition = VectorClass(0, 0, -1);//eye;//VectorClass(1.5, 3, 1);
	//VectorClass camLookAt = VectorClass(); //centreNew;// VectorClass(2, 2, 120);
	//double f = 3.0;

	// From File
	VectorClass camPosition = VectorClass(2.5, 3, 0);
	VectorClass camLookAt = VectorClass(2.5, 2, 120);
	double f = 3.0;
	

	KDNode kdtree = KDNode();

	kdtree = *kdtree.build(objects, 10);


	// Calculate the Camera parameters
	VectorClass camRight = camLookAt.normalize().crossProd(VectorClass(0, 1, 0));
	VectorClass camUp = camRight.crossProd(camLookAt);
	//VectorClass camUp = VectorClass(0,1,0);
	CameraClass originalCamera = CameraClass(camPosition, camLookAt, VectorClass(0, 1, 0), f);

	/* From File
	VectorClass camRight = camLookAt.Normalize().CrossProd(VectorClass(0, 1, 0));
	//VectorClass camUp = camRight.CrossProd(camLookAt);
	VectorClass camUp = VectorClass(0,1,0);
	CameraClass originalCamera = CameraClass(camPosition, camLookAt, camUp, f);
	*/

	VectorClass camN = (originalCamera.GetPosition() - originalCamera.GetLookAt()).normalize();
	VectorClass camU = (camN.crossProd(originalCamera.GetUpVector())).normalize();
	VectorClass camV = camU.crossProd(camN);
	
	// Calculate center pixel of image plane
	VectorClass center( originalCamera.GetPosition().getX() + f * camN.getX(),
						originalCamera.GetPosition().getY() + f * camN.getY(),
						originalCamera.GetPosition().getZ() + f * camN.getZ());

	// The bottom leftmost point of the image plane
	VectorClass startPixel;

	startPixel.setX(center.getX() - ((worldWidth * camU.getX()) + (worldHeight*camV.getX())) / 2.0);
	startPixel.setY(center.getY() - ((worldWidth * camU.getY()) + (worldHeight*camV.getY())) / 2.0);
	startPixel.setZ(originalCamera.GetFocalLength());

	double pixelW = worldWidth / screenWidth;
	double pixelH = worldHeight / screenHeight;

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
										  startPixel.getZ() + camU.getZ() * (j + 0.5) * pixelW + camV.getZ() * (i + 0.5) * pixelH);

			VectorClass direction = (val - originalCamera.GetPosition()).normalize();
			RayClass ray(originalCamera.GetPosition(), direction);
			
			ColourClass debugTmpRemoveLater;
			//debugTmpKDRemoveLater = traceObject.TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);;
			debugTmpRemoveLater = traceObject.TraceRay(ray, 0, 1.0, objectsForBruteForce, lights, illuminations, background, pointCol, maxDepth);

			//TraceRay(ray, 0, 1.0, objects, lights, illuminations, background, pointCol, maxDepth);
			double rt = debugTmpRemoveLater.GetRed();
			double gt = debugTmpRemoveLater.GetGreen();
			double bt = debugTmpRemoveLater.GetBlue();

			// This was for the VS push. Delete this comment line later.

			//if (rt != 0.3)
			//{
			//	//std::cout << rt << "/" << gt << "/" << bt << " ";
			//	std::cout << " " << i << " "<< j << " -- ";
			//}
			tmp = tmp + debugTmpRemoveLater;

			/*
			 0 = Regular ray tracing. Brute Force.
			 1 = Use KD trees.
			 2 = Use any other integer to skip following conditions.
			*/


			////bool choice = 0;

			////if (choice == 0)
			////{
			////	ColourClass debugTmpRemoveLater;

			////	debugTmpRemoveLater = traceObject.TraceRay(ray, 0, 1.0, objectsForBruteForce, lights, illuminations, background, pointCol, maxDepth);

			////	//TraceRay(ray, 0, 1.0, objects, lights, illuminations, background, pointCol, maxDepth);
			////	double rt = debugTmpRemoveLater.GetRed();
			////	double gt = debugTmpRemoveLater.GetGreen();
			////	double bt = debugTmpRemoveLater.GetBlue();
			////	//if (rt != 0.3)
			////	//{
			////	//	//std::cout << rt << "/" << gt << "/" << bt << " ";
			////	//	std::cout << " " << i << " "<< j << " -- ";
			////	//}
			////	tmp = tmp + debugTmpRemoveLater;
			////}
			////else if (choice == 1)
			////{
			////	ColourClass debugTmpKDRemoveLater;
			////	debugTmpKDRemoveLater = traceObject.TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);;
			////	
			////	//TraceRay(ray, 0, 1.0, objects, lights, illuminations, background, pointCol, maxDepth);
			////	double rt = debugTmpKDRemoveLater.GetRed();
			////	double gt = debugTmpKDRemoveLater.GetGreen();
			////	double bt = debugTmpKDRemoveLater.GetBlue();
			////	//if (rt != 0.3)
			////	//{
			////	//	//std::cout << rt << "/" << gt << "/" << bt << " ";
			////	//	std::cout << " " << i << " "<< j << " -- ";
			////	//}
			////	tmp = tmp + debugTmpKDRemoveLater;
			////}



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
		//std::cout << " eol " << std::endl;
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