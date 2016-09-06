#pragma once

namespace gml
{
	const double PI = 3.14159265358979323846;

	bool fequal(float a, float b);

	float a2r(float angle);

	float r2a(float raian);

	template<typename T>
	inline T lerp(T left, T right, float fac)
	{
		return left * (1.0f - fac) + right * fac;
	}

	template<typename T>
	inline void swap(T& a, T& b)
	{
		T tmp = a; a = b; b = tmp;
	}

	template<typename T>
	inline T clamp01(T value)
	{
		if (value < T(0))
			return T(0);
		else if (value > T(1))
			return T(1);
		return value;
	}

	template<typename T>
	inline T clamp(T value, T minValue, T maxValue)
	{
		if (value < T(minValue))
			return T(minValue);
		else if (value > T(maxValue))
			return T(maxValue);
		return value;
	}
}