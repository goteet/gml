#pragma once

namespace gml
{
	constexpr const double PI = 3.14159265358979323846;

	bool fequal(float a, float b);

	class radian;
	class degree;

	class radian
	{
	public:
		radian();
		explicit radian(float v);
		operator degree() const;
		operator float() const;
		radian operator-();
		radian operator+(const radian&) const;
		radian operator-(const radian&) const;
		radian operator*(float scaler) const;
		radian& operator+=(const radian&);
		radian& operator-=(const radian&);
		radian& operator*=(float scaler);
		float value;
	};

	class degree
	{
	public:
		degree();
		explicit degree(float v);
		operator radian() const;
		operator float() const;
		degree operator-();
		degree operator+(const degree&) const;
		degree operator-(const degree&) const;
		degree operator*(float scaler) const;
		degree& operator+=(const degree&);
		degree& operator-=(const degree&);
		degree& operator*=(float scaler);
		float value;
	};

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

	enum it_mode
	{
		it_none,
		it_contain,
		it_inside,
		it_intersect,
		it_same,
	};
}