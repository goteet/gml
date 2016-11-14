#pragma once

namespace gml
{
	constexpr double PI_d = 3.14159265358979323846;
	constexpr float PI = static_cast<float>(PI_d);


	bool fequal(float a, float b);

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

	enum it_mode
	{
		it_none,
		it_hit,
		it_contain,
		it_inside,
		it_same,
	};
}