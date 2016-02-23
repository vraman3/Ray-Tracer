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
	VectorClass GetRayInvDirection();
};

RayClass::RayClass()
{
	origin		= VectorClass(0, 0, 0);
	direction	= VectorClass(1, 0, 0);
	invDirection.SetX( 1 / direction.GetX() );
	invDirection.SetY( 1 / direction.GetY() );
	invDirection.SetZ( 1 / direction.GetZ() );
}

RayClass::RayClass(VectorClass o, VectorClass d)
{
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