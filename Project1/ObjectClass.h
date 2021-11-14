/**
	RayTracing, ObjectClass.h
	Header file to implement base ObjectClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
#pragma once

#include <iostream>

#include "ColourClass.h"
#include "RayClass.h"

const double epsilonval_small = 0.00000001;
const double infinity = std::numeric_limits<double>::infinity();

struct intersection_record
{
	VectorClass normal;

	// The intersection value
	double t;

	// The intersection point
	VectorClass point;
};

class ObjectClass
{
public:
	/* Constructors*/
	ObjectClass(){}

	/* Getters */
	virtual double GetAmbient();
	virtual double GetSpecular();
	virtual double GetDiffuse();

	virtual VectorClass GetNormal(VectorClass pi);
	virtual ColourClass GetColour();
	virtual double GetIntersection(RayClass ray);
	virtual double GetIntersection(RayClass ray, double tmin, double tmax, intersection_record intersectionRecord);

	virtual VectorClass GetMidpoint();
};