#pragma once

//Author: Vishwanath Raman
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
		VectorClass Bmin, Bmax;
		VectorClass centre;

	public:
		AABBClass();
		AABBClass(VectorClass min, VectorClass max);

		void SetCentre();
		void Expand(AABBClass);
		int GetLongestAxis();
		VectorClass GetNormal(VectorClass);
		double GetIntersection1(RayClass, double *hitt0 = NULL, double *hitt1 = NULL);
		virtual double GetIntersection(RayClass, double *hitt0 = NULL, double *hitt1 = NULL);
};

