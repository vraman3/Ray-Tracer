#pragma once

//Author: Vishwanath Raman
#include <iostream>

#include "ObjectClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"
#include "TriangleClass.h"
#include <cmath>

class AABBClass :public ObjectClass
{
	private:
		VectorClass Bmin, Bmax;
		VectorClass centre;

	public:
		AABBClass();
		AABBClass(VectorClass, VectorClass);

		VectorClass GetBmin();
		VectorClass GetBmax();

		void SetBmin(VectorClass);
		void SetBmax(VectorClass);

		void SetCentre();
		void Expand(AABBClass);
		int GetLongestAxis();
		VectorClass GetNormal(VectorClass);
		double GetIntersection1(RayClass, double *hitt0 = NULL, double *hitt1 = NULL);
		virtual double GetIntersection(RayClass, double *hitt0 = NULL, double *hitt1 = NULL);
};

AABBClass::AABBClass()
{
	Bmin = VectorClass(INFINITY, INFINITY, INFINITY);
	Bmax = VectorClass(-INFINITY, -INFINITY, -INFINITY);
}

AABBClass::AABBClass(VectorClass min, VectorClass max)
{
	Bmin = min;
	Bmax = max;

	SetCentre();
}

VectorClass AABBClass::GetNormal(VectorClass v = VectorClass(0, 0, 0)){ return v; }

VectorClass AABBClass::GetBmin()
{
	return this->Bmin;
}

VectorClass AABBClass::GetBmax()
{
	return this->Bmax;
}

void AABBClass::SetBmin(VectorClass val)
{
	this->Bmin = val;
}

void AABBClass::SetBmax(VectorClass val)
{
	this->Bmax = val;
}


int AABBClass::GetLongestAxis()
{
	double x = Bmax.GetX() - Bmin.GetX();
	double y = Bmax.GetY() - Bmin.GetY();
	double z = Bmax.GetZ() - Bmin.GetZ();

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

void AABBClass::Expand(AABBClass newBox)
{
	float newMinX = newBox.Bmin.GetX();
	float newMinY = newBox.Bmin.GetY();
	float newMinZ = newBox.Bmin.GetZ();

	float newMaxX = newBox.Bmax.GetX();
	float newMaxY = newBox.Bmax.GetY();
	float newMaxZ = newBox.Bmax.GetZ();

	// For debugging only. Delete later.
	float oldMinX = this->Bmin.GetX();
	float oldMinY = this->Bmin.GetY();
	float oldMinZ = this->Bmin.GetZ();

	float oldMaxX = this->Bmax.GetX();
	float oldMaxY = this->Bmax.GetY();
	float oldMaxZ = this->Bmax.GetZ();

	// Min
	std::cout << " Min " << std::endl;
	std::cout << newMinX << " : old : " << oldMinX << std::endl;
	if (newMinX < oldMinX)
	{
		std::cout << "setting X min to: " << newMinX << std::endl;
		this->Bmin.SetX(newMinX);
	}

	std::cout << newMinY << " : old : " << oldMinY << std::endl;
	if (newMinY < oldMinY)
	{
		std::cout << "setting Y min to: " << newMinY << std::endl;
		this->Bmin.SetY(newMinY);
	}

	std::cout << newMinZ << " : old : " << oldMinZ << std::endl;
	if (newMinZ < oldMinZ)
	{
		std::cout << "setting Z min to: " << newMinZ << std::endl;
		this->Bmin.SetZ(newMinZ);
	}
	// Max
	std::cout << " Max " << std::endl;
	std::cout << newMaxX << " : old : " << oldMaxX << std::endl;
	if (newMaxX > oldMaxX)
	{
		std::cout << "setting X max to: " << newMaxX << std::endl;
		this->Bmax.SetX(newMaxX);
	}

	std::cout << newMaxY << " : old : " << oldMaxY << std::endl;
	if (newMaxY > oldMaxY)
	{
		std::cout << "setting Y max to: " << newMaxY << std::endl;
		this->Bmax.SetY(newMaxY);
	}

	std::cout << newMaxZ << " : old : " << oldMaxZ << std::endl;
	if (newMaxZ > oldMaxZ)
	{
		std::cout << "setting Z max to: " << newMaxZ << std::endl;
		this->Bmax.SetZ(newMaxZ);
	}
}

double AABBClass::GetIntersection(RayClass ray, double *hitt0, double *hitt1)
{
	double t0 = ray.minT, t1 = ray.maxT;

	for (int i = 0; i < 3; i++)
	{
		double tNear = (Bmin[i] - ray.GetRayOrigin()[i]) * ray.GetRayInvDirection()[i];
		double tFar  = (Bmax[i] - ray.GetRayOrigin()[i]) * ray.GetRayInvDirection()[i];

		if (tNear > tFar)
		{
			double temp = tNear;
			tNear = tFar;
			tFar = temp;
		}

		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar  < t1 ? tFar  : t1;
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

double AABBClass::GetIntersection1(RayClass ray, double *hitt0, double *hitt1)
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

///
/// THIS IS WRONG
///
void AABBClass::SetCentre()
{
	centre.SetX((abs(Bmin.GetX()) + abs(Bmax.GetX())) / 2);
	centre.SetY((abs(Bmin.GetY()) + abs(Bmax.GetY())) / 2);
	centre.SetZ((abs(Bmin.GetZ()) + abs(Bmax.GetZ())) / 2);
}

