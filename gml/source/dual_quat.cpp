#include "../include/gmldualquat.h"
#include "../include/gmlutility.h"

#include <cmath>
namespace gml
{
	const dquat& dquat::I()
	{
		static dquat dq;
		return dq;
	}

	dquat::dquat() : real(1, 0, 0, 0), dual(0, 0, 0, 0) {}

	dquat::dquat(const quat &rotation, const quat& translation) : real(rotation), dual(translation)
	{
		real.normalize();
	}

	dquat::dquat(const quat& rotation, const vec3 translation)
		: real(rotation)
		, dual(0, translation)
	{
		real.normalize();
		dual = 0.5 * dual * real;
	}

	dquat::dquat(const vec3& axis, float radius) : real(axis, radius), dual(0, 0, 0, 0) { }

	dquat::dquat(const vec3& translation) : real(1, 0, 0, 0), dual(0, translation * 0.5f) { }

	dquat::dquat(float x, float y, float z) : real(1, 0, 0, 0), dual(0, x, y, z)
	{
		dual.v *= 0.5f;
	}

	dquat::dquat(const vec3& axis, float radius, const vec3& translation)
		: real(axis, radius)
		, dual(0, translation)
	{
		dual = 0.5f * dual * real;
	}

	quat dquat::get_rotation() const
	{
		return real;
	}

	vec3 dquat::get_translation() const
	{
		return (2.0f * dual * real.conjugated()).v;
	}

	float dquat::get_rotate_angle() const
	{
		return 2 * acos(real.w);
	}

	dquat dquat::operator+ (const dquat& rhs) const
	{
		dquat rst(*this);
		rst += rhs;
		return rst;
	}

	dquat dquat::operator* (const dquat& rhs) const
	{
		dquat rst(*this);
		rst *= rhs;
		return rst;
	}

	dquat dquat::operator* (float rhs) const
	{
		dquat rst(*this);
		rst *= rhs;
		return rst;
	}

	dquat& dquat::operator+=(const dquat& rhs)
	{
		this->real += rhs.real;
		this->dual += rhs.dual;
		return *this;
	}

	dquat& dquat::operator*=(const dquat& rhs)
	{
		quat newR = real*rhs.real;
		quat newD = real*rhs.dual + dual*rhs.real; //noticing the order.


		real = newR;
		dual = newD;

		return *this;
	}

	dquat& dquat::operator*=(float scaler)
	{
		real *= scaler;
		dual *= scaler;
		return *this;
	}

	dquat& dquat::normalize()
	{
		float l = length();
		if (!fequal(l, 0))
		{
			if (!fequal(l, 1))
			{
				auto invL = 1.0f / l;
				this->real *= invL;
				this->dual *= invL;
			}
		}
		return *this;
	}

	dquat dquat::normalized() const
	{
		dquat rst(*this);
		return rst.normalize();
	}

	dquat& dquat::conjugate()
	{
		real.conjugate();

		//q = -q && q.w =0;
		// => q.conjugate() = -q = q
		// so.... what....
		dual.conjugate();

		return *this;
	}

	dquat dquat::conjugated() const
	{
		dquat rst(*this);
		return rst.conjugate();
	}

	dquat& dquat::inverse()
	{
		return normalize().conjugate();
	}

	dquat dquat::inversed() const
	{
		dquat rst(*this);
		return rst.inverse();
	}

	dquat& dquat::exponent(float t)
	{
		float invr = 1.0f / sqrtf(length());
		// change the pitch. //
		// Screw parameters
		float angle = get_rotate_angle();
		float pitch = dual.w * invr; //-2 * dual.w * invr
		vec3 direction = real.v * invr;
		vec3 moment = (dual.v + direction * pitch * real.w) * invr;	//(dual.v - direction * pitch * real.w * 0.5f) * invr

		// Exponential power 
		angle *= t * 0.5f;
		pitch *= t;
		
		// Convert back to dual-quaternion
		float sinAngle = sin(angle); // angle/2
		float cosAngle = cos(angle); // angle/2

		real = quat(cosAngle, direction * sinAngle);
		
		//dual = quat(-pitch * sinAngle * 0.5f , sinAngle * moment + 0.5f * pitch * cosAngle * direction);
		dual = quat(pitch * sinAngle, sinAngle * moment - pitch * cosAngle * direction);

		return *this;
	}

	dquat dquat::exponented(float t) const
	{
		auto result(*this);
		return result.exponent(t);
	}

	float dquat::length() const
	{
		return dot(real, real);
	}

	dquat sc_lerp(const dquat& from, const dquat& to, float t)
	{
		
		/* this code piece may cause an unexpected result,
		   which the translation is oppsite from the right direction.

		// Shortest path
		float dotReal = dot(from.real, to.real);
		dquat to_n(to);
		if (dotReal < 0)
		{
			to_n.real = -to_n.real;
			to_n.dual = -to_n.dual;
		}
		*/

		// ScLERP = Qa * (Qa^-1 * Qb)^t 
		dquat diff = from.conjugated() * to;
		return from * diff.exponent(t);
	}

	dquat operator*(float scaler, const dquat& rhs)
	{
		return rhs * scaler;
	}

	float dot(const dquat& lhs, const dquat& rhs)
	{
		return dot(lhs.real, rhs.real);
	}

	vec3 transform(const dquat& dq, const vec3& point)
	{
		dquat inv = dq.inversed();
		inv.dual = -inv.dual;

		dquat pt = dquat(quat::Ipos(), quat(0, point));
		dquat rst = dq * pt * inv;
		return rst.dual.v;
	}
}