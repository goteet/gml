#pragma once
#include <gmlrotation.h>
#include <gmlutility.h>

namespace gml
{
	class dquat
	{
	public:
		static const dquat& I();

	public:
		quat real;
		quat dual;

	public:
		dquat();

		dquat(const quat& rotation, const vec3 translation);

		dquat(const vec3& axis, const radian& r, const vec3& translation);//rotate and translate

		dquat(const vec3& axis, const radian& r); //only rotate

		dquat(const vec3& translation);//only translation

		dquat(float x, float y, float z);//only translation

		quat get_rotation() const;

		vec3 get_translation() const;

		radian get_rotate_radian() const;

		dquat operator+ (const dquat& rhs) const;

		dquat operator* (const dquat& rhs) const;

		dquat operator* (float scaler) const;

		dquat& operator+=(const dquat& rhs);

		dquat& operator*=(const dquat& rhs);

		dquat& operator*=(float scaler);

		dquat& normalize();

		dquat normalized() const;

		dquat& conjugate();

		dquat conjugated() const;

		dquat& inverse();

		dquat inversed() const;

		dquat& exponent(float t);

		dquat exponented(float t) const;

		float length() const;

	public:
		dquat(const quat &r, const quat& t);//unless you know what u r doing.
	};

	dquat operator*(float scaler, const dquat& rhs);

	float dot(const dquat& lhs, const dquat& rhs);

	vec3 transform(const dquat& dq, const vec3& point);

	dquat sc_lerp(const dquat& from, const dquat& to, float t);
}
