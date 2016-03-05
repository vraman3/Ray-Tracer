#pragma once

//Author: Vishwanath Raman
#include <iostream>

#include "ColourClass.h"
#include "RayClass.h"

#define EPSILONVAL 0.00001

class ObjectClass
{
	public:
	ObjectClass(){}

	virtual double GetAmbient()
	{
		return 0.0;
	}
	virtual double GetSpecular()
	{
		return 0.0;
	}
	virtual double GetDiffuse()
	{
		return 0.0;
	}

	virtual VectorClass GetNormal(VectorClass pi)
	{
		return VectorClass(0, 0, 0);
	}
	virtual ColourClass GetColour()
	{
		return ColourClass(0, 0, 0);
	}
	virtual double GetIntersection(RayClass ray)
	{
		return 0.0;
	}

	virtual VectorClass GetMidpoint()
	{
		return VectorClass();
	}
};