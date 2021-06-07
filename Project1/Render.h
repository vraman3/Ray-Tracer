#pragma once
#include "VectorClass.h"
#include "CameraClass.h"
#include "ObjectClass.h"
#include "IlluminationClass.h"
#include "ColourClass.h"
#include "KDNode.h"

class Render
{
	public:
		/* Variables */

		/* Constructors */

		/* Functions */
		void render(int screenHeight, int screenWidth, double pixelW, double pixelH, double f, 
					VectorClass startPixel, VectorClass camU, VectorClass camV, CameraClass camera,
					std::vector<TriangleClass*> objects, std::vector<VectorClass*> lights, ColourClass background, 
					ColourClass pointCol, ColourClass* pixels, int maxDepth);

		void render(int screenHeight, int screenWidth, double pixelW, double pixelH, double f,
					VectorClass startPixel, VectorClass camU, VectorClass camV, CameraClass camera,
					KDNode kdtree, std::vector<VectorClass*> lights, ColourClass background, 
					ColourClass pointCol, ColourClass* pixels, int maxDepth);
};