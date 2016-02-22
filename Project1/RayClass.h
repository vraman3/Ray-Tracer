#pragma once

//Author: Vishwanath Raman
#include "VectorClass.h"

class RayClass
{
private:
	VectorClass origin;
	VectorClass direction;
	VectorClass invDirection;

public:
	RayClass();
	RayClass(VectorClass, VectorClass);

	VectorClass GetRayOrigin();
	VectorClass GetRayDirection();
};

RayClass::RayClass()
{
	origin		= VectorClass(0, 0, 0);
	direction	= VectorClass(1, 0, 0);
	invDirection = 1 / direction;
}

RayClass::RayClass(VectorClass o, VectorClass d)
{
	origin		= o;
	direction	= d;
	invDirection = 1 / direction;
}

VectorClass RayClass::GetRayOrigin()
{
	return origin;
}

VectorClass RayClass::GetRayDirection()
{
	return direction;
}