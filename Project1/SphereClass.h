/**
	RayTracing, SphereClass.h
	Header file for SphereClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/10/2017

*/

#pragma once

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
	/* Constructors */
	SphereClass();
	SphereClass(double, VectorClass, ColourClass);

	/* Getters */
	VectorClass GetNormal(VectorClass);
	VectorClass GetCenter();
	double GetDiffuse();
	double GetSpecular();
	double GetAmbient();
	virtual ColourClass GetColour();
	virtual double GetIntersection(RayClass);

	/* Setters */
	void SetDiffuse(double paramDiffuse);
	void SetSpecular(double paramSpecular);
	void SetAmbient(double paramAmbient);
};

