/**
	RayTracing, Tracing.cpp
	Class to run the functions to actually trace the ray on every object.

	@author: Vishwanath Raman
	@version: 1.0 Oct/23/2017

*/

#include "Tracing.h"

// Temp include
#include "SphereClass.h"
//

/**
	Default constructor.
*/
Tracing::Tracing()
{}

/**
	Trace a ray across all objects store in a k-d tree.

	@param ray: The ray to be traced.
	@param depth: The current depth of the tracing. For multiple light bounces.
	@param incomingni: The refractive index of the medium outside the objects.
	@param kdtree: The k-d tree that has all the objects for the scene.
	@param lights: All the light sources for the current scene.
	@param background: The background colour.
	@param pointCol: The intensity of the light.
	@param maxDepth: The maximum allowed depth for all light bounces.
*/
ColourClass Tracing::TraceRayKD(RayClass ray, int depth, double incomingni, KDNode kdtree, std::vector<VectorClass*> lights, 
	ColourClass background, ColourClass pointCol, int maxDepth)
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

/**
	Trace a ray across all objects store in a k-d tree.

	@param ray: The ray to be traced.
	@param depth: The current depth of the tracing. For multiple light bounces.
	@param incomingni: The refractive index of the medium outside the objects.
	@param objects: A vector array of all the Objects in the current scene.
	@param lights: All the light sources for the current scene.
	@param illuminations: The illumination model for all the objects. Ordered synced with 
						  the order of the Objects in 'objects'
	@param background: The background colour.
	@param pointCol: The intensity of the light.
	@param maxDepth: The maximum allowed depth for all light bounces.
*/
ColourClass Tracing::TraceRay(RayClass ray, int depth, double incomingni, std::vector<TriangleClass*> objects, std::vector<VectorClass*> lights,
	ColourClass background, ColourClass pointCol, int maxDepth)
{
	double currentLowestVal = 1000000;
	double omega = 0.0;
	int closest = -1;
	ColourClass tmp = ColourClass(0, 0, 0);

	int omegaCounter = 0;
	int objectsSize = objects.size();
	//std::cout << "objsize" << objectsSize << std::endl;
	for (int objNo = 0; objNo < objectsSize ; objNo++)
	{
		omega = objects[objNo]->GetIntersection(ray);
		
		if (omega == -1)
		{
			continue;
		}
		else
		{
			//std::cout << omega << " this " << std::endl;
			//std::getchar();
			if (omega < currentLowestVal)
			{
				closest = objNo;
				currentLowestVal = omega;
			}
			//std::cout << omega << " om " << closest << std::endl;
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
				double objkt = objects[shadowObj]->illum->getTransmissivitykt();

				//$// double objkt = illuminations[shadowObj]->getTransmissivitykt();

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
			
			tmp = tmp + objects[closest]->illum->getIllumination(pi, ray, N, L, V, (*objects[closest]).GetColour(), pointCol, maxDepth) / shade;

			//}
		}

		if (depth < maxDepth)
		{
			double reflectKr = objects[closest]->illum->getReflectivitykr();
			double transmiKt = objects[closest]->illum->getTransmissivitykt();

			if (reflectKr > 0.0)
			{
				VectorClass refRayDirection = objects[closest]->illum->Reflect(ray.GetRayDirection(), N);

				RayClass refRay = RayClass(pi, refRayDirection);

				tmp = tmp + TraceRay(refRay, depth + 1, incomingni, objects, lights, background, pointCol, maxDepth) * reflectKr;
			}

			if (transmiKt > 0.0) 
			{
				VectorClass I = ray.GetRayDirection().normalize()*(-1);
				//VectorClass I = pi - VectorClass(2.5, 4, 0);
				double outgoingnt = objects[closest]->illum->getNormal();

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
						transRayDirection = objects[closest]->illum->Reflect(I*(-1), N);
						niToBePassed = incomingni;
					}
				}

				RayClass transRay = RayClass(pi, transRayDirection);
				tmp = tmp + TraceRay(transRay, depth + 1, niToBePassed, objects, lights, background, pointCol, maxDepth) * transmiKt;
			}
		}
		return tmp;
	}
}

/**
	A debug function for TraceRay. Currently using object arrays

	@param ray: The ray to be traced.
	@param depth: The current depth of the tracing. For multiple light bounces.
	@param incomingni: The refractive index of the medium outside the objects.
	@param objects: A vector array of all the Objects in the current scene.
	@param lights: All the light sources for the current scene.
	@param background: The background colour.
	@param pointCol: The intensity of the light.
	@param maxDepth: The maximum allowed depth for all light bounces.
*/
ColourClass Tracing::TraceRay_debug(RayClass ray_debug, std::vector<ObjectClass*> objects_debug)
{
	double currentLowestVal = 1000000;
	double t_debug = 0.0;
	int closest = -1;
	ColourClass tmp = ColourClass(0, 0, 0);

	int omegaCounter = 0;
	int objectsSize = objects_debug.size();

	for (int objNo = 0; objNo < objects_debug.size(); objNo++)
	{
		t_debug = objects_debug[objNo]->GetIntersection(ray_debug);

		if (t_debug == -1)	{continue;}
		else
		{
			if (t_debug < currentLowestVal)
			{
				closest = objNo;
				currentLowestVal = t_debug;
			}
		}

	}

	//auto t_debug = (sphere_debug.GetIntersection(ray_debug));

	if (t_debug > EPSILONVAL)
	{
		// Create normal to Sphere at current intersection point of given ray and Sphere
		VectorClass normal_debug = (ray_debug.GetRayOrigin() + (ray_debug.GetRayDirection() * t_debug) - dynamic_cast<SphereClass*>(objects_debug[closest])->GetCenter()).normalize();

		return ColourClass(normal_debug.getX() + 1, normal_debug.getY() + 1, normal_debug.getZ() + 1) * 0.5;

	}
	
	t_debug = 0.5 * (ray_debug.GetRayDirection().normalize().getY() + 1.0);

	//ColourClass pixelColour_debug = ColourClass(1.0, 1.0, 1.0) * (1.0 - t_debug) + ColourClass(0.5, 0.7, 1.0) * t_debug;
	return ColourClass(1.0, 1.0, 1.0) * (1.0 - t_debug) + ColourClass(0.5, 0.7, 1.0) * t_debug;
}