#pragma once
#include <gmlrotation.h>
#include <gmlutility.h>
#include <gmlangle.h>

namespace gml
{
	class dquat
	{
	public:
		static const dquat& I() { static dquat dq; return dq; }

	public:
		quat real;
		quat dual;

	public:
		constexpr dquat() : real(1, 0, 0, 0), dual(0, 0, 0, 0) { }

		inline dquat(const quat& rotation, const vec3 translation)
			: real(rotation)
			, dual(0, translation)
		{
			real.normalize();
			dual = 0.5 * dual * real;
		}

		//rotate and translate
		inline dquat(const vec3& axis, const radian& r, const vec3& translation)
			: real(axis, r)
			, dual(0, translation)
		{
			dual = 0.5f * dual * real;
		}

		//only rotate
		inline dquat(const vec3& axis, const radian& r) : real(axis, r), dual(0, 0, 0, 0) { }

		//only translation
		constexpr dquat(const vec3& translation) : real(1, 0, 0, 0), dual(0, translation * 0.5f) { }

		//only translation
		constexpr dquat(float x, float y, float z) : real(1, 0, 0, 0), dual(0, x*0.5f, y*0.5f, z*0.5f) { }

		constexpr quat get_rotation() const { return real; }

		inline vec3 get_translation() const { return (2.0f * dual * real.conjugated()).v; }

		inline radian get_rotate_radian() const { return radian(2 * acos(real.w)); }

		inline dquat operator+ (const dquat& rhs) const
		{
			dquat rst(*this);
			rst += rhs;
			return rst;
		}

		inline dquat operator* (const dquat& rhs) const
		{
			dquat rst(*this);
			rst *= rhs;
			return rst;
		}

		inline dquat operator* (float rhs) const
		{
			dquat rst(*this);
			rst *= rhs;
			return rst;
		}

		inline dquat& operator+=(const dquat& rhs)
		{
			this->real += rhs.real;
			this->dual += rhs.dual;
			return *this;
		}

		inline dquat& operator*=(const dquat& rhs)
		{
			quat newR = real*rhs.real;
			quat newD = real*rhs.dual + dual*rhs.real; //noticing the order.
			real = newR;
			dual = newD;
			return *this;
		}

		inline dquat& operator*=(float scaler)
		{
			real *= scaler;
			dual *= scaler;
			return *this;
		}

		inline void normalize()
		{
			float l = length();
			if (!fequal(l, 0.0f))
			{
				if (!fequal(l, 1.0f))
				{
					auto invL = 1.0f / l;
					this->real *= invL;
					this->dual *= invL;
				}
			}
		}

		inline dquat normalized() const
		{
			dquat rst(*this);
			rst.normalize();
			return rst;
		}

		inline void conjugate()
		{
			real.conjugate();

			//q = -q && q.w =0;
			// => q.conjugate() = -q = q
			// so.... what....
			dual.conjugate();
		}

		inline dquat conjugated() const
		{
			dquat rst(*this);
			rst.conjugate();
			return rst;
		}

		inline void inverse()
		{
			normalize();
			conjugate();
		}

		inline dquat inversed() const
		{
			dquat rst(*this);
			rst.inverse();
			return rst;
		}

		inline void exponent(float t)
		{
			float invr = 1.0f / sqrtf(length());
			// change the pitch. //
			// Screw parameters
			radian r = get_rotate_radian();
			float pitch = dual.w * invr; //-2 * dual.w * invr
			vec3 direction = real.v * invr;
			vec3 moment = (dual.v + direction * pitch * real.w) * invr;	//(dual.v - direction * pitch * real.w * 0.5f) * invr

																		// Exponential power 
			r *= t * 0.5f;
			pitch *= t;

			// Convert back to dual-quaternion
			float sinAngle = sin(r); // angle/2
			float cosAngle = cos(r); // angle/2

			real = quat(cosAngle, direction * sinAngle);

			//dual = quat(-pitch * sinAngle * 0.5f , sinAngle * moment + 0.5f * pitch * cosAngle * direction);
			dual = quat(pitch * sinAngle, sinAngle * moment - pitch * cosAngle * direction);
		}

		inline dquat exponented(float t) const
		{
			auto result(*this);
			result.exponent(t);
			return result;
		}

		constexpr inline float length() const { return dot(real, real); }

	public://unless you know what u r doing.
		inline dquat(const quat &rotation, const quat& translation) : real(rotation.normalized()), dual(translation) {		}
	};

	inline dquat operator*(float scaler, const dquat& rhs) { return rhs * scaler; }

	constexpr float dot(const dquat& lhs, const dquat& rhs) { return dot(lhs.real, rhs.real); }

	inline vec3 transform(const dquat& dq, const vec3& point)
	{
		dquat inv = dq.inversed();
		inv.dual = -inv.dual;

		dquat pt = dquat(quat::Ipos(), quat(0, point));
		dquat rst = dq * pt * inv;
		return rst.dual.v;
	}

	inline dquat sc_lerp(const dquat& from, const dquat& to, float t)
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
		diff.exponent(t);
		return from * diff;
	}
}
