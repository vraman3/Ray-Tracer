
//Author: Vishwanath Raman

#include <vector>
#include <iostream>
#include <math.h>
#include <cstdlib>
//#include <cmatrix>
#include "VectorClass.h"
#include "CameraClass.h"
#include "RayClass.h"
#include "CameraClass.h"
#include "SphereClass.h"
#include "TriangleClass.h"
#include "PlaneClass.h"
#include "AABBClass.h"
#include "IlluminationClass.h"
#include "PhongModel.h"
#include "PhongBlinnModel.h"
#include "StraussModel.h"
#include "NoShadingModel.h"
#include "CheckerboardPattern.h"
#include "SaveToFile.h"
#include "ReadFromFile.h"
#include "KDNode.h"
#include "IntersectionInfo.h"
#include "ObjLoaderClass.h"
#include "MatrixClass.h"
//typedef techsoft::matrix<double> Matrix;

ColourClass TraceRay(RayClass, int, double, std::vector<ObjectClass*>, std::vector<VectorClass*>,
	std::vector<IlluminationClass*>, ColourClass, ColourClass, int);

ColourClass TraceRayKD(RayClass, int, double, KDNode kdtree, std::vector<VectorClass*>,
	ColourClass, ColourClass, int);

// Shift these two functions to Camera later after testing
MatrixClass viewPort(int x, int y, int w, int h, int depth);
MatrixClass lookAt(VectorClass eye, VectorClass centre, VectorClass up);

int main(int argc, char *argv[])
{
#pragma region start
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

	std::vector<TriangleClass*> testObjects;
	testObjects.push_back(new TriangleClass(VectorClass(1.2, 0.4, 3.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0)));
	/*testObjects.push_back(new TriangleClass(VectorClass(0.0, 0.5, 0.0), VectorClass(1.5, 0.5, 1.5),
	VectorClass(1.5,0.5,0.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)));*/
	/*testObjects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
	VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)));*/


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
#pragma endregion


	std::vector<VectorClass*> lights;

	lights.push_back(new VectorClass(5, 7.4, 9));

	ColourClass background(0.3, 0.8, 1.0);
	ColourClass pointCol(1.0, 1.0, 1.0);
#pragma endregion


	int filesize = screenWidth * screenHeight;
	ColourClass *pixels = new ColourClass[filesize];

	VectorClass eye(0,0,-1);//(1.0, 1.0, 3.0);
	VectorClass centreNew(2,2,120);

	VectorClass camPosition = eye;//VectorClass(1.5, 3, 1);
	VectorClass camLookAt = centreNew;// VectorClass(2, 2, 120);
	double f = 3.0;

	

	/*MatrixClass modelView = lookAt(eye, centreNew, VectorClass(0, 1, 0));
	MatrixClass projection = MatrixClass::identity(4);
	MatrixClass viewport = viewPort(screenWidth / 8, screenHeight / 8, screenWidth * 3 / 4, screenHeight * 3 / 4, 255);

	projection[3][2] = -1 / ((eye - centreNew).magnitude());*/

	

	/*for (int i = 0; i < objects.size(); i++)
	{
		VectorClass screenCoord[3];

		for (int j = 0; j < 3; j++)
		{
			VectorClass v = (*objects[i])[j];
			
			screenCoord[j] = (viewport*projection*modelView*MatrixClass(v)).toVector();
		}

		convObjects.push_back(new TriangleClass(screenCoord[0], screenCoord[1], screenCoord[2],
					ColourClass(0.0, 1.0, 0.0), new PhongModel(0.3, 0.6, 0.3, 12.5, 0.0, 0.0, 1.0)));
	}*/

	KDNode kdtree = KDNode();

	kdtree = *kdtree.build(objects, 10);


	// Calculate the Camera parameters
	VectorClass camRight = camLookAt.normalize().crossProd(VectorClass(0, 1, 0));
	VectorClass camUp = camRight.crossProd(camLookAt);
	//VectorClass camUp = VectorClass(0,1,0);
	CameraClass originalCamera = CameraClass(camPosition, camLookAt, VectorClass(0, 1, 0), f);


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

			debugTmpRemoveLater = TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);;
			//TraceRay(ray, 0, 1.0, objects, lights, illuminations, background, pointCol, maxDepth);
			double rt = debugTmpRemoveLater.GetRed();
			double gt = debugTmpRemoveLater.GetGreen();
			double bt = debugTmpRemoveLater.GetBlue();
			//if (rt != 0.3)
			//{
			//	//std::cout << rt << "/" << gt << "/" << bt << " ";
			//	std::cout << " " << i << " "<< j << " -- ";
			//}
			tmp = tmp + debugTmpRemoveLater;

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

			pixels[position].SetRed(tmp.GetRed());
			pixels[position].SetGreen(tmp.GetGreen());
			pixels[position].SetBlue(tmp.GetBlue());
			
			position++;
		}
		//std::cout << " eol " << std::endl;
	}
	SaveToFile saveObject = SaveToFile();
	saveObject.savebmp("scene_Vishwanath.bmp", screenWidth, screenHeight, 72, pixels, whichTR);

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

