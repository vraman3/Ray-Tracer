
#include "VectorClass.h"
#include "CameraClass.h"
#include "RayClass.h"
#include "CameraClass.h"
#include "SphereClass.h"
#include "TriangleClass.h"
#include "PlaneClass.h"
#include "SaveToFIle.h"
#include <iostream>
#include <cmatrix>
typedef techsoft::matrix<double> MATRIX;

int main()
{

	int objectCount = 5;
	int lightsCount = 2;
	ObjectClass *objects[] = {	new SphereClass(0.8, VectorClass(-0.448, -1.206, 12.407), ColourClass(1.0, 0.84, 0.0)),
								new SphereClass(0.8, VectorClass(0.212, -1.525, 12.983), ColourClass(1.0, 0.0, 0.0)),
								new PlaneClass(VectorClass(-1.249, -2.600, 9.300), VectorClass(2.743, -2.00, 18.291),
												VectorClass(-1.249, -2.00, 18.291), ColourClass(0.0, 1.0, 0.0)) ,
								new TriangleClass(VectorClass(-1.249, -2.600, 9.300), VectorClass(2.743, -2.00, 18.291), 
												VectorClass(-1.249, -2.00, 18.291),	ColourClass(0.0, 1.0, 0.0)),
								new TriangleClass(VectorClass(-1.249, -2.600, 9.300), VectorClass(2.743, -2.600, 9.300),
												VectorClass(2.743, -2.00, 18.291), ColourClass(0.0, 1.0, 0.0)) };
	
	VectorClass *lights[] = { new VectorClass(0, 0, 0), new VectorClass(3.676, 9.303, 9.157) };

	ColourClass background(0.0, 0.0, 0.0);
	ColourClass pointCol(1.0, 1.0, 1.0);
	
	double worldWidth = 2, worldHeight = 2;
	int screenWidth = 640, screenHeight = 480;

	int filesize = screenWidth * screenHeight;
	ColourClass *pixels = new ColourClass[filesize];

	CameraClass originalCamera = CameraClass(VectorClass(0,0,0), VectorClass(0,0,1), VectorClass(0,1,0), 2.0);

	VectorClass camN = (originalCamera.GetPosition() - originalCamera.GetLookAt()).Normalize();
	VectorClass camU = (camN.CrossProd(originalCamera.GetUpVector())).Normalize();
	VectorClass camV = camU.CrossProd(camN);

	double f = originalCamera.GetFocalLength();

	VectorClass center( originalCamera.GetPosition().GetX() + f * camN.GetX(),
						originalCamera.GetPosition().GetY() + f * camN.GetY(),
						originalCamera.GetPosition().GetZ() + f * camN.GetZ());

	VectorClass startPixel;

	startPixel.SetX(center.GetX() - ((worldWidth * camU.GetX()) + (worldHeight*camV.GetX())) / 2.0);
	startPixel.SetY(center.GetY() - ((worldWidth * camU.GetY()) + (worldHeight*camV.GetY())) / 2.0);
	startPixel.SetZ(originalCamera.GetFocalLength());

	double pixelW = worldWidth / screenWidth;
	double pixelH = worldHeight / screenHeight;

	int position = 0, testCounter = 0;

	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{			
			VectorClass val = VectorClass(  startPixel.GetX() + camU.GetX() * (j + 0.5) * pixelW + camV.GetX() * (i + 0.5) * pixelH,
											startPixel.GetY() + camU.GetY() * (j + 0.5) * pixelW + camV.GetY() * (i + 0.5) * pixelH,
											startPixel.GetZ() + camU.GetZ() * (j + 0.5) * pixelW + camV.GetZ() * (i + 0.5) * pixelH);

			VectorClass direction = (val - originalCamera.GetPosition()).Normalize();

			RayClass ray(originalCamera.GetPosition(), direction);

			double currentLowestVal = 1000000;
			double omega = 0.0;
			int closest = -1;
			ColourClass tmp = ColourClass(0, 0, 0);

			int omegaCounter = 0;
			for (int objNo = 0; objNo < objectCount ; objNo++)
			{
				omega = objects[objNo]->GetIntersection(ray);
				if (omega == -1)
				{
					continue;
				}
				else
				{
					if (omega < currentLowestVal)
					{
						closest = objNo;
						currentLowestVal = omega;
					}
				}
			}
			if (closest == -1)
			{
					pixels[position].SetRed(background.GetRed());
					pixels[position].SetGreen(background.GetGreen());
					pixels[position].SetBlue(background.GetBlue());
			}
			else
			{
				bool shadow = false;
				VectorClass pi = ray.GetRayOrigin() + ray.GetRayDirection() * currentLowestVal;

				for (int g = 0; g < lightsCount; g++)
				{					
					//VectorClass temp = (lights[lightsCount]);
					double shadowOmega = 0.0;
					VectorClass shadowRayDirection = (*lights[g] - pi).Normalize();

					RayClass shadowRay(pi, shadowRayDirection);

					for (int shadowObj = 0; shadowObj < objectCount; shadowObj++)
					{
						if (true)		//Made it to disable shadows
						{
							shadowOmega = objects[shadowObj]->GetIntersection(shadowRay);

							//std::cout << shadowOmega << " ";
							if (shadowOmega > 0.00001)
							{
								if (shadowOmega <= shadowRayDirection.Magnitude())
								{
									shadow = true;
									break;
								}
							}
						}
					}
				}

				if (shadow)
				{ 
					pixels[position].SetRed(0.0);
					pixels[position].SetGreen(0.0);
					pixels[position].SetBlue(0.0);
				}
				else //if(closest != -1)
				{
					//std::cout << " hmmm  ";
					for (int f = 0; f < lightsCount; f++)
					{
						VectorClass L = ((*lights[f]) - pi).Normalize();

						VectorClass N = (objects[closest]->GetNormal(pi)).Normalize();

						double objDiffuse = objects[closest]->GetDiffuse();
						double objSpecular = objects[closest]->GetSpecular();
						double objAmbient = objects[closest]->GetAmbient();

						if (objDiffuse > 0)
						{
							double dotNL = N.DotProd(L);

							if (dotNL > 0)
							{
								double diff = objDiffuse * dotNL;
								ColourClass diffuse = ((*objects[closest]).GetColour() * diff) * pointCol;

								tmp = tmp + diffuse;

								VectorClass R = (N * 2 * dotNL - L).Normalize();
								VectorClass V = (ray.GetRayOrigin() - pi).Normalize();

								double dotVR = V.DotProd(R);

								if (dotVR > 0)
								{
									double spec = objSpecular * pow(dotVR, 10.5);
									ColourClass specular = ((*objects[closest]).GetColour() * spec) * pointCol;
									tmp = tmp + specular;
								}
								ColourClass ambient = (*objects[closest]).GetColour() * objAmbient * pointCol;
								tmp = tmp + ambient;
								
								//if (tmp.GetGreen() > 1.0) std::cout << " red oops" << std::endl;															
							}
						}
					}
					pixels[position].SetRed(tmp.GetRed());
					pixels[position].SetGreen(tmp.GetGreen());
					pixels[position].SetBlue(tmp.GetBlue());
				}
				
			}
			position++;
		}
	}
	savebmp("scene_anti-aliased.bmp", screenWidth, screenHeight, 72, pixels);
	return 0;
}