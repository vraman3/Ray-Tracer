/**
	RayTracing, PlaneClass.cpp
	Implement plane objects.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
#include "PlaneClass.h"

/**
	Default constructor for a plane.
*/
PlaneClass::PlaneClass()
{
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
}

/**
	Parameterized constructor for a plane object, that takes in coordinates
	of three vertices on the plane and the plane colour.

	@param vert1: The first vertex.
	@param vert2: The second vertex.
	@param vert3: The third vertex.
	@param   col: The colour of the plane.
*/
PlaneClass::PlaneClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col)
{
	A = vert1;
	B = vert2;
	C = vert3;

	// Create edges from the three vertices.
	edge1 = vert3 - vert1;
	edge2 = vert2 - vert1;

	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;

	normal = (edge2.crossProd(edge1)).normalize();
	//std::cout << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
	colour = col;
	count = 0;
}

/**
	Return the normal at point P. For a plane normal on any point is
	the same.

	@param paramP: The point at which to get the normal.
	@return the normal of the plane.
*/
VectorClass PlaneClass::GetNormal(VectorClass paramP)
{
	//if (count < 500)
		//std::cout << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
		//count += 50;
	return normal;

}

/**
	Get the diffuse quotient value for current plane object.

	@return the diffuse quotient for current plane object.
*/
double PlaneClass::GetDiffuse()
{
	return diffuse;
}

/**
	Get the specular quotient value for current plane object.

	@return the specular quotient for current plane object.
*/
double PlaneClass::GetSpecular()
{
	return specular;
}

/**
	Get the ambient quotient value for current plane object.

	@return the ambient quotient for current plane object.
*/
double PlaneClass::GetAmbient()
{
	return ambient;
}

/**
	Get the colour of current plane object.

	@return the colour for current plane object.
*/
ColourClass PlaneClass::GetColour() { return colour; }


/**
	Get the intersection of the current plane with a ray.

	@return the distance of the intersection of the current plane and given ray,
	along the ray.
*/
double PlaneClass::GetIntersection(RayClass ray)
{

	//double d = -(normal.dotProd(A));
	//double denom = ray.GetRayDirection().dotProd(normal);
	//double t = 0;
	//if (denom > EPSILONPLANE)
	//{
	//	double num = -normal.dotProd(ray.GetRayOrigin() + normal*d);
	//	//double num = ray.GetRayOrigin().dotProd(normal * d);
	//	double temp = num / denom;
	//	//if (temp > 0)
	//	//{
	//		return temp;
	//	//}
	//}
	//return -1;

	double denom = ray.GetRayDirection().dotProd(normal);
	//std::cout << ray.GetRayDirection().getX() << " ";
	if (denom > EPSILONPLANE)
	{
		VectorClass vec = A - ray.GetRayOrigin();

		double t = vec.dotProd(normal) / denom;

		if (t >= 0)
		{
			//std::cout << t << " ";
			return t;
		}
	}
	return -1;
}

/* Old way to get normal at a particular point. Unnecessary?
//
///*double areaT = GetArea(A, B, C);
//double areaB = GetArea(A, P, C);
//double areaC = GetArea(A, P, B);
//double areaA = areaT - areaB - areaC;
//
//double c1 = areaA / areaT;
//double c2 = areaB / areaT;
//double c3 = areaC / areaT;
//
//VectorClass NA = (C - A).crossProd(B - A);
//VectorClass NB = (A - B).crossProd(C - B);
//VectorClass NC = (B - C).crossProd(A - C);
//
//double nx = NA.getX() * c1 + NB.getX() * c2 + NC.getX() * c3;
//double ny = NA.getY() * c1 + NB.getY() * c2 + NC.getY() * c3;
//double nz = NA.getZ() * c1 + NB.getZ() * c2 + NC.getZ() * c3;
//
//return VectorClass(nx,ny,nz);*/
//double PlaneClass::GetArea(VectorClass A, VectorClass B, VectorClass C)
//{
//	double a = A.getX() - B.getX() * A.getX() - B.getX() + A.getY() - B.getY() * A.getY() - B.getY() + A.getZ() - B.getZ() * A.getZ() - B.getZ();
//	double b = A.getX() - C.getX() * A.getX() - C.getX() + A.getY() - C.getY() * A.getY() - B.getY() + A.getZ() - B.getZ() * A.getZ() - B.getZ();
//	double c = B.getX() - C.getX() * B.getX() - C.getX() + B.getY() - C.getY() * B.getY() - C.getY() + B.getZ() - C.getZ() * B.getZ() - C.getZ();
//
//	double s = (sqrt(abs(a)) + sqrt(abs(b)) + sqrt(abs(c))) / 2;
//	double area = sqrt(abs(s * (s - a) * (s - b) * (s - c)));
//
//	return area;
//}
*/