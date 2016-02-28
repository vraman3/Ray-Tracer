#pragma once

//Author: Vishwanath Raman
#include <iostream>

#include "ObjectClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"
#include <cmath>

class AABBClass :public ObjectClass
{
	private:
		VectorClass Bmin, Bmax;
		VectorClass centre;

	public:
		AABBClass();
		AABBClass(VectorClass, VectorClass);
		AABBClass(TriangleClass);

		void SetCentre();
		VectorClass GetNormal(VectorClass);
		virtual double GetIntersection(RayClass);
};

AABBClass::AABBClass()
{
}

AABBClass::AABBClass(VectorClass min, VectorClass max)
{
	Bmin = min;
	Bmax = max;
}

AABBClass::AABBClass(TriangleClass tri)
{
}

VectorClass AABBClass::GetNormal(VectorClass v = VectorClass(0, 0, 0)){ return v; }

double AABBClass::GetIntersection(RayClass ray)
{

	double tmin, tmax, tymin, tymax, tzmin, tzmax;

	// X component
	if (ray.GetRayDirection().GetX() >= 0)
	{
		tmin = (Bmin.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
		tmax = (Bmax.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
	}
	else
	{
		tmin = (Bmax.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
		tmax = (Bmin.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
	}

	// Y component
	if (ray.GetRayDirection().GetY() >= 0)
	{
		tymin = (Bmin.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
		tymax = (Bmax.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
	}
	else
	{
		tymin = (Bmax.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
		tymax = (Bmin.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
	}

	if ((tmin > tymax) || (tymin > tmax))
		return -1;

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	// Z component
	if (ray.GetRayDirection().GetZ() >= 0)
	{
		tzmin = (Bmin.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
		tzmax = (Bmax.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
	}
	else
	{
		tzmin = (Bmax.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
		tzmax = (Bmin.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
	}

	if ((tmin > tzmax) || (tzmin > tmax))
		return -1;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return tmin;
}

void AABBClass::SetCentre()
{
	centre.SetX((abs(Bmin.GetX()) + abs(Bmax.GetX())) / 2);
	centre.SetY((abs(Bmin.GetY()) + abs(Bmax.GetY())) / 2);
	centre.SetZ((abs(Bmin.GetZ()) + abs(Bmax.GetZ())) / 2);
}