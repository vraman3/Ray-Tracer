
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
#include "SaveToFIle.h"
#include "ReadFromFile.h"
#include "KDNode.h"
#include "IntersectionInfo.h"
//typedef techsoft::matrix<double> Matrix;

ColourClass TraceRay(RayClass, int, double, std::vector<ObjectClass*>, std::vector<VectorClass*>,
	std::vector<IlluminationClass*>, ColourClass, ColourClass, int);

ColourClass TraceRayKD(RayClass, int, double, KDNode kdtree, std::vector<VectorClass*>,
	ColourClass, ColourClass, int);


int main(int argc, char *argv[])
{
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
		std::cout << " Width:"<<argv[1] << "  Height:" << argv[2] << " Max Depth:" << argv[3] << " ToneReproduction:" << argv[4] <<std::endl;
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
	std::vector<ObjectClass*> objects;
	//objects.push_back(new SphereClass(0.9, VectorClass(2, 2.0, 12.0), ColourClass(1.0, 1.0, 1.0)));
	//objects.push_back(new SphereClass(0.8, VectorClass(3, 1.3, 13.9), ColourClass(1.0, 1.0, 1.0)));
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0)));
	objects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
		VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0)));
	
	std::vector<TriangleClass*> testObjects;
	testObjects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 22.0),
		VectorClass(0.2, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)));
	testObjects.push_back(new TriangleClass(VectorClass(0.2, 0.4, 9.300), VectorClass(5.5, 0.4, 9.3),
		VectorClass(5.5, 0.4, 22.0), ColourClass(0.0, 1.0, 0.0), new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)));

	KDNode kdtree = KDNode();

	kdtree = *kdtree.build(testObjects, 4);

	/*
	#define MAX_TODO 64
	KDToDo todo[MAX_TODO];
	int todoPos = 0;
	
	todo[todoPos].node = secondChild;
	todo[todoPos].tminTD = tplane;
	todo[todoPos].tmaxTD = tmax;
	++todoPos;
			
	if (todoPos > 0)
	{
		--todoPos;
		nodeT = todo[todoPos].node;
		tmin = todo[todoPos].tminTD;
		tmax = todo[todoPos].tmaxTD;
	}
	else
		break;
	*/
	//struct tempKD
	//{
	//	KDNode *node;
	//};
	//tempKD stack[64];
	//int stackPos = 0;

	//while (tempNode->splitAxis != 3)
	//{
	//	//std::cout << " a " << tempNode->objects.size() << std::endl;
	//	if (tempNode->splitAxis == 3)
	//		std::cout << " a " << tempNode->objects.size() << std::endl;

	//	/*if (tempNode->left->objects.size() != NULL)
	//	{
	//		std::cout << " l " << std::endl;*/
	//		stack[stackPos].node = tempNode->left;
	//		++stackPos;
	//	/*}
	//	if (tempNode->right->objects.size() != NULL)
	//	{
	//		std::cout << " r " << std::endl;*/
	//		stack[stackPos].node = tempNode->right;
	//		++stackPos;
	//	//}

	//	if (stackPos > 0)
	//	{
	//		--stackPos;
	//		tempNode = stack[stackPos].node;
	//	}
	//	else
	//		break;
	//}



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
		new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)
		/*new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0, 1.0)*/
		/*new NoShadingModel(0.0, 0.0, 1.0)*/);
	illuminations.push_back(
		new CheckerboardPattern(320, 240, 0.0, 0.0, 1.0)
		/*new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0, 1.0)*/
		/*new NoShadingModel(0.0, 0.0, 1.0)*/);

	std::vector<VectorClass*> lights;

	lights.push_back(new VectorClass(5, 7.4, 9));

	ColourClass background(0.3 , 0.8, 1.0);
	ColourClass pointCol(1.0, 1.0, 1.0);	

	int filesize = screenWidth * screenHeight;
	ColourClass *pixels = new ColourClass[filesize];

	VectorClass camPosition = VectorClass(1.5, 3, 1);
	VectorClass camLookAt = VectorClass(2, 2, 120);
	double f = 3.0;


	// Unused. Left for future clean build
	//double scale = tan(90 * 3.1415925 / 180);
	//double imageAspectRatio = screenWidth / screenHeight;


	// Calculate the Camera parameters
	VectorClass camRight = camLookAt.Normalize().CrossProd(VectorClass(0, 1, 0));
	VectorClass camUp = camRight.CrossProd(camLookAt);
	//VectorClass camUp = VectorClass(0,1,0);
	CameraClass originalCamera = CameraClass(camPosition, camLookAt, camUp, f);


	VectorClass camN = (originalCamera.GetPosition() - originalCamera.GetLookAt()).Normalize();
	VectorClass camU = (camN.CrossProd(originalCamera.GetUpVector())).Normalize();
	VectorClass camV = camU.CrossProd(camN);
	//VectorClass camU = (originalCamera.GetUpVector().CrossProd(camN)).Normalize();
	//VectorClass camV = camN.CrossProd(camU);
	
	// Calculate center pixel of image plane
	VectorClass center( originalCamera.GetPosition().GetX() + f * camN.GetX(),
						originalCamera.GetPosition().GetY() + f * camN.GetY(),
						originalCamera.GetPosition().GetZ() + f * camN.GetZ());

	// The bottom leftmost point of the image plane
	VectorClass startPixel;

	startPixel.SetX(center.GetX() - ((worldWidth * camU.GetX()) + (worldHeight*camV.GetX())) / 2.0);
	startPixel.SetY(center.GetY() - ((worldWidth * camU.GetY()) + (worldHeight*camV.GetY())) / 2.0);
	startPixel.SetZ(originalCamera.GetFocalLength());

	double pixelW = worldWidth / screenWidth;
	double pixelH = worldHeight / screenHeight;

	double pw2 = pixelW / 2;
	double ph2 = pixelH / 2;

	int position = 0, testCounter = 0;
	int noOfSamples = 4;

	//VectorClass U = VectorClass(0,1,0).Normalize();
	//VectorClass N = camLookAt.Normalize();
	//VectorClass V = N.CrossProd(U);
	//double wtcam = { U.GetX(),  }
	//Matrix worldToCamera()

	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			ColourClass tmp = ColourClass(0, 0, 0);
			
			VectorClass val = VectorClass(startPixel.GetX() + camU.GetX() * (j + 0.5) * pixelW + camV.GetX() * (i + 0.5) * pixelH,
				startPixel.GetY() + camU.GetY() * (j + 0.5) * pixelW + camV.GetY() * (i + 0.5) * pixelH,
				startPixel.GetZ() + camU.GetZ() * (j + 0.5) * pixelW + camV.GetZ() * (i + 0.5) * pixelH);

			VectorClass direction = (val - originalCamera.GetPosition()).Normalize();
			RayClass ray(originalCamera.GetPosition(), direction);

			ColourClass debugTmpRemoveLater;
			//ColourClass debugTmpRemoveLater = TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);
			/*if (i == 157 && j == 570)
			{
				debugTmpRemoveLater = TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);
				std::cout << debugTmpRemoveLater.GetRed() << "/" << debugTmpRemoveLater.GetGreen() << "/" << debugTmpRemoveLater.GetBlue() << " ";
			}
			else
			{
				debugTmpRemoveLater = TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);
			}*/

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
			
			VectorClass val1 = VectorClass(val.GetX() - pw2, val.GetY() + ph2, val.GetZ());
			VectorClass val2 = VectorClass(val.GetX() + pw2, val.GetY() + ph2, val.GetZ());
			VectorClass val3 = VectorClass(val.GetX() + pw2, val.GetY() - ph2, val.GetZ());
			VectorClass val4 = VectorClass(val.GetX() - pw2, val.GetY() - ph2, val.GetZ());

			VectorClass direction1 = (val1 - originalCamera.GetPosition()).Normalize();
			VectorClass direction2 = (val2 - originalCamera.GetPosition()).Normalize();
			VectorClass direction3 = (val3 - originalCamera.GetPosition()).Normalize();
			VectorClass direction4 = (val4 - originalCamera.GetPosition()).Normalize();

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
		std::cout << " eol " << std::endl;
	}
	savebmp("scene_Vishwanath.bmp", screenWidth, screenHeight, 72, pixels, whichTR);

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
		VectorClass N = (isect.tri->GetNormal(pi)).Normalize();

		VectorClass V = (ray.GetRayOrigin() - pi).Normalize();
		double shade = 1.0;
		int lightsSize = (int)lights.size();
		for (int g = 0; g < lightsSize; g++)
		{
			double shadowOmega = 0.0;
			VectorClass shadowRayDirection = (*lights[g] - pi).Normalize();

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
				shadowObjkt = shadowIsect.tri->illum->Getkt();
				if (shadowObjkt > 0.0)
					shade += 1 - shadowObjkt;
				else
					shade += 1;
				break;
			}
			
			VectorClass L = ((*lights[g]) - pi).Normalize();

			tmp = tmp + isect.tri->illum->GetIllumination(pi, ray, N, L, V, isect.tri->GetColour(), pointCol, maxDepth) / shade;

			//}
		}

		if (depth < maxDepth)
		{
			double reflectKr = isect.tri->illum->Getkr();
			double transmiKt = isect.tri->illum->Getkt();

			if (reflectKr > 0.0)
			{
				VectorClass refRayDirection = isect.tri->illum->Reflect(ray.GetRayDirection(), N);

				RayClass refRay = RayClass(pi, refRayDirection);

				tmp = tmp + TraceRayKD(refRay, depth + 1, incomingni, kdtree, lights, background, pointCol, maxDepth) * reflectKr;
			}

			if (transmiKt > 0.0)
			{
				VectorClass I = ray.GetRayDirection().Normalize()*(-1);
				//VectorClass I = pi - VectorClass(2.5, 4, 0);
				double outgoingnt = isect.tri->illum->Getn();

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
					double dotNI = N.DotProd(I);
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
		VectorClass N = (objects[closest]->GetNormal(pi)).Normalize();

		VectorClass V = (ray.GetRayOrigin() - pi).Normalize();
		double shade = 1.0;
		int lightsSize = (int)lights.size();
		for (int g = 0; g < lightsSize; g++)
		{
			double shadowOmega = 0.0;
			VectorClass shadowRayDirection = (*lights[g] - pi).Normalize();

			RayClass shadowRay(pi, shadowRayDirection);

			noShadow = true;
			for (int shadowObj = 0; shadowObj < objectsSize; shadowObj++)
			{
				shadowOmega = objects[shadowObj]->GetIntersection(shadowRay);
				double objkt = illuminations[shadowObj]->Getkt();
				//std::cout << shadowOmega << " ";
				if (shadowOmega > 0.00001)
					//if (false)					// Use this to disable shadows. Comment the "if" condition above.
				{
					//if (shadowOmega <= shadowRayDirection.Magnitude())
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
			VectorClass L = ((*lights[g]) - pi).Normalize();

			tmp = tmp + illuminations[closest]->GetIllumination(pi, ray, N, L, V, (*objects[closest]).GetColour(), pointCol, maxDepth) / shade;

			//}
		}

		if (depth < maxDepth)
		{
			double reflectKr = illuminations[closest]->Getkr();
			double transmiKt = illuminations[closest]->Getkt();

			if (reflectKr > 0.0)
			{
				VectorClass refRayDirection = illuminations[closest]->Reflect(ray.GetRayDirection(), N);

				RayClass refRay = RayClass(pi, refRayDirection);

				tmp = tmp + TraceRay(refRay, depth + 1, incomingni, objects, lights, illuminations, background, pointCol, maxDepth) * reflectKr;
			}

			if (transmiKt > 0.0) 
			{
				VectorClass I = ray.GetRayDirection().Normalize()*(-1);
				//VectorClass I = pi - VectorClass(2.5, 4, 0);
				double outgoingnt = illuminations[closest]->Getn();

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
					double dotNI = N.DotProd(I);
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