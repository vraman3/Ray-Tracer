#pragma once
#include "VectorClass.h"
#include "CameraClass.h"

class Render
{
	public:
		/* Variables */

		/* Constructors */

		/* Functions */
		void render(int screenHeight, int screenWidth, double pixelW, double pixelH, double f, 
					VectorClass startPixel, VectorClass camU, VectorClass camV, CameraClass camera,
					bool dataStructure);

};