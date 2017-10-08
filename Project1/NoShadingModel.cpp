#include "NoShadingModel.h"

NoShadingModel::NoShadingModel(double inkr, double inkt, double inn) : IlluminationClass(inkr, inkt, inn)
{}

ColourClass NoShadingModel::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{
	//return ColourClass(0,0,0);

	return objColour;
}