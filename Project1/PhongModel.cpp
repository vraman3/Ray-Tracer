#include "PhongModel.h"

PhongModel::PhongModel(double tkd, double tks, double tka, double tke, double inkr, double inkt, double inn) : IlluminationClass(inkr, inkt, inn)
{
	ka = tka;
	kd = tkd;
	ks = tks;
	ke = tke;
}


ColourClass PhongModel::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{
	ColourClass tmp = ColourClass(0.0, 0.0, 0.0);

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
			if (dotNL > 0.0001)
			{
				double diff = kd * dotNL;
				ColourClass diffuse = objColour * diff * pointCol;

				tmp = tmp + diffuse;

				//VectorClass V = (ray.GetRayOrigin() - pi).Normalize();

				VectorClass R = (N * 2 * dotNL - L).Normalize();				//1//	For Phong
				double dotVR = R.DotProd(V);									//2//


				if (dotVR > 0.0001)
				{
					double spec = ks * pow(dotVR, ke);
					ColourClass specular = (ColourClass(1.0, 1.0, 1.0) * spec) * pointCol;
					tmp = tmp + specular;
				}


			}
		}
		ColourClass ambient = objColour * pointCol * ka;
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