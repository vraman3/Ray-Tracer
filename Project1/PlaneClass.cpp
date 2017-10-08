#include "PlaneClass.h"

PlaneClass::PlaneClass()
{
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
}

PlaneClass::PlaneClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col)
{
	A = vert1;
	B = vert2;
	C = vert3;
	edge1 = vert3 - vert1;
	edge2 = vert2 - vert1;

	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;

	normal = (edge2.CrossProd(edge1)).Normalize();
	std::cout << normal.GetX() << " " << normal.GetY() << " " << normal.GetZ() << std::endl;
	colour = col;
	count = 0;
}

VectorClass PlaneClass::GetNormal(VectorClass P)
{
	if (count < 500)
		//std::cout << normal.GetX() << " " << normal.GetY() << " " << normal.GetZ() << std::endl;

		count += 50;
	return normal;

}

double PlaneClass::GetDiffuse()
{
	return diffuse;
}

double PlaneClass::GetSpecular()
{
	return specular;
}

double PlaneClass::GetAmbient()
{
	return ambient;
}

ColourClass PlaneClass::GetColour() { return colour; }

double PlaneClass::GetIntersection(RayClass ray)
{

	//double d = -(normal.DotProd(A));
	//double denom = ray.GetRayDirection().DotProd(normal);
	//double t = 0;
	//if (denom > EPSILONPLANE)
	//{
	//	double num = -normal.DotProd(ray.GetRayOrigin() + normal*d);
	//	//double num = ray.GetRayOrigin().DotProd(normal * d);
	//	double temp = num / denom;
	//	//if (temp > 0)
	//	//{
	//		return temp;
	//	//}
	//}
	//return -1;

	double denom = ray.GetRayDirection().DotProd(normal);
	//std::cout << ray.GetRayDirection().GetX() << " ";
	if (denom > EPSILONPLANE)
	{
		VectorClass vec = A - ray.GetRayOrigin();

		double t = vec.DotProd(normal) / denom;

		if (t >= 0)
		{
			//std::cout << t << " ";
			return t;
		}
	}
	return -1;
}


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
//VectorClass NA = (C - A).CrossProd(B - A);
//VectorClass NB = (A - B).CrossProd(C - B);
//VectorClass NC = (B - C).CrossProd(A - C);
//
//double nx = NA.GetX() * c1 + NB.GetX() * c2 + NC.GetX() * c3;
//double ny = NA.GetY() * c1 + NB.GetY() * c2 + NC.GetY() * c3;
//double nz = NA.GetZ() * c1 + NB.GetZ() * c2 + NC.GetZ() * c3;
//
//return VectorClass(nx,ny,nz);*/
//double PlaneClass::GetArea(VectorClass A, VectorClass B, VectorClass C)
//{
//	double a = A.GetX() - B.GetX() * A.GetX() - B.GetX() + A.GetY() - B.GetY() * A.GetY() - B.GetY() + A.GetZ() - B.GetZ() * A.GetZ() - B.GetZ();
//	double b = A.GetX() - C.GetX() * A.GetX() - C.GetX() + A.GetY() - C.GetY() * A.GetY() - B.GetY() + A.GetZ() - B.GetZ() * A.GetZ() - B.GetZ();
//	double c = B.GetX() - C.GetX() * B.GetX() - C.GetX() + B.GetY() - C.GetY() * B.GetY() - C.GetY() + B.GetZ() - C.GetZ() * B.GetZ() - C.GetZ();
//
//	double s = (sqrt(abs(a)) + sqrt(abs(b)) + sqrt(abs(c))) / 2;
//	double area = sqrt(abs(s * (s - a) * (s - b) * (s - c)));
//
//	return area;
//}
