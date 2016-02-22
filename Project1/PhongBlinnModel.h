#pragma once

//Author: Vishwanath Raman
#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class PhongBlinnModel : public IlluminationClass
{
	private:
		double ka, kd, ks, ke;

	public:
		PhongBlinnModel(double, double, double, double, double, double, double);
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

PhongBlinnModel::PhongBlinnModel(double tkd, double tks, double tka, double tke, double inkr, double inkt, double inn) : IlluminationClass(inkr, inkt, inn)
{
	ka = tka;
	kd = tkd;
	ks = tks;
	ke = tke;
}


ColourClass PhongBlinnModel::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{
	ColourClass tmp = ColourClass(0.0, 0.0, 0.0);
	//double kd = objects[closest]->GetDiffuse();
	//double ks = objects[closest]->GetSpecular();
	//double ka = objects[closest]->GetAmbient();

	/*if (closest == 2 && testCounter < 500)
	{
	std::cout << kd << " dnl" << std::endl;
	testCounter += 50;
	}*/
	if (ray.GetRayDirection().DotProd(N) < 0)
	{
		if (kd > 0)
		{
			double dotNL = N.DotProd(L);

			/*if (closest == 2 && testCounter < 500)
			{
			std::cout << dotNL << " dnl" << std::endl;
			testCounter += 50;
			}*/
			if (dotNL > 0)
			{
				double diff = kd * dotNL;
				ColourClass diffuse = objColour * diff * pointCol;

				tmp = tmp + diffuse;

				//VectorClass V = (ray.GetRayOrigin() - pi).Normalize();			

				VectorClass temp = (L + V).Normalize();							//1//
				VectorClass R = temp / temp.Magnitude();						//2//  For Phong-Blinn
				double dotVR = R.DotProd(N);									//3//		

				//VectorClass R = (N * 2 * dotNL - L).Normalize();				//1//	For Phong
				//double dotVR = R.DotProd(V);									//2//


				if (dotVR > 0)
				{
					double spec = ks * pow(dotVR, ke);
					ColourClass specular = (ColourClass(1.0, 1.0, 1.0) * spec) * pointCol;
					tmp = tmp + specular;
				}
				
			}
		}
		ColourClass ambient = (objColour * ka)* pointCol;
		tmp = tmp + ambient;

		return tmp;
	}
	else
	{
		double dotNL = N.DotProd(L);

		//if (dotNL > 0.0001)
		//{
		if (kt == 1.0)
		{
			VectorClass R = (N * 2 * dotNL - L).Normalize();				//1//	For Phong
			double dotVR = R.DotProd(V);									//2//


			if (dotVR > 0.0001)
			{
				double spec = ks * pow(dotVR, ke);
				ColourClass specular = (ColourClass(1.0, 1.0, 1.0) * spec) * pointCol;
				tmp = tmp + specular;
			}
		}
		return tmp;
	}
}