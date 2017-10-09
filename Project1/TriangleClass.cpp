#include "TriangleClass.h"

#include <iostream>
#include <math.h>
#include <algorithm>

TriangleClass::TriangleClass()
{
	A = VectorClass(1.0, 1.0, 1.0);
	B = VectorClass(1.0, 1.0, 1.0);
	C = VectorClass(1.0, 1.0, 1.0);
	colour = ColourClass(0.0, 1.0, 1.0);
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
	minValBbox = VectorClass(1.0, 1.0, 1.0);
	maxValBbox = VectorClass(1.0, 1.0, 1.0);
	testcount = 0;
}

TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col)
{
	A = vert1;
	B = vert2;
	C = vert3;
	normal = (vert3 - vert1).crossProd(vert2 - vert1);
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
	SetValuesForBoundingBox();
}

TriangleClass::TriangleClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col, IlluminationClass *inputIllum)
{
	A = vert1;
	B = vert2;
	C = vert3;
	normal = (vert3 - vert1).crossProd(vert2 - vert1);
	colour = col;
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
	illum = inputIllum;

	SetValuesForBoundingBox();
}

VectorClass TriangleClass::operator[](const int dimension) const
{
	switch (dimension)
	{
	case 0: return A;
		break;

	case 1: return B;
		break;

	case 2: return C;
		break;

	default: return VectorClass(-1, -1, -1);
		break;
	}
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

	VectorClass NA = (C - A).crossProd(B - A);
	VectorClass NB = (A - B).crossProd(C - B);
	VectorClass NC = (B - C).crossProd(A - C);

	double nx = NA.getX() * c1 + NB.getX() * c2 + NC.getX() * c3;
	double ny = NA.getY() * c1 + NB.getY() * c2 + NC.getY() * c3;
	double nz = NA.getZ() * c1 + NB.getZ() * c2 + NC.getZ() * c3;

	return VectorClass(nx, ny, nz);*/
	return normal;
}

double TriangleClass::GetArea(VectorClass A, VectorClass B, VectorClass C)
{
	double a = A.getX() - B.getX() * A.getX() - B.getX() + A.getY() - B.getY() * A.getY() - B.getY() + A.getZ() - B.getZ() * A.getZ() - B.getZ();
	double b = A.getX() - C.getX() * A.getX() - C.getX() + A.getY() - C.getY() * A.getY() - B.getY() + A.getZ() - B.getZ() * A.getZ() - B.getZ();
	double c = B.getX() - C.getX() * B.getX() - C.getX() + B.getY() - C.getY() * B.getY() - C.getY() + B.getZ() - C.getZ() * B.getZ() - C.getZ();


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
	VectorClass P = ray.GetRayDirection().crossProd(e2);
	det = e1.dotProd(P);

	if (det < EPSILONVAL && det > -EPSILONVAL) return -1;
	inv_det = 1.0 / det;

	VectorClass T = (ray.GetRayOrigin() - A);

	u = T.dotProd(P) * inv_det;

	if (u < 0.0 || u > 1.0) return -1;

	VectorClass Q = T.crossProd(e1);

	v = ray.GetRayDirection().dotProd(Q) * inv_det;

	if (v < 0.0 || u + v > 1.0)  return -1;

	double t = e2.dotProd(Q) * inv_det;
	if (t > EPSILONVAL)
	{
		return t;
	}
	return -1;
}

VectorClass TriangleClass::GetMidpoint()
{
	double x = (A.getX() + B.getX() + C.getX()) / 3;
	double y = (A.getY() + B.getY() + C.getY()) / 3;
	double z = (A.getZ() + B.getZ() + C.getZ()) / 3;

	return VectorClass(x, y, z);
}

VectorClass TriangleClass::GetMinValBBox()
{
	return minValBbox;
}
VectorClass TriangleClass::GetMaxValBBox()
{
	return maxValBbox;
}

void TriangleClass::SetMinValBBox(VectorClass newMinVal)
{
	minValBbox = newMinVal;
}

void TriangleClass::SetMaxValBBox(VectorClass newMaxVal)
{
	maxValBbox = newMaxVal;
}

void TriangleClass::SetValuesForBoundingBox()
{
	VectorClass minVal, maxVal;

	double ax = A.getX();
	double ay = A.getY();
	double az = A.getZ();

	double bx = B.getX();
	double by = B.getY();
	double bz = B.getZ();

	double cx = C.getX();
	double cy = C.getY();
	double cz = C.getZ();

	minVal.setX(std::min({ ax, bx, cx }));
	minVal.setY(std::min({ ay, by, cy }));
	minVal.setZ(std::min({ az, bz, cz }));

	maxVal.setX(std::max({ ax, bx, cx }));
	maxVal.setY(std::max({ ay, by, cy }));
	maxVal.setZ(std::max({ az, bz, cz }));

	this->SetMinValBBox(minVal);
	this->SetMaxValBBox(maxVal);
	//return AABBClass(minVal, maxVal);
}