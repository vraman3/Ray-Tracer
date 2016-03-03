#pragma once

//Author: Vishwanath Raman
#include "VectorClass.h"

class RayClass
{
private:
	VectorClass origin;
	VectorClass direction;
	VectorClass invDirection;
	double minT;
	double maxT;

public:
	RayClass();
	RayClass(VectorClass, VectorClass);

	VectorClass GetRayOrigin();
	VectorClass GetRayDirection();
	VectorClass GetRayInvDirection();
};

RayClass::RayClass()
{
	minT = 0.0;
	maxT = DBL_MAX;

	origin		= VectorClass(0, 0, 0);
	direction	= VectorClass(1, 0, 0);
	invDirection.SetX( 1 / direction.GetX() );
	invDirection.SetY( 1 / direction.GetY() );
	invDirection.SetZ( 1 / direction.GetZ() );
}

RayClass::RayClass(VectorClass o, VectorClass d)
{
	minT = 0.0;
	maxT = DBL_MAX;

	origin		= o;
	direction	= d;
	invDirection.SetX(1 / direction.GetX());
	invDirection.SetY(1 / direction.GetY());
	invDirection.SetZ(1 / direction.GetZ());
}

VectorClass RayClass::GetRayOrigin()
{
	return origin;
}

VectorClass RayClass::GetRayDirection()
{
	return direction;
}

VectorClass RayClass::GetRayInvDirection()
{
	return invDirection;
}