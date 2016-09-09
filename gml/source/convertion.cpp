#include "../include/gmlconv.h"
#include <cmath>

namespace gml
{
	mat33 to_mat33(const quat& q)
	{
		mat33 rst;
		vec3 vsqr2 = q.v * q.v * 2;
		float xy2 = q.v.x * q.v.y * 2;
		float yz2 = q.v.y * q.v.z * 2;
		float zx2 = q.v.z * q.v.x * 2;
		float wx2 = q.w * q.v.x * 2;
		float wy2 = q.w * q.v.y * 2;
		float wz2 = q.w * q.v.z * 2;

		rst._00 = 1 - vsqr2.y - vsqr2.z;
		rst._11 = 1 - vsqr2.z - vsqr2.x;
		rst._22 = 1 - vsqr2.x - vsqr2.y;

		rst._01 = xy2 - wz2;
		rst._02 = zx2 + wy2;

		rst._10 = xy2 + wz2;
		rst._12 = yz2 - wx2;

		rst._20 = zx2 - wy2;
		rst._21 = yz2 + wx2;

		return rst;
	}
	mat44 to_mat44(const quat& q)
	{
		mat44 rst(to_mat33(q));
		return rst;
	}
	quat to_quat(const mat44& mat)
	{
		float wsqr = mat._00 + mat._11 + mat._22;
		float xsqr = mat._00 - mat._11 - mat._22;
		float ysqr = mat._11 - mat._00 - mat._22;
		float zsqr = mat._22 - mat._00 - mat._11;

		int maxIndex = 0;
		float maxSqr = wsqr;
		if (xsqr > maxSqr)
		{
			maxSqr = xsqr;
			maxIndex = 1;
		}
		if (ysqr > maxSqr)
		{
			maxSqr = ysqr;
			maxIndex = 2;
		}
		if (zsqr > maxSqr)
		{
			maxSqr = zsqr;
			maxIndex = 3;
		}

		maxSqr = sqrtf(maxSqr + 1) * 0.5f;
		float base = 0.25f / maxSqr;
		quat rst;
		switch (maxIndex)
		{
		case 0:
			rst.w = maxSqr;
			rst.v.x = (mat._12 - mat._21) * base;
			rst.v.y = (mat._20 - mat._02) * base;
			rst.v.z = (mat._01 - mat._10) * base;
			break;
		case 1:
			rst.v.x = maxSqr;
			rst.w = (mat._12 - mat._21) * base;
			rst.v.y = (mat._01 + mat._10) * base;
			rst.v.z = (mat._02 + mat._20) * base;
			break;
		case 2:
			rst.v.y = maxSqr;
			rst.w = (mat._20 - mat._02) * base;
			rst.v.x = (mat._01 + mat._10) * base;
			rst.v.z = (mat._12 + mat._21) * base;
			break;
		case 3:
			rst.v.z = maxSqr;
			rst.w = (mat._01 - mat._10) * base;
			rst.v.x = (mat._02 + mat._20) * base;
			rst.v.y = (mat._12 + mat._21) * base;
			break;
		}
		return rst.normalize();
	}
}