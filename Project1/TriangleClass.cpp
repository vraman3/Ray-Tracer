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
	Parameterized Constructor. Requires vertices in counter clockwise order (for a RHS)

	@param vert1: First(a) vertex for triangle.
	@param vert2: Second(b) vertex for triangle.
	@param vert3: Third(c) vertex for triangle.
	@param   col: Colour for current triangle.	
*/
TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col)
{
	// For a RHS vertices should be counter clockwise
	a = vert1;
	b = vert2;
	c = vert3;
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;

	//
	// For a RHS with counter clockwise vertices,
	// normal = (vert2 - vert1) x (vert3 - vert 1)
	//
	normal = (b - a).crossProd(c - a);

	SetValuesForBoundingBox();
}

/**
	Parameterized Constructor. Requires vertices in counter clockwise order (for a RHS)

	@param		 vert1: First(a) vertex for triangle.
	@param		 vert2: Second(b) vertex for triangle.
	@param		 vert3: Third(c) vertex for triangle.
	@param		   col: Colour for current triangle.
	@param  paramIllum: Illumination model for current triangle.
*/
TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col, IlluminationClass *paramIllum)
{
	// For a RHS vertices should be counter clockwise
	a = vert1;
	b = vert2;
	c = vert3;
	
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
	illum = paramIllum;

	//
	// For a RHS with counter clockwise vertices,
	// (vert2 - vert1) x (vert3 - vert 1)
	//
	normal = (b - a).crossProd(c - a);

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
	Only returns intersection point

	@param	ray: The ray (RayClass) to be intersected with.
	@return the intersection as a double.
*/
double TriangleClass::GetIntersection(RayClass ray)
{
	int choice = 0;
	// Compute the plane normal
	VectorClass e1 = b - a;   // v0v1 = v1 - v0;
	VectorClass e2 = c - a;   // v0v2 = v2 - v0;

	if (choice == 0)
	{
		// Do not normalize since we will use length of this normal to calculate
		// the barycentric coordinates using area of the sub triangles
		VectorClass planeNormal = e1.crossProd(e2);
		double denominator = planeNormal.dotProd(planeNormal);

		// Finding P. Where P is a point that could be inside the triangle

		// Check if the plane is parallel to the ray
		double planeNormal_dot_RayDir = planeNormal.dotProd(ray.GetRayDirection());
		if (fabs(planeNormal_dot_RayDir) < EPSILONVAL)
			return -1;

		// Find D from Ax + By + Cz + D = 0
		// A,B,C lie in the plane of the triangle, can subsitute any vertex to
		// find D, where D is distance from the origin
		double planeConstant_D = planeNormal.dotProd(a);


		/*
		*
		*			N (A,B,C) . O + D
		*	t = -  ____________________
		*			N(A,B,C) . R
		*
		*
		*
		*	Since camera is aligned along negative z-axis all primary rays have
		*	negative z-coordinates. So when the normal of a triangle faces the
		*	camera the dot product of the plane Normal and the ray will be negative.
		*	Hence the negative sign of the equation is cancelled out by the negative
		*	sign of the denominator. So practically for calculations we do NOT
		*	negate 't'.
		*
		*/

		// Compute t, the distance from the ray origin to the intersection point
		double t = planeNormal.dotProd(ray.GetRayOrigin()) + planeConstant_D / planeNormal_dot_RayDir;


		// Check if the triangle is behind the ray
		if (t < 0) {
			return -1;
		}

		/*
		*
		* 		P = RayOrigin + t * RayDirection;
		*
		*/
		// Compute the intersection point P 
		VectorClass intersectionPoint_P = ray.GetRayOrigin() + ray.GetRayDirection() * t;

		// Check if intersection point P is inside or outside

		VectorClass insideOutsideTestNormal; //

		// Edge A
		VectorClass edgeA = b - a;
		VectorClass edgePa = intersectionPoint_P - a;
		insideOutsideTestNormal = edgeA.crossProd(edgePa);

		if (planeNormal.dotProd(insideOutsideTestNormal) < 0) {
			return -1;	// intersection point P is on the outside of edge A
		}

		// Edge 1
		VectorClass edgeB = c - b;
		VectorClass edgePb = intersectionPoint_P - b;
		insideOutsideTestNormal = edgeB.crossProd(edgePb);

		double u;

		if ((u = planeNormal.dotProd(insideOutsideTestNormal)) < 0) {
			return -1;	// intersection point P is on the outside of edge B
		}

		// Edge 2
		VectorClass edgeC = a - c;
		VectorClass edgePc = intersectionPoint_P - c;
		insideOutsideTestNormal = edgeC.crossProd(edgePc);

		double v;

		if ((v = planeNormal.dotProd(insideOutsideTestNormal)) < 0) {
			return -1;	// intersection point P is on the outside of edge C
		}

		u /= denominator;
		v /= denominator;

		return t;
	}
	
	if (choice == 1)
	{
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
}

/**
Calculate the intersection of the current triangle with a ray.
Only returns intersection point

@param	ray: The ray (RayClass) to be intersected with.
@return the intersection as a double.
*/
bool TriangleClass::GetIntersectionBarycentric(RayClass ray, double &t, double &u, double &v)
{
	/* Compute the plane normal */
	VectorClass e1 = b - a;   // v0v1 = v1 - v0;
	VectorClass e2 = c - a;   // v0v2 = v2 - v0;

	/* Do not normalize since we will use length of this normal to calculate 
	   the barycentric coordinates using area of the sub triangles 
	*/
	VectorClass planeNormal = e1.crossProd(e2);
	double denominator = planeNormal.dotProd(planeNormal);

	// Finding P. Where P is a point that could be inside the triangle

	// Check if the plane is parallel to the ray
	double planeNormal_dot_RayDir = planeNormal.dotProd(ray.GetRayDirection());
	if (fabs(planeNormal_dot_RayDir) < EPSILONVAL)
		return false;

	// Find D from Ax + By + Cz + D = 0
	// A,B,C lie in the plane of the triangle, can subsitute any vertex to
	// find D, where D is distance from the origin
	double planeConstant_D = planeNormal.dotProd(a);


	/*
	*
	*			N (A,B,C) . O + D
	*	t = -  ____________________
	*			N(A,B,C) . R
	*
	*
	*
	*	Since camera is aligned along negative z-axis all primary rays have
	*	negative z-coordinates. So when the normal of a triangle faces the
	*	camera the dot product of the plane Normal and the ray will be negative.
	*	Hence the negative sign of the equation is cancelled out by the negative
	*	sign of the denominator. So practically for calculations we do NOT
	*	negate 't'.
	*
	*/
	// Compute t, the distance from the ray origin to the intersection point

	t = planeNormal.dotProd(ray.GetRayOrigin()) + planeConstant_D / planeNormal_dot_RayDir;



	// Check if the triangle is behind the ray
	if (t < 0) {
		return false;
	}

	/*
	*
	* 		P = RayOrigin + t * RayDirection;
	*
	*/
	// Compute the intersection point P 
	VectorClass intersectionPoint_P = ray.GetRayOrigin() + ray.GetRayDirection() * t;

	// Check if intersection point P is inside or outside

	VectorClass insideOutsideTestNormal; //

										 // Edge A
	VectorClass edgeA = b - a;
	VectorClass edgePa = intersectionPoint_P - a;
	insideOutsideTestNormal = edgeA.crossProd(edgePa);

	if (planeNormal.dotProd(insideOutsideTestNormal) < 0) {
		return false;	// intersection point P is on the outside of edge A
	}

	// Edge 1
	VectorClass edgeB = c - b;
	VectorClass edgePb = intersectionPoint_P - b;
	insideOutsideTestNormal = edgeB.crossProd(edgePb);

	if ((u = planeNormal.dotProd(insideOutsideTestNormal)) < 0) {
		return false;	// intersection point P is on the outside of edge B
	}

	// Edge 2
	VectorClass edgeC = a - c;
	VectorClass edgePc = intersectionPoint_P - c;
	insideOutsideTestNormal = edgeC.crossProd(edgePc);

	if ((v = planeNormal.dotProd(insideOutsideTestNormal)) < 0) {
		return false;	// intersection point P is on the outside of edge C
	}

	u /= denominator;
	v /= denominator;

	return true;
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






