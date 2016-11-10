#include "../include/gmlutility.h"
#include "inner_util.h"

namespace gml
{
	constexpr static const float a2r_factor = static_cast<float>(PI / 180.0);
	constexpr static const float r2a_factor = 1.0f / a2r_factor;
	float a2r(float angle) { return angle * a2r_factor; }
	float r2a(float raian) { return raian * a2r_factor; }

	radian::radian(float v) : value(v) {}

	radian::operator degree() const { return degree(r2a(value)); }

	radian::operator float() const { return value; }

	radian radian::operator+(const radian& other) const { return radian(*this) += other; }

	radian radian::operator-(const radian& other) const { return radian(*this) -= other; }

	radian radian::operator*(float scaler) const { return radian(*this) *= scaler; }

	radian& radian::operator+=(const radian& other) { value += other.value; return *this; }

	radian& radian::operator-=(const radian& other) { value -= other.value; return *this; }

	radian& radian::operator*=(float scaler) { value *= scaler; return *this; }

	degree::degree(float v) : value(v) {}

	degree::operator radian() const { return radian(a2r(value)); }

	degree::operator float() const { return value; }

	degree degree::operator+(const degree& other) const { return degree(*this) += other; }

	degree degree::operator-(const degree& other) const { return degree(*this) -= other; }

	degree degree::operator*(float scaler) const { return degree(*this) *= scaler; }

	degree& degree::operator+=(const degree& other) { value += other.value; return *this; }

	degree& degree::operator-=(const degree& other) { value -= other.value; return *this; }

	degree& degree::operator*=(float scaler) { value *= scaler; return *this; }


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

	int get_float_exponent_base2(float d)
	{
		int i = 0;
		((short *)(&i))[0] = (((short *)(&d))[1] & (short)0x7FC0); // _123456789ab____ & 0111111110000000
		return (i >> 7) - 127;
	}

	float determinant_impl(
		float a00, float a01,
		float a10, float a11)
	{
		return a00 * a11 - a01 * a10;
	}

	float determinant_impl(
		float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22)
	{
		return a00 * determinant_impl(a11, a12,
			a21, a22)
			- a01 * determinant_impl(a10, a12,
				a20, a22)
			+ a02 * determinant_impl(a10, a11,
				a20, a21);
	}

	float determinant_impl(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33)
	{
		return a00 * determinant_impl(a11, a12, a13,
			a21, a22, a23,
			a31, a32, a33)

			- a01 * determinant_impl(a10, a12, a13,
				a20, a22, a23,
				a30, a32, a33)

			+ a02 * determinant_impl(a10, a11, a13,
				a20, a21, a23,
				a30, a31, a33)

			- a03 * determinant_impl(a10, a11, a12,
				a20, a21, a22,
				a30, a31, a32);
	}
}