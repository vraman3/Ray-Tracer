#pragma once

//Author: Vishwanath Raman
#include <iostream>

#include "VectorClass.h"
#include "RayClass.h"
#include "ColourClass.h"
#include "ObjectClass.h"

#define EPSILONPLANE 0.00001

class PlaneClass : public ObjectClass
{
	private:
		VectorClass A, B, C, edge1, edge2, normal;
		double		diffuse, specular, ambient;
		int count;
		ColourClass colour;
		double GetArea(VectorClass, VectorClass, VectorClass);

	public:
		PlaneClass();
		PlaneClass(VectorClass, VectorClass, VectorClass, ColourClass);
		VectorClass GetNormal(VectorClass);

		double GetDiffuse();
		double GetSpecular();
		double GetAmbient();

		virtual ColourClass GetColour();
		virtual double GetIntersection(RayClass);
};