MatrixClass viewPort(int x, int y, int w, int h, int depth)
{
	MatrixClass vp = MatrixClass::identity(4);
	vp[0][3] = x + (w / 2.0);
	vp[1][3] = y + (h / 2.0);
	vp[2][3] = depth / 2.0;

	vp[0][0] = w / 2.0;
	vp[1][1] = h / 2.0;
	vp[2][2] = depth / 2.0;
	return vp;
}

MatrixClass lookAt(VectorClass eye, VectorClass centre, VectorClass up)
{
	//std::cout << "lookat" << std::endl;
	VectorClass z = (eye - centre).normalize();
	VectorClass x = (up.crossProd(z)).normalize();
	VectorClass y = (z.crossProd(x)).normalize();

	MatrixClass result = MatrixClass::identity(4);

	for (int i = 0; i < 3; i++)
	{
		result[0][i] = x[i];
		result[1][i] = y[i];
		result[2][i] = z[i];
		result[i][3] = -centre[i];
	}
	//std::cout << "lookat end";
	return result;
}

ColourClass TraceRayKD(RayClass ray, int depth, double incomingni, KDNode kdtree, std::vector<VectorClass*> lights,ColourClass background, ColourClass pointCol, int maxDepth)
{
	//double currentLowestVal = 1000000;
	double omega = 0.0;
	int closest = -1;
	ColourClass tmp = ColourClass(0, 0, 0);

	intersectionInfo isect;

	//int omegaCounter = 0;
	
	/*int objectsSize = (int)objects.size();
	for (int objNo = 0; objNo < objectsSize; objNo++)
	{
		omega = objects[objNo]->GetIntersection(ray);
		if (omega == -1)
		{
			continue;
		}
		else
		{
			if (omega < currentLowestVal)
			{
				closest = objNo;
				currentLowestVal = omega;
			}
		}
	}*/
	isect.flag = false;
	isect.hit = -1;
	isect.tri = NULL;

	isect = kdtree.Traverse(ray, isect);
	if (!isect.flag)
	{
		return background;
	}
	else
	{
		//std::cout << "bla";
		bool noShadow = true;
		VectorClass pi = ray.GetRayOrigin() + ray.GetRayDirection() * isect.hit;
		VectorClass N = (isect.tri->GetNormal(pi)).normalize();

		VectorClass V = (ray.GetRayOrigin() - pi).normalize();
		double shade = 1.0;
		int lightsSize = (int)lights.size();
		for (int g = 0; g < lightsSize; g++)
		{
			double shadowOmega = 0.0;
			VectorClass shadowRayDirection = (*lights[g] - pi).normalize();

			RayClass shadowRay(pi, shadowRayDirection);

			noShadow = true;

			intersectionInfo shadowIsect;
			shadowIsect.flag = false;
			shadowIsect.hit = -1;
			shadowIsect.tri = NULL;

			shadowIsect = kdtree.Traverse(shadowRay, shadowIsect);
			double shadowObjkt;

			if (shadowIsect.flag)
			{
				shadowObjkt = shadowIsect.tri->illum->getTransmissivitykt();
				if (shadowObjkt > 0.0)
					shade += 1 - shadowObjkt;
				else
					shade += 1;
				break;
			}
			
			VectorClass L = ((*lights[g]) - pi).normalize();

			tmp = tmp + isect.tri->illum->getIllumination(pi, ray, N, L, V, isect.tri->GetColour(), pointCol, maxDepth) / shade;

			//}
		}

		if (depth < maxDepth)
		{
			double reflectKr = isect.tri->illum->getReflectivitykr();
			double transmiKt = isect.tri->illum->getTransmissivitykt();

			if (reflectKr > 0.0)
			{
				VectorClass refRayDirection = isect.tri->illum->Reflect(ray.GetRayDirection(), N);

				RayClass refRay = RayClass(pi, refRayDirection);

				tmp = tmp + TraceRayKD(refRay, depth + 1, incomingni, kdtree, lights, background, pointCol, maxDepth) * reflectKr;
			}

			if (transmiKt > 0.0)
			{
				VectorClass I = ray.GetRayDirection().normalize()*(-1);
				//VectorClass I = pi - VectorClass(2.5, 4, 0);
				double outgoingnt = isect.tri->illum->getNormal();

				VectorClass transRayDirection;
				double niToBePassed;

				//
				//	FIXED.... FORGOT TO MULTIPLY DIRECTION(I) BY (-1)
				if (incomingni == outgoingnt)
				{
					transRayDirection = I*(-1);
					niToBePassed = outgoingnt;

					//std::cout << "nobending " << depth << std::endl;
				}
				/*if (true)*/else
				{
					bool flag = true;
					double dotNI = N.dotProd(I);
					double nr = incomingni / outgoingnt;

					if (dotNI < 0)
					{
						N = N * (-1);
						dotNI = -dotNI;
						nr = incomingni;
						flag = false;
					}

					double rootTerm = 1 - (nr*nr)*(1 - (dotNI)*(dotNI));

					if (rootTerm >= 0)
					{
						//std::cout << "Bending" << std::endl;
						double nrdotNI = nr*(dotNI);

						double tempTerm = nrdotNI - sqrt(rootTerm);

						transRayDirection = N * tempTerm - I * nr;

						if (flag)
							niToBePassed = 1.0;
						else
							niToBePassed = outgoingnt;
					}
					else
					{
						//std::cout << "TotalIntReflection" << std::endl;
						transRayDirection = isect.tri->illum->Reflect(I*(-1), N);
						niToBePassed = incomingni;
					}
				}

				RayClass transRay = RayClass(pi, transRayDirection);
				tmp = tmp + TraceRayKD(transRay, depth + 1, niToBePassed, kdtree, lights, background, pointCol, maxDepth) * transmiKt;
			}
		}
		return tmp;
	}
}


