#include "StraussModel.h"

StraussModel::StraussModel(double ts, double tm, double tt, double inkr, double inkt, double inn) : IlluminationClass(inkr, inkt, inn)
{
	s = ts;
	m = tm;
	t = tt;
	kf = 1.12;
	ks = 1.01;
	debugcounter = 0;
}

ColourClass StraussModel::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{
	ColourClass tmp = ColourClass(0, 0, 0);

	VectorClass H = Reflect(L, N);

	double dotNL = N.DotProd(L);
	double dotNV = N.DotProd(V);
	double dotHV = H.DotProd(V);

	double fdotNL = Fresnel(dotNL);

	double s3 = s*s*s;

	double d = (1.0 - m * s);
	double rd = (1.0 - s3) * (1.0 - t);

	ColourClass diffuse = objColour * (dotNL * d * rd);

	double r = (1.0 - t) - rd;

	double j = fdotNL * Shadow(dotNL) * Shadow(dotNV);

	double reflectVar = fmin(1.0, r + j*(r + 0.1));

	ColourClass C1 = ColourClass(1.0, 1.0, 1.0);

	ColourClass Cs = C1 + (objColour - C1) * m * (1.0 - fdotNL);

	ColourClass specular = Cs * reflectVar;


	// HOW TO APPROXIMATE POW OF A NEGATIVE BASE AND NON INTEGER EXPONENET
	// WHICH IS A COMPLEX ANSEWER TO A GOD DAMN REAL NUMBER

	//if (s < 1.0)
	specular = specular * pow(-dotHV, 3.0 / (1.0 - s));
	//else
	//specular = specular * pow(-dotHV, 3.0 / 1.0);


	diffuse = pointCol * diffuse;
	specular = pointCol * specular;
	//if (debugcounter < 500)
	//{
	//std::cout << "in " << specular.GetRed() << " " << specular.GetGreen() << " " << specular.GetBlue() << " " << std::endl;
	//std::cout << "in " << diffuse.GetRed() << " " << diffuse.GetGreen() << " " << diffuse.GetBlue() << " " << std::endl;
	//std::cout << "in " << Cs.GetRed() << " " << Cs.GetGreen() << " " << Cs.GetBlue() << " " << std::endl;
	//std::cout << "in " << powl(-dotHV, 3.0 / (1.0 - s)) << std::endl;
	//debugcounter += 50;
	//}

	//##################################################################################################################################################//
	/////////////////////////////
	// AMBIENT IS WRONG.. AFFECTS WHOLE PIC. DEBUG
	ColourClass ambient = objColour * rd;

	//std::cout << diffuse.GetRed() << " " << diffuse.GetGreen() << " " <<diffuse.GetBlue() << " " << std::endl;

	if (diffuse.GetRed() < 0 || diffuse.GetGreen() < 0 || diffuse.GetBlue() < 0)
		diffuse = ColourClass(0.0, 0.0, 0.0);

	if (specular.GetRed() < 0 || specular.GetGreen() < 0 || specular.GetBlue() < 0)
		specular = ColourClass(0.0, 0.0, 0.0);

	tmp = diffuse;
	/*if (debugcounter < 500)
	{
	std::cout << "in " << tmp.GetRed() << " " << tmp.GetGreen() << " " << tmp.GetBlue() << " " << std::endl;
	debugcounter += 50;
	}*/
	return tmp;
}

double StraussModel::Fresnel(double x)
{
	double a = (1 / (x - kf) * (x - kf)) - (1 / kf*kf);

	//double b1 = 1 / ((1 - kf) * (1 - kf));
	double b = 1 / ((1 - kf) * (1 - kf)) - (1 / kf*kf);

	/*if (debugcounter < 500)
	{
	std::cout << "in " << a/b << std::endl;
	debugcounter += 50;
	}*/
	return a / b;
}

double StraussModel::Shadow(double x)
{

	double a1 = 1 / ((1 - ks) * (1 - ks));
	double a2 = 1 / ((x - ks) * (x - ks));

	double a = a1 - a2;


	double b1 = 1 / ((1 - ks) * (1 - ks));
	double b = b1 - (1 / ks*ks);

	/*if (debugcounter < 500)
	{
	std::cout << "in " << a/b << std::endl;
	debugcounter += 50;
	}*/
	return a / b;
}
