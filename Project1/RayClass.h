/**
	RayTracing, RayClass.h
	Header file for class RayClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
#pragma once

#include "VectorClass.h"

class RayClass
{
private:
	/* Variables */
	VectorClass origin;
	VectorClass direction;
	VectorClass invDirection;

public:
	/* Variables */
	double minT;
	double maxT;
	
	/* Constructors */
	RayClass();
	RayClass(VectorClass paramOrigin, VectorClass paramDirection);

	/* Getters */
	VectorClass GetRayOrigin();
	VectorClass GetRayDirection();
	VectorClass GetRayInvDirection();

	/* Setters */
	void SetRayOrigin(VectorClass paramOrigin);
	void SetRayDirection(VectorClass paramDirection);
};

