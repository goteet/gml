#include "../include/gmlvector.h"
#include "../include/gmlutility.h"
#include <cmath>
#include <cassert>
#include "inner_util.h"

namespace gml
{
	const vec3& vec3::zero()
	{
		static vec3 v(0.0f, 0.0f, 0.0f);
		return v;
	}
	const vec3& vec3::one()
	{
		static vec3 v(1.0f, 1.0f, 1.0f);
		return v;
	}
	const vec3& vec3::left()
	{
		static vec3 v(-1.0f, 0.0f, 0.0f);
		return v;
	}
	const vec3& vec3::right()
	{
		static vec3 v(1.0f, 0.0f, 0.0f);
		return v;
	}
	const vec3& vec3::up()
	{
		static vec3 v(0.0f, 1.0f, 0.0f);
		return v;
	}
	const vec3& vec3::down()
	{
		static vec3 v(0.0f, -1.0f, 0.0f);
		return v;
	}
	const vec3& vec3::forward()
	{
		static vec3 v(0.0f, 0.0f, 1.0f);
		return v;
	}
	const vec3& vec3::backward()
	{
		static vec3 v(0.0f, 0.0f, -1.0f);
		return v;
	}

	vec3::vec3()
	{
	}

	vec3::vec3(float x, float y, float z)
	{
		set(x, y, z);
	}

	vec3::vec3(const vec2& v2, float z)
	{
		set(v2, z);
	}

	vec3::vec3(const vec4& v4)
	{
		set(v4.x, v4.y, v4.z);
	}

	vec3 vec3::operator-() const
	{
		return vec3(-x, -y, -z);
	}

	bool vec3::operator==(const vec3& rhs) const
	{
		if (&rhs == this)
			return true;

		return fequal(x, rhs.x) &&
			fequal(y, rhs.y) &&
			fequal(z, rhs.z);
	}

	bool vec3::operator!=(const vec3& rhs) const
	{
		return !(*this == rhs);
	}

	vec3 vec3::operator+(float value) const
	{
		vec3 copy(*this);
		copy += value;
		return copy;
	}

	vec3 vec3::operator-(float value) const
	{
		vec3 copy(*this);
		copy -= value;
		return copy;
	}

	vec3 vec3::operator*(float value) const
	{
		vec3 copy(*this);
		copy *= value;
		return copy;
	}

	vec3 vec3::operator+(const vec3& rhs) const
	{
		return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	vec3 vec3::operator-(const vec3& rhs) const
	{
		return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	vec3 vec3::operator*(const vec3& rhs) const
	{
		return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	vec3& vec3::operator+=(float value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}

	vec3& vec3::operator-=(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	vec3& vec3::operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	vec3& vec3::operator+=(const vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	vec3& vec3::operator-=(const vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	vec3& vec3::operator*=(const vec3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	float& vec3::operator[](int index)
	{
		return const_cast<float&>(const_cast<const vec3*>(this)->operator[](index));
	}

	const float& vec3::operator[](int index) const
	{
		assert(index >= 0 && index < 3);
		return *(&x + index);
	}

	vec3::operator float*()
	{
		return &(this->x);
	}

	void vec3::set(const vec2& v2, float z)
	{
		this->x = v2.x;
		this->y = v2.y;
		this->z = z;
	}

	void vec3::set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void vec3::set(const vec4& v4)
	{
		set(v4.x, v4.y, v4.z);
	}

	void vec3::replace(const vec2& v2)
	{
		x = v2.x;
		y = v2.y;
	}

	vec3 vec3::normalized() const
	{
		vec3 copy(*this);
		copy.normalize();
		return copy;
	}

	void vec3::normalize()
	{
		float length2 = length_sqr();
		if (!fequal(length2, 0.0f))
		{
			if (!fequal(1.0f, length2))
			{
				float invLength = 1.0f / sqrtf(length2);
				this->x *= invLength;
				this->y *= invLength;
				this->z *= invLength;
			}
		}
		else
		{
			*this = zero();
		}
	}

	void vec3::inverse()
	{
		x = 1.0f / x;
		y = 1.0f / y;
		z = 1.0f / z;
	}

	vec3 vec3::inversed() const
	{
		vec3 copy(*this);
		copy.inverse();
		return copy;
	}

	float vec3::length() const
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float vec3::length_sqr() const
	{
		return x*x + y*y + z*z;
	}

	vec3 operator+(float value, const vec3& rhs)
	{
		return rhs + value;
	}

	vec3 operator-(float value, const vec3& rhs)
	{
		return rhs - value;
	}

	vec3 operator*(float value, const vec3& rhs)
	{
		return rhs * value;
	}

	float dot(const vec3& lhs, const vec3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	vec3 cross(const vec3& lhs, const vec3& rhs)
	{
		return vec3(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
			);
	}

	vec3 min_combine(const vec3& lhs, const vec3& rhs)
	{
		return vec3(
			lhs.x < rhs.x ? lhs.x : rhs.x,
			lhs.y < rhs.y ? lhs.y : rhs.y,
			lhs.z < rhs.z ? lhs.z : rhs.z
			);
	}

	vec3 max_combine(const vec3& lhs, const vec3& rhs)
	{
		return vec3(
			lhs.x > rhs.x ? lhs.x : rhs.x,
			lhs.y > rhs.y ? lhs.y : rhs.y,
			lhs.z > rhs.z ? lhs.z : rhs.z
			);
	}

	float det33(const gml::vec3& row1, const gml::vec3& row2, const gml::vec3& row3)
	{
		return determinant_impl(row1.x, row1.y, row1.z, row2.x, row2.y, row2.z, row3.x, row3.y, row3.z);
	}

	float det33_t(const gml::vec3& row1, const gml::vec3& row2, const gml::vec3& row3)
	{
		return determinant_impl(row1.x, row2.x, row3.x, row1.y, row2.y, row3.y, row1.z, row2.z, row3.z);
	}
}