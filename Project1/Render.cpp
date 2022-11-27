#include "Render.h"
#include "Tracing.h"

void Render::render(int screenHeight, int screenWidth, double pixelW, double pixelH, double f, 
					VectorClass startPixel, VectorClass camU, VectorClass camV, CameraClass originalCamera,
					std::vector<TriangleClass*> objects, std::vector<VectorClass*> lights, ColourClass background, 
					ColourClass pointCol, ColourClass* pixels, int maxDepth)

{
	int position = 0, testCounter = 0;
	int noOfSamples = 4;

	//////////////////////////////////////////////////////////
	bool onceflag = true;

	Tracing traceObject = Tracing();
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			ColourClass tmp = ColourClass(0, 0, 0);

			VectorClass val = VectorClass(startPixel.getX() + camU.getX() * (j + 0.5) * pixelW + camV.getX() * (i + 0.5) * pixelH,
				startPixel.getY() + camU.getY() * (j + 0.5) * pixelW + camV.getY() * (i + 0.5) * pixelH,
				-f);

			VectorClass direction = (val - originalCamera.GetPosition()).normalize();
			RayClass ray(originalCamera.GetPosition(), direction);

			/*
			 0 = Regular ray tracing. Brute Force.
			 1 = Use KD trees.
			 2 = Use any other integer to skip following conditions.
			*/


			bool setSpecificPixel_debug = 0;

			
			ColourClass debugTmpRemoveLater;

			//if (i == 0 && j == 271)
			if (i == 90 && j == 240)
			{
				setSpecificPixel_debug = 0;
			}
			//Working scene. For debugging.
			//debugTmpRemoveLater = traceObject.TraceRay(ray, 0, 1.0, openGLTraceRay, lights, illumOGLTraceRay, background, pointCol, maxDepth);
			debugTmpRemoveLater = traceObject.TraceRay(ray, 0, 1.0, objects, lights, background, pointCol, maxDepth);
			//debugTmpRemoveLater = traceObject.TraceRay(ray, 0, 1.0, objectsTraceRay, lights, illuminations, background, pointCol, maxDepth);

			if (debugTmpRemoveLater.GetGreen() == 1)
				bool testIfGreen = false;
			double rt = debugTmpRemoveLater.GetRed();
			double gt = debugTmpRemoveLater.GetGreen();
			double bt = debugTmpRemoveLater.GetBlue();

			if (setSpecificPixel_debug)
			{
				tmp = tmp + ColourClass(0, 0, 0);
			}
			else
			{
				tmp = tmp + debugTmpRemoveLater;
			}
			// Only this line should be here instead of above if condition tmp = tmp + debugTmpRemoveLater;
			
#pragma region multisampling
			/*//Multisampling using 4 points for a pixel

			VectorClass val1 = VectorClass(val.getX() - pw2, val.getY() + ph2, val.getZ());
			VectorClass val2 = VectorClass(val.getX() + pw2, val.getY() + ph2, val.getZ());
			VectorClass val3 = VectorClass(val.getX() + pw2, val.getY() - ph2, val.getZ());
			VectorClass val4 = VectorClass(val.getX() - pw2, val.getY() - ph2, val.getZ());

			VectorClass direction1 = (val1 - originalCamera.GetPosition()).normalize();
			VectorClass direction2 = (val2 - originalCamera.GetPosition()).normalize();
			VectorClass direction3 = (val3 - originalCamera.GetPosition()).normalize();
			VectorClass direction4 = (val4 - originalCamera.GetPosition()).normalize();

			RayClass ray1(originalCamera.GetPosition(), direction1);
			RayClass ray2(originalCamera.GetPosition(), direction2);
			RayClass ray3(originalCamera.GetPosition(), direction3);
			RayClass ray4(originalCamera.GetPosition(), direction4);

			ColourClass debugTmpRemoveLater1 = TraceRay(ray1, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater1;
			ColourClass debugTmpRemoveLater2 = TraceRay(ray2, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater2;
			ColourClass debugTmpRemoveLater3 = TraceRay(ray3, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater3;
			ColourClass debugTmpRemoveLater4 = TraceRay(ray4, 0, 1.0, objects, objectCount, lights, lightsCount, illuminations, background, pointCol, position);
			tmp = tmp + debugTmpRemoveLater4;

			tmp = tmp / (noOfSamples);*/
#pragma endregion

			pixels[position].SetRed(tmp.GetRed());
			pixels[position].SetGreen(tmp.GetGreen());
			pixels[position].SetBlue(tmp.GetBlue());

			position++;
		}
	}
}

