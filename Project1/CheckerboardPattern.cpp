#include "CheckerboardPattern.h"

CheckerboardPattern::CheckerboardPattern(int w, int h, double inkr, double inkt, double inn) : IlluminationClass(inkr, inkt, inn)
{
	width = w;
	height = h;
}

ColourClass CheckerboardPattern::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{
	double x = pi.GetX();
	double y = pi.GetY();
	double z = pi.GetZ();
	double size = 1.0;

	PhongModel *p = new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0, 0.0);

	int val = 0;

	switch (val)
	{
		//Smooth Colour. Merges cos and sin phases		No
	case 1:return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0) + sin(9 * x)*cos(9 * x), pointCol, position);
		break;

		// Colours straight lines
	case 2:return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0) + sin(9 * x) + sin(9 * x), pointCol, position);
		break;

		//Straight lines with a smooth gradient change      No
	case 3:return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0) + sin(9 * x) + sin(9 * x) * sin(9 * x), pointCol, position);
		break;

		// Equally spaced circular donuts with colour in middle
	case 4:return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0) + sin(9 * x) + sin(9 * x)* sin(9 * z), pointCol, position);
		break;

		// Offset, equally spaced, more dense donuts with colour in middle
	case 5:return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0) + sin(9 * x)* sin(9 * z) + sin(9 * x)* sin(9 * z), pointCol, position);
		break;

		//Default checkerboard
	default:
		if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)
			return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0), pointCol, position);
		else
			return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 1.0, 0.0), pointCol, position);
		break;
	}

	/*if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)
	return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0) + sin(5*x), pointCol, position);
	else
	return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 1.0, 0.0) + sin(5*x), pointCol, position);*/

	// Scale by sin
	//return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0) + sin(9 * x), pointCol, position);

	// Disco light lol
	//return p->GetIllumination(pi, ray, N, L, V, ColourClass(sin(x), sin(y), sin(z)), pointCol, position);

	// Weird wood thing
	/*if ( (int)(x*x + z*z) % 2 == 0)
	return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 0.0, 0.0), pointCol, position);
	else
	return p->GetIllumination(pi, ray, N, L, V, ColourClass(1.0, 1.0, 0.0), pointCol, position);*/

}