#include "../include/gmlutility.h"
#include "inner_util.h"

namespace gml
{

	bool fequal(float a, float b)
	{
		if (a == b)
			return true;
		int ediff = get_float_exponent_base2(a - b);

		if (ediff < -50)
		{
			return true;
		}
		else
		{
			int ea = get_float_exponent_base2(a);
			int eb = get_float_exponent_base2(b);
			return ((ediff - eb < -20) && (ediff - ea < -20));
		}
	}
}