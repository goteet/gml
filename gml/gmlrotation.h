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

		friend bool operator== (const euler& lhs, const euler& rhs);

		friend inline bool operator!= (const euler& lhs, const euler& rhs) { return !(lhs == rhs); }
	};

	class quat
	{
	public:
		static const quat& identity_pos();
		static const quat& identity_neg();

	public:
		float w = 1.0f;
		vec3 v;

	public:
		constexpr quat() = default;

		quat(const vec3& axis, const radian& r);

		friend bool operator== (const quat& lhs, const quat& rhs);

		friend inline bool operator!= (const quat& lhs, const quat& rhs) { return !(lhs == rhs); }

		constexpr const quat& operator+() const { return *this; }

		constexpr quat operator-() const { return *this; }

		friend constexpr quat operator+(const quat& lhs, const quat& rhs);

		friend constexpr quat operator*(const quat& lhs, const quat& rhs);

		friend constexpr quat operator*(const quat& lhs, float rhs);

		friend constexpr quat operator*(float lhs, const quat& rhs);

		friend inline quat& operator+=(quat& lhs, const quat& rhs);

		friend inline quat& operator*=(quat& lhs, const quat& rhs);

		friend inline quat& operator*=(quat& lhs, float rhs);

		void normalize();

		quat normalized() const;

		void conjugate();

		constexpr quat conjugated() const;

		void inverse();

		quat inversed() const;

		float length() const;

		constexpr float length_sqr() const;

	public: //do not use unless you know what happen.
		constexpr quat(float rw, const vec3& rv) : w(rw), v(rv) {	}

		constexpr quat(float rw, float rx, float ry, float rz) : w(rw), v(rx, ry, rz) { }
	};

	constexpr float dot(const quat& lhs, const quat& rhs);

	vec3 rotate(const quat& rotation, const vec3& point);

	quat slerp(const quat& s, const quat& d, float f);
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


namespace gml
{
	inline bool operator== (const euler& lhs, const euler& rhs)
	{
		if (&lhs != &rhs)
		{
			return fequal(lhs.roll, rhs.roll) &&
				fequal(lhs.pitch, rhs.pitch) &&
				fequal(lhs.yaw, rhs.yaw);
		}
		else
		{
			return true;
		}
	}

	inline const quat& quat::identity_pos()
	{
		static quat ipos(1, 0, 0, 0);
		return ipos;
	}
	inline const quat& quat::identity_neg()
	{
		static quat ineg(-1, 0, 0, 0);
		return ineg;
	}

	inline quat::quat(const vec3& axis, const radian& r)
	{
		radian halfRadian = r * 0.5f;

		float halfCos = gml::cos(halfRadian);
		float halfSin = gml::sin(halfRadian);

		v = axis * halfSin;
		w = halfCos;

		normalize();
	}

	inline bool operator== (const quat& lhs, const quat& rhs)
	{
		if (&lhs != &rhs)
		{
			return fequal(lhs.w, rhs.w) && lhs.v == rhs.v;
		}
		else
		{
			return true;
		}
	}

	constexpr quat operator+(const quat& lhs, const quat& rhs)
	{
		return quat(lhs.w + rhs.w, lhs.v + rhs.v);
	}

	constexpr quat operator*(const quat& lhs, const quat& rhs)
	{
		return quat(
			lhs.w * rhs.w - dot(lhs.v, rhs.v),
			lhs.w * rhs.v + rhs.w * lhs.v + cross(lhs.v, rhs.v)
			);
	}

	constexpr quat operator*(const quat& lhs, float rhs)
	{
		return quat(lhs.w * rhs, lhs.v * rhs);
	}

	constexpr quat operator*(float lhs, const quat& rhs)
	{
		return rhs * lhs;
	}

	inline quat& operator+=(quat& lhs, const quat& rhs)
	{
		lhs.w += rhs.w;
		lhs.v += rhs.v;
		return lhs;
	}

	inline quat& operator*=(quat& lhs, const quat& rhs)
	{
		return (lhs = lhs * rhs);
	}

	inline quat& operator*=(quat& lhs, float rhs)
	{
		lhs.w *= rhs;
		lhs.v *= rhs;
		return lhs;
	}

	inline void quat::normalize()
	{
		float length2 = length_sqr();
		if (!fequal(0.0f, length2) && !fequal(1.0f, length2))
		{
			float invLength = 1.0f / sqrtf(length2);
			v *= invLength;
			w *= invLength;
		}
	}

	inline quat quat::normalized() const
	{
		quat rst(*this);
		rst.normalize();
		return rst;
	}

	inline void quat::conjugate()
	{
		v = -v;
		/*w = -w;*/
	}

	constexpr quat quat::conjugated() const
	{
		return quat(w, -v);
	}

	inline void quat::inverse()
	{
		conjugate();
		normalize();
	}

	inline quat quat::inversed() const
	{
		quat rst(*this);
		rst.inverse();
		return rst;
	}

	inline float quat::length() const
	{
		return sqrtf(length_sqr());
	}

	constexpr float quat::length_sqr() const
	{
		return w*w + v.length_sqr();
	}

	constexpr float dot(const quat& lhs, const quat& rhs)
	{
		return lhs.w*rhs.w + dot(lhs.v, rhs.v);
	}

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
		slerp(Qs,Qd,f)	= (sin((1-t)w) / sinw) * Qs + (sin(tw) / sinw)*Qd
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