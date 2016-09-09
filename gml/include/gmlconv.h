#pragma once
#include <gmlmatrix.h>
#include <gmlquaternion.h>

namespace gml
{
	mat33 to_mat33(const quat&);
	mat44 to_mat44(const quat&);
	quat to_quat(const mat44&);
}
