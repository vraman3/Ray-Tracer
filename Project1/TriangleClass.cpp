/**
RayTracing, VectorClass.cpp
Class file for direction vector class

@author: Vishwanath Raman
@version: 1.0 Oct/07/2017

*/

#include "TriangleClass.h"

#include <iostream>
#include <math.h>
#include <algorithm>

/**
	Default Constructor.
*/
TriangleClass::TriangleClass()
{
	a = VectorClass(1.0, 1.0, 1.0);
	b = VectorClass(1.0, 1.0, 1.0);
	c = VectorClass(1.0, 1.0, 1.0);
	colour = ColourClass(0.0, 1.0, 1.0);
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
	minValBbox = VectorClass(1.0, 1.0, 1.0);
	maxValBbox = VectorClass(1.0, 1.0, 1.0);
	testcount = 0;
}

/**
	Parameterized Constructor.

	@param vert1: First(a) vertex for triangle.
	@param vert2: Second(b) vertex for triangle.
	@param vert3: Third(c) vertex for triangle.
	@param   col: Colour for current triangle.	
*/
TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col)
{
	a = vert1;
	b = vert2;
	c = vert3;
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;

	normal = (vert3 - vert1).crossProd(vert2 - vert1);

	SetValuesForBoundingBox();
}

/**
	Parameterized Constructor.

	@param		 vert1: First(a) vertex for triangle.
	@param		 vert2: Second(b) vertex for triangle.
	@param		 vert3: Third(c) vertex for triangle.
	@param		   col: Colour for current triangle.
	@param  paramIllum: Illumination model for current triangle.
*/
TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col, IlluminationClass *paramIllum)
{
	a = vert1;
	b = vert2;
	c = vert3;
	
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
	illum = paramIllum;

	normal = (vert3 - vert1).crossProd(vert2 - vert1);

	SetValuesForBoundingBox();
}

/**
	Overloading operator [] for TriangleClass.

	@param  vertexNumber: The vertex to be returned.
	@return the corresponding vertex returned as a VectorClass.
*/
VectorClass TriangleClass::operator[](const int vertexNumber) const
{
	switch (vertexNumber)
	{
	case 0: return a;
		break;

	case 1: return b;
		break;

	case 2: return c;
		break;

	default: return VectorClass(-1, -1, -1);
		break;
	}
}

/**
	Getter for first vertex (a) of current triangle.

	@return the first vertex (a) of the triangle as a VectorClass.
*/
VectorClass TriangleClass::GetA()
{
	return a;
}

/**
	Getter for second vertex (b) of current triangle.

	@return the second vertex (b) of the triangle as a VectorClass.
*/
VectorClass TriangleClass::GetB()
{
	return b;
}

/**
	Getter for three vertex (c) of current triangle.

	@return the three vertex (c) of the triangle as a VectorClass.
*/
VectorClass TriangleClass::GetC()
{
	return c;
}

/**
	Getter for the normal of the current triangle.

	@param paramPoint: a point on the triangle to calculate the normal.
				######  NOT USED CURRENTLY, hence the default parameterized value. ######
	@return the normal of the triangle as a VectorClass.
*/
VectorClass TriangleClass::GetNormal(VectorClass paramPoint=VectorClass(0.0,0.0,0.0))
{
	/*double areaT = GetArea(a, B, C);
	double areaB = GetArea(a, P, C);
	double areaC = GetArea(a, P, B);
	double areaA = areaT - areaB - areaC;

	double c1 = areaA / areaT;
	double c2 = areaB / areaT;
	double c3 = areaC / areaT;

	VectorClass NA = (C - a).crossProd(B - a);
	VectorClass NB = (a - B).crossProd(C - B);
	VectorClass NC = (B - C).crossProd(a - C);

	double nx = NA.getX() * c1 + NB.getX() * c2 + NC.getX() * c3;
	double ny = NA.getY() * c1 + NB.getY() * c2 + NC.getY() * c3;
	double nz = NA.getZ() * c1 + NB.getZ() * c2 + NC.getZ() * c3;

	return VectorClass(nx, ny, nz);*/
	return normal;
}

/**
	Get the minimum value, along each dimension/axis, for all three vertices of 
	the current triangle (for Bounding Box).

	@return the minimum value as a VectorClass.
*/
VectorClass TriangleClass::GetMinValBBox()
{
	return minValBbox;
}

/**
	Get the maximum value, along each dimension/axis, for all three vertices of 
	the current triangle (for Bounding Box).

	@return the maximum value as a VectorClass.
*/
VectorClass TriangleClass::GetMaxValBBox()
{
	return maxValBbox;
}

/**
	Get the diffuse value for the current triangle.

	@return the diffuse value for current triangle as a double.
*/
double TriangleClass::GetDiffuse()
{
	return diffuse;
}

/**
	Get the specular value for the current triangle.

	@return the specular value for current triangle as a double.
*/
double TriangleClass::GetSpecular()
{
	return specular;
}

