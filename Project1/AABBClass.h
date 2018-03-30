/**
	RayTracing, AABBClass.h
	Header file for the AABBClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#pragma once

#include <iostream>

#include "ObjectClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"
#include "TriangleClass.h"
#include <cmath>

class AABBClass :public ObjectClass
{
	private:
		// The centre, minimum and maximum values for the bounding box
		VectorClass bMin, bMax, centre;

	public:
		/* Constructors */
		AABBClass();
		AABBClass(VectorClass point);
		AABBClass(VectorClass min, VectorClass max);

		/* Getters */
		VectorClass getbMin();
		VectorClass getbMax();
		int GetLongestAxis();
		VectorClass GetNormal(VectorClass);
		double GetIntersection1(RayClass, double *hitt0 = NULL, double *hitt1 = NULL);
		virtual double GetIntersection(RayClass, double *hitt0 = NULL, double *hitt1 = NULL);

		/* Methods */
		void calculateCenter();
		void Expand(AABBClass);
		AABBClass Expand(VectorClass& point);
};

