#pragma once

//Author: Vishwanath Raman
#include <iostream>
#include <math.h>
#include <algorithm>

#include "VectorClass.h"
#include "RayClass.h"
#include "ColourClass.h"
#include "AABBClass.h"
#include "IlluminationClass.h"

class TriangleClass : public ObjectClass
{
	// VERTICES TAKEN COUNTER CLOCKWISE
	
	private:
		VectorClass A, B, C, N, N1, N2, N3, normal;
		double		D, D1, D2, D3;
		double		diffuse, specular, ambient;
		ColourClass colour;
		VectorClass minValBbox, maxValBbox;
		double GetArea(VectorClass, VectorClass, VectorClass);
		int testcount;

	public:
		TriangleClass();
		TriangleClass(VectorClass, VectorClass, VectorClass, ColourClass);
		TriangleClass(VectorClass, VectorClass, VectorClass, ColourClass, IlluminationClass*);
		IlluminationClass *illum;
		VectorClass GetNormal(VectorClass);
		
		VectorClass operator[](const int) const;
		VectorClass GetA();
		VectorClass GetB();
		VectorClass GetC();

		VectorClass GetMinValBBox();
		VectorClass GetMaxValBBox();

		void SetMinValBBox(VectorClass);
		void SetMaxValBBox(VectorClass);

		void SetValuesForBoundingBox();

		double GetDiffuse();
		double GetSpecular();
		double GetAmbient();

		virtual ColourClass GetColour();
		virtual double GetIntersection(RayClass);
		virtual VectorClass GetMidpoint();
		
};
