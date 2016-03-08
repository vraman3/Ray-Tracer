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
		double GetArea(VectorClass, VectorClass, VectorClass);
		int testcount;

	public:
		TriangleClass();
		TriangleClass(VectorClass, VectorClass, VectorClass, ColourClass);
		TriangleClass(VectorClass, VectorClass, VectorClass, ColourClass, IlluminationClass*);
		IlluminationClass *illum;
		VectorClass GetNormal(VectorClass);
		
		VectorClass GetA();
		VectorClass GetB();
		VectorClass GetC();
		double GetDiffuse();
		double GetSpecular();
		double GetAmbient();
		virtual ColourClass GetColour();
		virtual double GetIntersection(RayClass);
		virtual VectorClass GetMidpoint();
		AABBClass GetBoundingBox();
};

TriangleClass::TriangleClass()
{
	A = VectorClass(1.0, 1.0, 1.0);
	B = VectorClass(1.0, 1.0, 1.0);
	C = VectorClass(1.0, 1.0, 1.0);
	colour = ColourClass(0.0, 1.0, 1.0);
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;

	testcount = 0;
}

TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col)
{
	A = vert1;
	B = vert2;
	C = vert3;
	normal = (vert3 - vert1).CrossProd(vert2 - vert1);
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
}

TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col, IlluminationClass *inputIllum)
{
	A = vert1;
	B = vert2;
	C = vert3;
	normal = (vert3 - vert1).CrossProd(vert2 - vert1);
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
	illum = inputIllum;
}

VectorClass TriangleClass::GetA()
{
	return A;
}

VectorClass TriangleClass::GetB()
{
	return B;
}

VectorClass TriangleClass::GetC()
{
	return C;
}
VectorClass TriangleClass::GetNormal(VectorClass P)
{
	/*double areaT = GetArea(A, B, C);
	double areaB = GetArea(A, P, C);
	double areaC = GetArea(A, P, B);
	double areaA = areaT - areaB - areaC;

	double c1 = areaA / areaT;
	double c2 = areaB / areaT;
	double c3 = areaC / areaT;

	VectorClass NA = (C - A).CrossProd(B - A);
	VectorClass NB = (A - B).CrossProd(C - B);
	VectorClass NC = (B - C).CrossProd(A - C);

	double nx = NA.GetX() * c1 + NB.GetX() * c2 + NC.GetX() * c3;
	double ny = NA.GetY() * c1 + NB.GetY() * c2 + NC.GetY() * c3;
	double nz = NA.GetZ() * c1 + NB.GetZ() * c2 + NC.GetZ() * c3;
		
	return VectorClass(nx, ny, nz);*/
	return normal;
}

double TriangleClass::GetArea(VectorClass A, VectorClass B, VectorClass C)
{
	double a = A.GetX() - B.GetX() * A.GetX() - B.GetX() + A.GetY() - B.GetY() * A.GetY() - B.GetY() + A.GetZ() - B.GetZ() * A.GetZ() - B.GetZ();
	double b = A.GetX() - C.GetX() * A.GetX() - C.GetX() + A.GetY() - C.GetY() * A.GetY() - B.GetY() + A.GetZ() - B.GetZ() * A.GetZ() - B.GetZ();
	double c = B.GetX() - C.GetX() * B.GetX() - C.GetX() + B.GetY() - C.GetY() * B.GetY() - C.GetY() + B.GetZ() - C.GetZ() * B.GetZ() - C.GetZ();
	
	
	double s = (sqrt(abs(a)) + sqrt(abs(b)) + sqrt(abs(c))) / 2;

	double area = sqrt(s * (s - a) * (s - b) * (s - c));
	
	return area;
}

double TriangleClass::GetDiffuse()
{
	return diffuse;
}

double TriangleClass::GetSpecular()
{
	return specular;
}

double TriangleClass::GetAmbient()
{
	return ambient;
}

ColourClass TriangleClass::GetColour() { return colour; }

double TriangleClass::GetIntersection(RayClass ray)
{
	VectorClass e1 = B - A;
	VectorClass e2 = C - A;
	double det, inv_det, u, v;
	VectorClass P = ray.GetRayDirection().CrossProd(e2);
	det = e1.DotProd(P);

	if (det < EPSILONVAL && det > -EPSILONVAL) return -1;
	inv_det = 1.0 / det;

	VectorClass T = (ray.GetRayOrigin() - A);
	
	u = T.DotProd(P) * inv_det;

	if (u < 0.0 || u > 1.0) return -1;

	VectorClass Q = T.CrossProd(e1);

	v = ray.GetRayDirection().DotProd(Q) * inv_det;

	if (v < 0.0 || u + v > 1.0)  return -1;

	double t = e2.DotProd(Q) * inv_det;
	if (t > EPSILONVAL)
	{
		return t; 
	}
	return -1;
}

VectorClass TriangleClass::GetMidpoint()
{
	double x = (A.GetX() + B.GetX() + C.GetX()) / 3;
	double y = (A.GetY() + B.GetY() + C.GetY()) / 3;
	double z = (A.GetZ() + B.GetZ() + C.GetZ()) / 3;

	return VectorClass(x, y, z);
}

AABBClass TriangleClass::GetBoundingBox()
{
	VectorClass minVal, maxVal;

	double ax = A.GetX();
	double ay = A.GetY();
	double az = A.GetZ();

	double bx = B.GetX();
	double by = B.GetY();
	double bz = B.GetZ();

	double cx = C.GetX();
	double cy = C.GetY();
	double cz = C.GetZ();

	minVal.SetX(std::min({ ax, bx, cx }));
	minVal.SetY(std::min({ ay, by, cy }));
	minVal.SetZ(std::min({ az, bz, cz }));

	maxVal.SetX(std::max({ ax, bx, cx }));
	maxVal.SetY(std::max({ ay, by, cy }));
	maxVal.SetZ(std::max({ az, bz, cz }));

	return AABBClass(minVal, maxVal);
}