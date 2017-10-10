#include "PhongBlinnModel.h"

PhongBlinnModel::PhongBlinnModel(double tkd, double tks, double tka, double tke, double inkr, double inkt) : IlluminationClass(inkr, inkt)
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
	if (ray.GetRayDirection().dotProd(N) < 0)
	{
		if (kd > 0)
		{
			double dotNL = N.dotProd(L);

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

				//VectorClass V = (ray.GetRayOrigin() - pi).normalize();			

				VectorClass temp = (L + V).normalize();							//1//
				VectorClass R = temp / temp.magnitude();						//2//  For Phong-Blinn
				double dotVR = R.dotProd(N);									//3//		

				//VectorClass R = (N * 2 * dotNL - L).normalize();				//1//	For Phong
				//double dotVR = R.dotProd(V);									//2//


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
		double dotNL = N.dotProd(L);

		//if (dotNL > 0.0001)
		//{
		if (ktTransmissivity == 1.0)
		{
			VectorClass R = (N * 2 * dotNL - L).normalize();				//1//	For Phong
			double dotVR = R.dotProd(V);									//2//


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