ColourClass TraceRay(RayClass ray, int depth, double incomingni, std::vector<ObjectClass*> objects, std::vector<VectorClass*> lights,
	std::vector<IlluminationClass*> illuminations, ColourClass background, ColourClass pointCol, int maxDepth)
{
	double currentLowestVal = 1000000;
	double omega = 0.0;
	int closest = -1;
	ColourClass tmp = ColourClass(0, 0, 0);

	int omegaCounter = 0;
	int objectsSize = (int)objects.size();
	for (int objNo = 0; objNo < objectsSize ; objNo++)
	{
		omega = objects[objNo]->GetIntersection(ray);
		if (omega == -1)
		{
			continue;
		}
		else
		{
			if (omega < currentLowestVal)
			{
				closest = objNo;
				currentLowestVal = omega;
			}
		}
	}
	if (closest == -1)
	{
		//if (depth != 0)
		//std::cout << depth << std::endl;
		return background;
	}
	else
	{
		bool noShadow = true;
		VectorClass pi = ray.GetRayOrigin() + ray.GetRayDirection() * currentLowestVal;
		VectorClass N = (objects[closest]->GetNormal(pi)).normalize();

		VectorClass V = (ray.GetRayOrigin() - pi).normalize();
		double shade = 1.0;
		int lightsSize = (int)lights.size();
		for (int g = 0; g < lightsSize; g++)
		{
			double shadowOmega = 0.0;
			VectorClass shadowRayDirection = (*lights[g] - pi).normalize();

			RayClass shadowRay(pi, shadowRayDirection);

			noShadow = true;
			for (int shadowObj = 0; shadowObj < objectsSize; shadowObj++)
			{
				shadowOmega = objects[shadowObj]->GetIntersection(shadowRay);
				double objkt = illuminations[shadowObj]->getTransmissivitykt();
				//std::cout << shadowOmega << " ";
				if (shadowOmega > 0.00001)
					//if (false)					// Use this to disable shadows. Comment the "if" condition above.
				{
					//if (shadowOmega <= shadowRayDirection.magnitude())
					//{
					noShadow = false;
					//break;.......
					if (objkt > 0.0)
						shade += 1 - objkt;
					else
						shade += 1;
					break;
					//}
				}  
			}
			//if (noShadow)
			//{
			VectorClass L = ((*lights[g]) - pi).normalize();

			tmp = tmp + illuminations[closest]->getIllumination(pi, ray, N, L, V, (*objects[closest]).GetColour(), pointCol, maxDepth) / shade;

			//}
		}

		if (depth < maxDepth)
		{
			double reflectKr = illuminations[closest]->getReflectivitykr();
			double transmiKt = illuminations[closest]->getTransmissivitykt();

			if (reflectKr > 0.0)
			{
				VectorClass refRayDirection = illuminations[closest]->Reflect(ray.GetRayDirection(), N);

				RayClass refRay = RayClass(pi, refRayDirection);

				tmp = tmp + TraceRay(refRay, depth + 1, incomingni, objects, lights, illuminations, background, pointCol, maxDepth) * reflectKr;
			}

			if (transmiKt > 0.0) 
			{
				VectorClass I = ray.GetRayDirection().normalize()*(-1);
				//VectorClass I = pi - VectorClass(2.5, 4, 0);
				double outgoingnt = illuminations[closest]->getNormal();

				VectorClass transRayDirection;
				double niToBePassed;

				//
				//	FIXED.... FORGOT TO MULTIPLY DIRECTION(I) BY (-1)
				if (incomingni == outgoingnt)
				{
					transRayDirection = I*(-1);
					niToBePassed = outgoingnt;

					//std::cout << "nobending " << depth << std::endl;
				}
				/*if (true)*/else
				{
					bool flag = true;
					double dotNI = N.dotProd(I);
					double nr = incomingni / outgoingnt;

					if (dotNI < 0)
					{
						N = N * (-1);
						dotNI = -dotNI;
						nr = incomingni;
						flag = false;
					}

					double rootTerm = 1 - (nr*nr)*(1 - (dotNI)*(dotNI));

					if (rootTerm >= 0)
					{
						//std::cout << "Bending" << std::endl;
						double nrdotNI = nr*(dotNI);

						double tempTerm = nrdotNI - sqrt(rootTerm);

						transRayDirection = N * tempTerm - I * nr;

						if (flag)
							niToBePassed = 1.0;
						else
							niToBePassed = outgoingnt;
					}
					else
					{
						//std::cout << "TotalIntReflection" << std::endl;
						transRayDirection = illuminations[closest]->Reflect(I*(-1), N);
						niToBePassed = incomingni;
					}
				}

				RayClass transRay = RayClass(pi, transRayDirection);
				tmp = tmp + TraceRay(transRay, depth + 1, niToBePassed, objects, lights, illuminations, background, pointCol, maxDepth) * transmiKt;
			}
		}
		return tmp;
	}
}