/**
	Get the ambient value for the current triangle.

	@return the ambient value for current triangle as a double.
*/
double TriangleClass::GetAmbient()
{
	return ambient;
}

/**
	Set the minimum value, along each dimension/axis, for all three vertices of 
	the current triangle (for Bounding Box).

	@param newMinVal: The minimum value to be set, as a VectorClass.
*/
void TriangleClass::SetMinValBBox(VectorClass newMinVal)
{
	minValBbox = newMinVal;
}

/**
	Set the maximum value, along each dimension/axis, for all three vertices of 
	the current triangle (for Bounding Box).

	@param newMaxVal: The maximum value to be set, as a VectorClass.
*/
void TriangleClass::SetMaxValBBox(VectorClass newMaxVal)
{
	maxValBbox = newMaxVal;
}

/**
	Set the minimum and maximum value, along each dimension/axis, for all three vertices of 
	the current triangle (for Bounding Box).

	@param newMinVal: The minimum value to be set, as a VectorClass.
*/
void TriangleClass::SetValuesForBoundingBox()
{
	VectorClass minVal, maxVal;

	double ax = a.getX();
	double ay = a.getY();
	double az = a.getZ();

	double bx = b.getX();
	double by = b.getY();
	double bz = b.getZ();

	double cx = c.getX();
	double cy = c.getY();
	double cz = c.getZ();

	minVal.setX(std::min({ ax, bx, cx }));
	minVal.setY(std::min({ ay, by, cy }));
	minVal.setZ(std::min({ az, bz, cz }));

	maxVal.setX(std::max({ ax, bx, cx }));
	maxVal.setY(std::max({ ay, by, cy }));
	maxVal.setZ(std::max({ az, bz, cz }));

	this->SetMinValBBox(minVal);
	this->SetMaxValBBox(maxVal);
}

/**
	Get the colour of the current triangle.

	@return the colour of the current triangle as a VectorClass.
*/
ColourClass TriangleClass::GetColour()
{ 
	return colour;
}

/**
	Calculate the intersection of the current triangle with a ray.

	@param	ray: The ray (RayClass) to be intersected with.
	@return the intersection as a double.
*/
double TriangleClass::GetIntersection(RayClass ray)
{
	VectorClass e1 = b - a;
	VectorClass e2 = c - a;
	double det, inv_det, u, v;
	VectorClass P = ray.GetRayDirection().crossProd(e2);
	det = e1.dotProd(P);

	if (det < EPSILONVAL && det > -EPSILONVAL) return -1;
	inv_det = 1.0 / det;

	VectorClass T = (ray.GetRayOrigin() - a);

	u = T.dotProd(P) * inv_det;

	if (u < 0.0 || u > 1.0) return -1;

	VectorClass Q = T.crossProd(e1);

	v = ray.GetRayDirection().dotProd(Q) * inv_det;

	if (v < 0.0 || u + v > 1.0)  return -1;

	double t = e2.dotProd(Q) * inv_det;
	//std::cout << t << " t" << std::endl;
	if (t > EPSILONVAL)
	{
		return t;
	}
	return -1;
}

/**
	Get the midpoint of the current triangle.

	@return the midpoint of the current triangle as a VectorClass.
*/
VectorClass TriangleClass::GetMidpoint()
{
	double x = (a.getX() + b.getX() + c.getX()) / 3;
	double y = (a.getY() + b.getY() + c.getY()) / 3;
	double z = (a.getZ() + b.getZ() + c.getZ()) / 3;

	return VectorClass(x, y, z);
}

/**
	Get the area of the current triangle.

	NOT NEEDED CURRENTLY
*/
//double TriangleClass::GetArea(VectorClass aIn, VectorClass bIn, VectorClass cIn)
//{
//	double aVar = aIn.getX() - bIn.getX() * aIn.getX() - bIn.getX() + aIn.getY() - bIn.getY() * aIn.getY() - bIn.getY() + aIn.getZ() - bIn.getZ() * aIn.getZ() - bIn.getZ();
//	double bVar = aIn.getX() - cIn.getX() * aIn.getX() - cIn.getX() + aIn.getY() - cIn.getY() * aIn.getY() - bIn.getY() + aIn.getZ() - bIn.getZ() * aIn.getZ() - bIn.getZ();
//	double cVar = bIn.getX() - cIn.getX() * bIn.getX() - cIn.getX() + bIn.getY() - cIn.getY() * bIn.getY() - cIn.getY() + bIn.getZ() - cIn.getZ() * bIn.getZ() - cIn.getZ();
//
//
//	double s = (sqrt(abs(aVar)) + sqrt(abs(bVar)) + sqrt(abs(cVar))) / 2;
//
//	double area = sqrt(s * (s - aVar) * (s - bVar) * (s - cVar));
//
//	return area;
//}






