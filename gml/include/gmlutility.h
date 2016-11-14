#pragma once

namespace gml_impl
{
	inline int get_float_exponent_base2(float d)
	{
		int i = 0;
		((short *)(&i))[0] = (((short *)(&d))[1] & (short)0x7FC0); // _123456789ab____ & 0111111110000000
		return (i >> 7) - 127;
	}

	constexpr inline float determinant(
		float a00, float a01,
		float a10, float a11)
	{
		return a00 * a11 - a01 * a10;
	}

	constexpr inline float determinant(
		float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22)
	{
		return a00 * determinant(a11, a12, a21, a22)
			- a01 * determinant(a10, a12, a20, a22)
			+ a02 * determinant(a10, a11, a20, a21);
	}

	constexpr inline float determinant(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33)
	{
		return a00 * determinant(a11, a12, a13, a21, a22, a23, a31, a32, a33)
			- a01 * determinant(a10, a12, a13, a20, a22, a23, a30, a32, a33)
			+ a02 * determinant(a10, a11, a13, a20, a21, a23, a30, a31, a33)
			- a03 * determinant(a10, a11, a12, a20, a21, a22, a30, a31, a32);
	}
}

namespace gml
{
	constexpr double PI_d = 3.14159265358979323846;
	constexpr float PI = static_cast<float>(PI_d);

	inline bool fequal(float a, float b)
	{
		if (a != b)
		{
			int ediff = gml_impl::get_float_exponent_base2(a - b);
			if (ediff > -50)
			{
				int ea = gml_impl::get_float_exponent_base2(a);
				int eb = gml_impl::get_float_exponent_base2(b);
				return ((ediff - eb < -20) && (ediff - ea < -20));
			}
			else
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}

	template<typename T>
	constexpr inline T lerp(T left, T right, float fac)
	{
		return left * (1.0f - fac) + right * fac;
	}

	template<typename T>
	inline void swap(T& a, T& b)
	{
		T tmp = a; a = b; b = tmp;
	}

	template<typename T>
	constexpr T clamp01(T value)
	{
		return (value < T(0)) ? T(0) :
			((value > T(1)) ? T(1) : value);
	}

	template<typename T>
	constexpr T clamp(T value, T minValue, T maxValue)
	{
		return (value < T(minValue)) ? T(minValue) :
			((value > T(maxValue)) ? T(maxValue) : value);
	}

	enum it_mode
	{
		it_none,
		it_hit,
		it_contain,
		it_inside,
		it_same,
	};
}