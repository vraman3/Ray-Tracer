#include "TextureMapping.h"

TextureMapping::TextureMapping(double inu, double inv)
{
	u = inu;
	v = inv;
}

ColourClass TextureMapping::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{

}
