#pragma once

//Author: Vishwanath Raman
#include <iostream>

#include "ObjectClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class AABBClass :public ObjectClass
{
	private:
		VectorClass Bmin, Bmax;
		ColourClass colour;
		double diffuse, specular, ambient;

	public:
		AABBClass();
		AABBClass(VectorClass, VectorClass, ColourClass);

		VectorClass GetNormal(VectorClass);
		double GetDiffuse();
		double GetSpecular();
		double GetAmbient();
		virtual ColourClass GetColour();
		virtual double GetIntersection(RayClass);
};

AABBClass::AABBClass()
{
	diffuse = 0.3;
	specular = 0.6;
	ambient = 0.1;
}

AABBClass::AABBClass(VectorClass min, VectorClass max, ColourClass col)
{
	Bmin = min;
	Bmax = max;
	colour = col;

	diffuse = 0.3;
	specular = 0.6;
	ambient = 0.1;
}

double AABBClass::GetAmbient() { return ambient; }

double AABBClass::GetSpecular(){ return specular; }

double AABBClass::GetDiffuse(){ return diffuse; }

VectorClass AABBClass::GetNormal(VectorClass v = VectorClass(0, 0, 0)){ return v; }

ColourClass AABBClass::GetColour(){ return colour; }

double AABBClass::GetIntersection(RayClass ray)
{

	double tmin, tmax, tymin, tymax, tzmin, tzmax;

	// X component
	if (ray.GetRayDirection().GetX() >= 0)
	{
		tmin = (Bmin.GetX() - ray.GetRayOrigin().GetX()) / ray.GetRayDirection().GetX();
		tmax = (Bmax.GetX() - ray.GetRayOrigin().GetX()) / ray.GetRayDirection().GetX();
	}
	else
	{
		tmin = (Bmax.GetX() - ray.GetRayOrigin().GetX()) / ray.GetRayDirection().GetX();
		tmax = (Bmin.GetX() - ray.GetRayOrigin().GetX()) / ray.GetRayDirection().GetX();
	}

	// Y component
	if (ray.GetRayDirection().GetY() >= 0)
	{
		tymin = (Bmin.GetY() - ray.GetRayOrigin().GetY()) / ray.GetRayDirection().GetY();
		tymax = (Bmax.GetY() - ray.GetRayOrigin().GetY()) / ray.GetRayDirection().GetY();
	}
	else
	{
		tymin = (Bmax.GetY() - ray.GetRayOrigin().GetY()) / ray.GetRayDirection().GetY();
		tymax = (Bmin.GetY() - ray.GetRayOrigin().GetY()) / ray.GetRayDirection().GetY();
	}

	if ((tmin > tymax) || (tymin > tmax))
		return -1;

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	// Z component
	if (ray.GetRayDirection().GetY() >= 0)
	{
		tzmin = (Bmin.GetZ() - ray.GetRayOrigin().GetZ()) / ray.GetRayDirection().GetZ();
		tzmax = (Bmax.GetZ() - ray.GetRayOrigin().GetZ()) / ray.GetRayDirection().GetZ();
	}
	else
	{
		tzmin = (Bmax.GetZ() - ray.GetRayOrigin().GetZ()) / ray.GetRayDirection().GetZ();
		tzmax = (Bmin.GetZ() - ray.GetRayOrigin().GetZ()) / ray.GetRayDirection().GetZ();
	}

	if ((tmin > tzmax) || (tzmin > tmax))
		return -1;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return 1;
}