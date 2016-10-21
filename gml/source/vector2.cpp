#include "../include/gmlvector.h"
#include "../include/gmlutility.h"
#include "inner_util.h"
#include <cmath>
#include <cassert>

namespace gml
{
	const vec2& vec2::zero()
	{
		static vec2 v(0.0f, 0.0f);
		return v;
	}
	const vec2& vec2::one()
	{
		static vec2 v(1.0f, 1.0f);
		return v;
	}
	const vec2& vec2::left()
	{
		static vec2 v(-1.0f, 0.0f);
		return v;
	}
	const vec2& vec2::right()
	{
		static vec2 v(1.0f, 0.0f);
		return v;
	}
	const vec2& vec2::up()
	{
		static vec2 v(0.0f, 1.0f);
		return v;
	}
	const vec2& vec2::down()
	{
		static vec2 v(0.0f, -1.0f);
		return v;
	}

	vec2::vec2()
	{
	}

	vec2::vec2(float x, float y)
	{
		set(x, y);
	}

	vec2::vec2(const vec3& vec3)
	{
		set(vec3.x, vec3.y);
	}

	vec2::vec2(const vec4& vec4)
	{
		set(vec4.x, vec4.y);
	}

	vec2 vec2::operator-() const
	{
		return vec2(-x, -y);
	}

	bool vec2::operator==(const vec2& rhs) const
	{
		if (&rhs == this)
			return true;

		return fequal(x, rhs.x) &&
			fequal(y, rhs.y);
	}

	bool vec2::operator!=(const vec2& rhs) const
	{
		return !(*this == rhs);
	}

	vec2 vec2::operator+(float value) const
	{
		vec2 copy(*this);
		copy += value;
		return copy;
	}

	vec2 vec2::operator-(float value) const
	{
		vec2 copy(*this);
		copy -= value;
		return copy;
	}

	vec2 vec2::operator*(float value) const
	{
		vec2 copy(*this);
		copy *= value;
		return copy;
	}

	vec2 vec2::operator+(const vec2& rhs) const
	{
		return vec2(x + rhs.x, y + rhs.y);
	}


	vec2 vec2::operator-(const vec2& rhs) const
	{
		return vec2(x - rhs.x, y - rhs.y);
	}


	vec2 vec2::operator*(const vec2& rhs) const
	{
		return vec2(rhs.x, rhs.y);
	}

	vec2& vec2::operator+=(float value)
	{
		x += value;
		y += value;
		return *this;
	}

	vec2& vec2::operator-=(float value)
	{
		x -= value;
		y -= value;
		return *this;
	}

	vec2& vec2::operator*=(float value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	vec2& vec2::operator+=(const vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	vec2& vec2::operator-=(const vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	vec2& vec2::operator*=(const vec2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	float& vec2::operator[](int index)
	{
		return const_cast<float&>(const_cast<const vec2*>(this)->operator[](index));
	}

	const float& vec2::operator[](int index) const
	{
		assert(index >= 0 && index < 2);
		return *(&x + index);
	}

	vec2::operator float*()
	{
		return &(this->x);
	}

	vec2& vec2::set(float x, float y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	vec2& vec2::set(const vec3& other)
	{
		set(other.x, other.y);
		return *this;
	}

	vec2& vec2::set(const vec4& other)
	{
		set(other.x, other.y);
		return *this;
	}

	vec2 vec2::normalized() const
	{
		vec2 copy(*this);
		return copy.normalize();
	}

	vec2& vec2::normalize()
	{
		float length2 = length_sqr();
		if (!fequal(length2, 0.0f) && !fequal(1.0f, length2))
		{
			auto invLength = 1.0f / sqrtf(length2);
			x *= invLength;
			y *= invLength;
		}
		else
		{
			*this = zero();
		}
		return *this;
	}

	vec2& vec2::inverse()
	{
		x = 1.0f / x;
		y = 1.0f / y;
		return *this;
	}

	vec2 vec2::inversed() const
	{
		vec2 copy(*this);
		return copy.inverse();
	}

	float vec2::length() const
	{
		return sqrtf(x*x + y*y);
	}

	float vec2::length_sqr() const
	{
		return x*x + y*y;
	}

	vec2 operator+(float value, const vec2& rhs)
	{
		return rhs + value;
	}

	vec2 operator-(float value, const vec2& rhs)
	{
		return rhs - value;
	}

	vec2 operator*(float value, const vec2& rhs)
	{
		return rhs * value;
	}

	float dot(const vec2& lhs, const vec2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	float cross(const vec2& lhs, const vec2& rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}

	vec2 min_combine(const vec2& lhs, const vec2& rhs)
	{
		return vec2(
			lhs.x < rhs.x ? lhs.x : rhs.x,
			lhs.y < rhs.y ? lhs.y : rhs.y
			);
	}

	vec2 max_combine(const vec2& lhs, const vec2& rhs)
	{
		return vec2(
			lhs.x > rhs.x ? lhs.x : rhs.x,
			lhs.y > rhs.y ? lhs.y : rhs.y
			);
	}

	float det22(const gml::vec2& row1, const gml::vec2& row2)
	{
		return determinant_impl(row1.x, row1.y, row2.x, row2.y);
	}

	float det22_t(const gml::vec2& row1, const gml::vec2& row2)
	{
		return determinant_impl(row1.x, row2.x, row1.y, row2.y);
	}
}