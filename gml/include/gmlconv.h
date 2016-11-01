#pragma once
#include <gmlaabb.h>
#include <gmlmatrix.h>
#include <gmlrotation.h>
#include <gmldualquat.h>

namespace gml
{
	mat33 to_mat33(const quat&);
	mat44 to_mat44(const quat&);
	quat to_quat(const mat44&);
	mat44 to_mat44(const dquat& q);
	aabb transform(const mat44& mat, const aabb& aabb);
	aabb2d transform(const mat32& mat, const aabb2d& aabb);
}
