#include "../include/gmlangle.h"
#include <cmath>


namespace gml
{
	float cos(const radian& r)
	{
		return cosf(r.value);
	}

	float sin(const radian& r)
	{
		return sinf(r.value);
	}
}