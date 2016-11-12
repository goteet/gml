#pragma once
#include <gmlvector.h>
#include <gmlutility.h>
#include <gmlangle.h>

namespace gml
{
	class euler
	{
	public:
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;

	public:
		euler() = default;

		euler(float roll, float pitch, float yaw);

		euler(const vec3& v);
	};

	class quat
	{
	public:
		static const quat& Ipos();
		static const quat& Ineg();

	public:
		float w = 1.0f;
		vec3 v;

	public:
		quat() = default;

		quat(const vec3& axis, const radian& r);

		quat operator-() const;

		quat operator+(const quat& rhs) const;

		quat operator*(const quat& rhs) const;

		quat operator*(float scaler) const;

		quat& operator+=(const quat& rhs);

		quat& operator*=(const quat& rhs);

		quat& operator*=(float scaler);

		void normalize();

		quat normalized() const;

		void conjugate();

		quat conjugated() const;

		void inverse();

		quat inversed() const;

		float length() const;

		float length_sqr() const;

	public:
		quat(float rw, const vec3& rv);//do not use unless you know what happen.

		quat(float rw, float rx, float ry, float rz);//do not use unless you know what happen.
	};

	quat operator*(float scaler, const quat& q);

	float dot(const quat& lhs, const quat& rhs);

	vec3 rotate(const quat& rotation, const vec3& point);

	quat slerp(const quat& s, const quat& d, float f);

	// quaternion to euler angle.
	euler to_eular(const quat& q);

	// euler angle to quaternion.
	quat to_quaternion(const euler& e);
}
