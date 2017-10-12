/**
	RayTracing, AABBClass.cpp
	Class to implement an Axis Aligned Bounding Box.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#include "AABBClass.h"

/**
	Default constructor.
*/
AABBClass::AABBClass()
{
}

/**
	Parameterized Constructor.

	@param paramMin: The minimum value for the bounding box.
	@param paramMax: The maximum value for the bounding box.
*/
AABBClass::AABBClass(VectorClass paramMin, VectorClass paramMax)
{
	bMin = paramMin;
	bMax = paramMax;

	calculateCenter();
}

/**
	Get the normal to the current bounding box.
	Default value: VectorClass(0,0,0)

	@return the normal as a VectorClass.
*/
VectorClass AABBClass::GetNormal(VectorClass paramNormal = VectorClass(0, 0, 0))
{ 
	return paramNormal;
}

/**
	Get the longest axis for the current bounding box.

	@return the longest axis as an integer: 0, 1, 2 for x, y, z respectively.
*/
int AABBClass::GetLongestAxis()
{
	double x = bMax.getX() - bMin.getX();
	double y = bMax.getY() - bMin.getY();
	double z = bMax.getZ() - bMin.getZ();

	if (x > y)				// X > Y
	{
		if (x > z)			// X > Z so return X (0)
			return 0;
		else
			return 2;		// Z > X > Y so return Z (2)
	}
	else					// Y > X
	{
		if (y > z)			// Y > Z so return Y (1)
			return 1;
		else
			return 2;		// Z > Y > X so return Z (2)
	}
}

/**
	Method 2: Get the intersection between the current bounding box and a ray.

	@param paramRay: The ray that the bounding box is intersecting with.
	@param hitt0: INCOMPLETE
	@param hitt1: INCOMPLETE
	@return the intersection distance as a double.
*/
double AABBClass::GetIntersection1(RayClass paramRay, double *hitt0, double *hitt1)
{

	double tmin, tmax, tymin, tymax, tzmin, tzmax;

	// X component
	if (paramRay.GetRayDirection().getX() >= 0)
	{
		tmin = (bMin.getX() - paramRay.GetRayOrigin().getX()) * paramRay.GetRayInvDirection().getX();
		tmax = (bMax.getX() - paramRay.GetRayOrigin().getX()) * paramRay.GetRayInvDirection().getX();
	}
	else
	{
		tmin = (bMax.getX() - paramRay.GetRayOrigin().getX()) * paramRay.GetRayInvDirection().getX();
		tmax = (bMin.getX() - paramRay.GetRayOrigin().getX()) * paramRay.GetRayInvDirection().getX();
	}

	// Y component
	if (paramRay.GetRayDirection().getY() >= 0)
	{
		tymin = (bMin.getY() - paramRay.GetRayOrigin().getY()) * paramRay.GetRayInvDirection().getY();
		tymax = (bMax.getY() - paramRay.GetRayOrigin().getY()) * paramRay.GetRayInvDirection().getY();
	}
	else
	{
		tymin = (bMax.getY() - paramRay.GetRayOrigin().getY()) * paramRay.GetRayInvDirection().getY();
		tymax = (bMin.getY() - paramRay.GetRayOrigin().getY()) * paramRay.GetRayInvDirection().getY();
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		if ((tymin > tmax))
		{
			std::cout << "test ";
		}
		return -1;
	}

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	// Z component
	if (paramRay.GetRayDirection().getZ() >= 0)
	{
		tzmin = (bMin.getZ() - paramRay.GetRayOrigin().getZ()) * paramRay.GetRayInvDirection().getZ();
		tzmax = (bMax.getZ() - paramRay.GetRayOrigin().getZ()) * paramRay.GetRayInvDirection().getZ();
	}
	else
	{
		tzmin = (bMax.getZ() - paramRay.GetRayOrigin().getZ()) * paramRay.GetRayInvDirection().getZ();
		tzmax = (bMin.getZ() - paramRay.GetRayOrigin().getZ()) * paramRay.GetRayInvDirection().getZ();
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		std::cout << "bbox returning -1 later";
		return -1;
	}

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;


	if (hitt0) *hitt0 = tmin;
	if (hitt1) *hitt1 = tmax;

	std::cout << "bbox tmin" << tmin;
	return tmin;
}

/**
	Method 1: Get the intersection between the current bounding box and a ray.

	@param paramRay: The ray that the bounding box is intersecting with.
	@param hitt0: INCOMPLETE
	@param hitt1: INCOMPLETE
	@return the intersection distance as a double.
*/
double AABBClass::GetIntersection(RayClass ray, double *hitt0, double *hitt1)
{
	double t0 = ray.minT, t1 = ray.maxT;

	for (int i = 0; i < 3; i++)
	{
		double tNear = (bMin[i] - ray.GetRayOrigin()[i]) * ray.GetRayInvDirection()[i];
		double tFar = (bMax[i] - ray.GetRayOrigin()[i]) * ray.GetRayInvDirection()[i];

		if (tNear > tFar)
		{
			double temp = tNear;
			tNear = tFar;
			tFar = temp;
		}

		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar  < t1 ? tFar : t1;
		if (t0 > t1)
		{
			return -1;
		}
	}
	if (hitt0) *hitt0 = t0;
	if (hitt1) *hitt1 = t1;
	//std::cout << " bbox ";
	return t0;
}

/**
	Calculate the center of the bounding box.
*/
void AABBClass::calculateCenter()
{
	centre.setX((abs(bMin.getX()) + abs(bMax.getX())) / 2);
	centre.setY((abs(bMin.getY()) + abs(bMax.getY())) / 2);
	centre.setZ((abs(bMin.getZ()) + abs(bMax.getZ())) / 2);
}

/**
	Expand the current bounding box with a new box, if any 
	of its dimensions are bigger than the current bounding box.

	@param paramNewBox: The bounding box the current bounding box has to be
						compared with.
*/
void AABBClass::Expand(AABBClass paramNewBox)
{
	if (paramNewBox.bMin.getX() < bMin.getX())
		bMin.setX(paramNewBox.bMin.getX());
	if (paramNewBox.bMin.getY() < bMin.getY())
		bMin.setY(paramNewBox.bMin.getY());
	if (paramNewBox.bMin.getZ() < bMin.getZ())
		bMin.setZ(paramNewBox.bMin.getZ());

	if (paramNewBox.bMax.getX() < bMax.getX())
		bMax.setX(paramNewBox.bMax.getX());
	if (paramNewBox.bMax.getY() < bMax.getY())
		bMax.setY(paramNewBox.bMax.getY());
	if (paramNewBox.bMax.getZ() < bMax.getZ())
		bMax.setZ(paramNewBox.bMax.getZ());
}