void Render::render(int screenHeight, int screenWidth, double pixelW, double pixelH, double f,
					VectorClass startPixel, VectorClass camU, VectorClass camV, CameraClass originalCamera,
					KDNode kdtree, std::vector<VectorClass*> lights, ColourClass background, 
					ColourClass pointCol, ColourClass *pixels, int maxDepth)

{
	int position = 0, testCounter = 0;
	int noOfSamples = 4;

	//////////////////////////////////////////////////////////
	bool onceflag = true;

	Tracing traceObject = Tracing();
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			ColourClass tmp = ColourClass(0, 0, 0);

			VectorClass val = VectorClass(startPixel.getX() + camU.getX() * (j + 0.5) * pixelW + camV.getX() * (i + 0.5) * pixelH,
				startPixel.getY() + camU.getY() * (j + 0.5) * pixelW + camV.getY() * (i + 0.5) * pixelH,
				-f);

			VectorClass direction = (val - originalCamera.GetPosition()).normalize();
			RayClass ray(originalCamera.GetPosition(), direction);

			
			bool setSpecificPixel_debug = 0;

			
			if (i == 90 && j == 240)
				//if (i == 9 && j == 280)
			{
				setSpecificPixel_debug = 0;
			}
			ColourClass debugTmpKDRemoveLater;
			debugTmpKDRemoveLater = traceObject.TraceRayKD(ray, 0, 1.0, kdtree, lights, background, pointCol, maxDepth);;

			double ddr = debugTmpKDRemoveLater.GetRed();
			double ddg = debugTmpKDRemoveLater.GetGreen();
			double ddb = debugTmpKDRemoveLater.GetBlue();

			if (setSpecificPixel_debug)
			{
				tmp = tmp + ColourClass(0, 0, 0);
			}
			else
			{
				tmp = tmp + debugTmpKDRemoveLater;
			}

			pixels[position].SetRed(tmp.GetRed());
			pixels[position].SetGreen(tmp.GetGreen());
			pixels[position].SetBlue(tmp.GetBlue());

			position++;
		}
	}
}

void Render::rt1wRender(std::vector<ObjectClass*> objects_debug, ColourClass background,
	ColourClass* pixels_debug, int imageHeight, int imageWidth)
{
	int position_debug = 0;

	Tracing traceObject_d = Tracing();

	//CameraClass cam(0,0);
	CameraClass cam(90, double(imageWidth) / double(imageHeight), VectorClass(0, 0, 0), VectorClass(0, 0, -1), VectorClass(0, 1, 0));

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		for (int i = 0; i < imageWidth; ++i)
		{
			double u = double(i) / double(imageWidth);
			double v = double(j) / double(imageHeight);

			//VectorClass tempDirection = lowerLeftCorner_d + horizontal_d * u + vertical_d * v;
			//RayClass ray_d(origin_d, tempDirection);
			RayClass ray_d = cam.getRay(u, v);

			ColourClass pixelColour;
			pixelColour = traceObject_d.TraceRay_rt1w(ray_d, objects_debug);

			/*
			// This is what the Tracing class will replace.
			double tForSphere = SphereClass(0.5, VectorClass(0, 0, -1)).GetIntersection(ray_d);

			if (tForSphere > 0.0)
			{
				VectorClass normalSphere = (ray_d.at(tForSphere) - VectorClass(0.0, 0.0, -1)).normalize();
				pixelColour = VectorClass(normalSphere.getX() + 1.0,
					normalSphere.getY() + 1.0,
					normalSphere.getZ() + 1.0) * 0.5;
			}
			else
			{
				pixelColour = ray_d.colour();
			}
			*/
			int ir = int(255.99 * pixelColour.GetRed());
			int ig = int(255.99 * pixelColour.GetGreen());
			int ib = int(255.99 * pixelColour.GetBlue());

			pixels_debug[position_debug].SetRed(ir);//pixelColour.GetRed());
			pixels_debug[position_debug].SetGreen(ig);//pixelColour.GetGreen());
			pixels_debug[position_debug].SetBlue(ib);




			position_debug++;
		}
	}
}