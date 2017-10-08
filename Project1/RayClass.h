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
	double minT;
	double maxT;
	
	RayClass();
	RayClass(VectorClass, VectorClass);

	VectorClass GetRayOrigin();
	VectorClass GetRayDirection();
	VectorClass GetRayInvDirection();
};

