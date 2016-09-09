#include "../include/gmlvector.h"
#include "../include/gmlutility.h"
#include <cassert>
#include <cmath>
#include "inner_util.h"

namespace gml
{
	vec4::vec4() { }

	vec4::vec4(float x, float y, float z, float w)
	{
		set(x, y, z, w);
	}

	vec4::vec4(const vec2& v2, float z, float w)
	{
		set(v2, z, w);
	}

	vec4::vec4(const vec3& v3, float w)
	{
		set(v3, w);
	}

	bool vec4::operator==(const vec4& rhs) const
	{
		if (&rhs == this)
			return true;

		return fequal(x, rhs.x) &&
			fequal(y, rhs.y) &&
			fequal(z, rhs.z) &&
			fequal(w, rhs.w);
	}

	bool vec4::operator!=(const vec4& rhs) const
	{
		return !(*this == rhs);
	}

	vec4 vec4::operator*(float value) const
	{
		vec4 copy(*this);
		copy *= value;
		return copy;
	}

	vec4& vec4::operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	//hack
	float& vec4::operator[](int index)
	{
		return const_cast<float&>(const_cast<const vec4*>(this)->operator[](index));
	}

	const float& vec4::operator[](int index) const
	{
		assert(index >= 0 && index < 4);
		return *(&x + index);
	}

	vec4::operator float*()
	{
		return &(this->x);
	}

	vec4& vec4::set(const vec2& v2, float z, float w)
	{
		this->x = v2.x;
		this->y = v2.y;
		this->z = z;
		this->w = w;
		return *this;
	}

	vec4& vec4::set(const vec3& v3, float w)
	{
		this->x = v3.x;
		this->y = v3.y;
		this->z = v3.z;
		this->w = w;
		return *this;
	}

	vec4& vec4::set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		return *this;
	}

	vec4& vec4::replace(const vec2& v2)
	{
		this->x = v2.x;
		this->y = v2.y;
		return *this;
	}

	vec4& vec4::replace(const vec3& v3)
	{
		this->x = v3.x;
		this->y = v3.y;
		this->z = v3.z;
		return *this;
	}

	float vec4::length() const
	{
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	float vec4::length_sqr() const
	{
		return x*x + y*y + z*z + w*w;
	}

	float dot(const vec4& lhs, const vec4& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}

	float det44(const gml::vec4& row1, const gml::vec4& row2, const gml::vec4& row3, const gml::vec4& row4)
	{
		return determinant_impl(
			row1.x, row1.y, row1.z, row1.w,
			row2.x, row2.y, row2.z, row2.w,
			row3.x, row3.y, row3.z, row3.w,
			row4.x, row4.y, row4.z, row4.w
			);
	}

	float det44_t(const gml::vec4& row1, const gml::vec4& row2, const gml::vec4& row3, const gml::vec4& row4)
	{
		return determinant_impl(
			row1.x, row2.y, row3.z, row4.w,
			row1.x, row2.y, row3.z, row4.w,
			row1.x, row2.y, row3.z, row4.w,
			row1.x, row2.y, row3.z, row4.w
			);
	}
}