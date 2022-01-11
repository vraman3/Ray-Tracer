/**
	RayTracing, TriangleClass.h
	Custom class for storing Triangles

	@author: Vishwanath Raman
	@version: 1.0 Oct/08/2017

*/
#pragma once

#include "VectorClass.h"
#include "RayClass.h"
#include "ColourClass.h"
#include "ObjectClass.h"

class TriangleClass : public ObjectClass
{
	// VERTICES TAKEN COUNTER CLOCKWISE
	
	private:
		VectorClass a, b, c, normal;
		double		diffuse, specular, ambient;
		ColourClass colour;
		VectorClass minValBbox, maxValBbox;
		int id;

		//double GetArea(VectorClass, VectorClass, VectorClass);
		

	public:
		IlluminationClass *illum;

		/* Constructors */
		TriangleClass();
		TriangleClass(VectorClass, VectorClass, VectorClass, ColourClass, int id = -1);
		TriangleClass(VectorClass, VectorClass, VectorClass, ColourClass, IlluminationClass*, int id = -1);
				
		/* Getters */
		int GetId();
		VectorClass GetA();
		VectorClass GetB();
		VectorClass GetC();
		VectorClass GetNormal(VectorClass);
		VectorClass GetMinValBBox();
		VectorClass GetMaxValBBox();
		double GetDiffuse();
		double GetSpecular();
		double GetAmbient();

		/* Setters */
		void SetId(int id);
		void SetMinValBBox(VectorClass);
		void SetMaxValBBox(VectorClass);
		void SetValuesForBoundingBox();

		/* Virtual functions */
		virtual ColourClass GetColour();
		virtual double GetIntersection(RayClass ray);
		virtual double GetIntersection(RayClass ray, double tmin, double tmax, intersection_record &intersectionRecord);
		virtual VectorClass GetMidpoint();

		bool GetIntersectionBarycentric(RayClass ray, double &t, double &u, double &v);
		VectorClass operator[](const int) const;
		
		friend std::ostream& operator<<(std::ostream& os, TriangleClass& triangle);
};
