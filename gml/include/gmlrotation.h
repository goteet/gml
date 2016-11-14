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
		constexpr euler() = default;

		constexpr euler(float _roll, float _pitch, float _yaw) : roll(_roll), pitch(_pitch), yaw(_yaw) { }

		constexpr euler(const vec3& v) : roll(v.x), pitch(v.y), yaw(v.z) { }
	};
}

namespace gml
{
	class quat
	{
	public:
		inline static const quat& Ipos() { static quat ipos;				return ipos; }
		inline static const quat& Ineg() { static quat ineg(-1, 0, 0, 0);	return ineg; }

	public:
		float w = 1.0f;
		vec3 v;

	public:
		constexpr quat() = default;

		inline quat(const vec3& axis, const radian& r)
		{
			radian halfRadian = r * 0.5f;

			float halfCos = gml::cos(halfRadian);
			float halfSin = gml::sin(halfRadian);

			v = axis * halfSin;
			w = halfCos;

			normalize();
		}

		constexpr const quat& operator+() const { return *this; }

		constexpr quat operator-() const { return quat(w, v); }

		friend constexpr quat operator+(const quat& lhs, const quat& rhs) { return quat(lhs.w + rhs.w, lhs.v + rhs.v); }

		friend constexpr quat operator*(const quat& lhs, const quat& rhs)
		{
			return quat(
				lhs.w * rhs.w - dot(lhs.v, rhs.v),
				lhs.w * rhs.v + rhs.w * lhs.v + cross(lhs.v, rhs.v)
				);
		}

		friend constexpr quat operator*(const quat& lhs, float rhs) { return quat(lhs.w * rhs, lhs.v * rhs); }

		friend constexpr quat operator*(float lhs, const quat& rhs) { return rhs*lhs; }

		friend inline quat& operator+=(quat& lhs, const quat& rhs) { return (lhs = lhs + rhs); }

		friend inline quat& operator*=(quat& lhs, const quat& rhs) { return (lhs = lhs * rhs); }

		friend inline quat& operator*=(quat& lhs, float rhs) { return (lhs = lhs * rhs); }

		inline void normalize()
		{
			float length2 = length_sqr();
			if (!fequal(0.0f, length2) && !fequal(1.0f, length2))
			{
				float invLength = 1.0f / sqrtf(length2);
				v *= invLength;
				w *= invLength;
			}
		}

		inline quat normalized() const
		{
			quat rst(*this);
			rst.normalize();
			return rst;
		}

		inline void conjugate() { v = -v;	/*w = -w;*/ }

		inline quat conjugated() const
		{
			quat rst(*this);
			rst.conjugate();
			return rst;
		}

		inline void inverse()
		{
			conjugate();
			normalize();
		}

		inline quat inversed() const
		{
			quat rst(*this);
			rst.inverse();
			return rst;
		}

		inline float length() const { return sqrtf(length_sqr()); }

		constexpr float length_sqr() const { return w*w + v.length_sqr(); }

	public: //do not use unless you know what happen.
		constexpr quat(float rw, const vec3& rv) : w(rw), v(rv) {	}
		constexpr quat(float rw, float rx, float ry, float rz) : w(rw), v(rx, ry, rz) { }
	};

	constexpr float dot(const quat& lhs, const quat& rhs) { return lhs.w*rhs.w + dot(lhs.v, rhs.v); }

	inline vec3 rotate(const quat& rotation, const vec3& point)
	{
		quat invRotation = rotation.inversed();
		quat tmpPoint(0, point);
		return (rotation * tmpPoint * invRotation).v;
	}

	inline quat slerp(const quat& s, const quat& d, float f)
	{
		/*
		slerp(Qs, Qd, f) = (Qd * Qs^-1)^f * Qs;
		cross(d,s^-1) means the diff from s to d.

		quat rst = cross(d, s.inversed());
		rst.exp(f);
		return cross(rst, s);

		another slerp:
		slerp(Qs,Qd,f) = (sin((1-t)w) / sinw) * Qs + (sin(tw) / sinw)*Qd
		= (sin((1-t)w)*Qs + sin(tw)*Qd) / sinw
		*/
		float cos_w = dot(s, d);
		float f0, f1;
		if (fequal(cos_w, 1)) //means sin_w = 0.0
		{
			f0 = 1.0f - f;
			f1 = f;
		}
		else
		{
			float sin_w = sqrtf(1.0f - cos_w * cos_w);
			float inv_sin_w = 1.0f / sin_w;
			float w = atan2(sin_w, cos_w);

			f0 = sinf((1.0f - f) * w)*inv_sin_w;
			f1 = sinf(f * w)*inv_sin_w;
		}

		return f0 * s + f1 * d;
	}
}

namespace gml
{
	inline euler to_eular(const quat& q)
	{
		vec3 vsqr2 = q.v * q.v * 2;
		float xy2 = q.v.x * q.v.y * 2;
		float yz2 = q.v.y * q.v.z * 2;
		float zx2 = q.v.z * q.v.x * 2;
		float wx2 = q.w * q.v.x * 2;
		float wy2 = q.w * q.v.y * 2;
		float wz2 = q.w * q.v.z * 2;

		return euler(
			atan2(yz2 - wx2, 1 - vsqr2.x - vsqr2.y),
			asin(clamp<float>(-(zx2 + wy2), -1.0f, 1.0f)),
			atan2(xy2 - wz2, 1 - vsqr2.y - vsqr2.z)
			);
	}

	// euler angle to quaternion.
	inline quat to_quaternion(const euler& e)
	{
		vec4 v0(cosf(e.yaw / 2), 0, 0, sinf(e.yaw / 2));
		vec4 v1(cosf(e.pitch / 2), 0, sinf(e.pitch / 2), 0);
		vec4 v2(cosf(e.roll / 2), sinf(e.roll / 2), 0, 0);
		vec4 v = v0 * v1 * v2;
		return quat(v.w, v.x, v.y, v.z);
	}
}
