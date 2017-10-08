#pragma once

//Author: Vishwanath Raman
#include <iostream>
#include <math.h>
#include "VectorClass.h"
#include "RayClass.h"
#include "ColourClass.h"
#include "ObjectClass.h"


class SphereClass:public ObjectClass
{
private:
	double radius, diffuse, specular, ambient;
	VectorClass center;
	ColourClass colour;

public:
	SphereClass();
	SphereClass(double, VectorClass, ColourClass);
	VectorClass GetNormal(VectorClass);
	VectorClass GetCenter();
	double GetDiffuse();
	double GetSpecular();
	double GetAmbient();
	virtual ColourClass GetColour();
	virtual double GetIntersection(RayClass);
};

