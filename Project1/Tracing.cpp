
#include "Tracing.h"

Tracing::Tracing()
{

}

ColourClass Tracing::TraceRayKD(RayClass ray, int depth, double incomingni, KDNode kdtree, std::vector<VectorClass*> lights,ColourClass background, ColourClass pointCol, int maxDepth)
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


ColourClass Tracing::TraceRay(RayClass ray, int depth, double incomingni, std::vector<ObjectClass*> objects, std::vector<VectorClass*> lights,
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