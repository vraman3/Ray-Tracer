/**
	RayTracing, PlaneClass.h
	Header file to implement PlaneClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
#pragma once

#include <iostream>

#include "VectorClass.h"
#include "RayClass.h"
#include "ColourClass.h"
#include "ObjectClass.h"

#define EPSILONPLANE 0.00001

class PlaneClass : public ObjectClass
{
	private:
		/* Variables */
		VectorClass A, B, C, edge1, edge2, normal;
		double		diffuse, specular, ambient;
		int count;
		ColourClass colour;

		/* Getters */
		double GetArea(VectorClass, VectorClass, VectorClass);

	public:
		/* Constructors */
		PlaneClass();
		PlaneClass(VectorClass, VectorClass, VectorClass, ColourClass);

		/* Getters */
		VectorClass GetNormal(VectorClass);

		double GetDiffuse();
		double GetSpecular();
		double GetAmbient();

		virtual ColourClass GetColour();
		virtual double GetIntersection(RayClass);
};

