#pragma once

#include "../include/gmlvector.h"

namespace gml
{
	int get_float_exponent_base2(float d);

	float determinant_impl(
		float a00, float a01, 
		float a10, float a11);

	float determinant_impl(
		float a00, float a01, float a02, 
		float a10, float a11, float a12, 
		float a20, float a21, float a22);

	float determinant_impl(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);
}
