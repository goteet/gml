#include "../include/gmlquaternion.h"
#include <cmath>
#include "../include/gmlutility.h"
#include "../include/gmlconv.h"

namespace gml
{
	const quat& quat::Ipos()
	{
		static quat ipos;
		return ipos;
	}
	const quat& quat::Ineg()
	{
		static quat ineg(-1, 0, 0, 0);
		return ineg;
	}

	quat::quat() :w(1), v(0, 0, 0) { }

	quat::quat(float rw, const vec3& rv) : w(rw), v(rv) {	}

	quat::quat(float rw, float rx, float ry, float rz) : w(rw), v(rx, ry, rz) { }

	quat::quat(const vec3& axis, float radius)
	{
		float halfRadius = radius * 0.5f;
		float halfCos = cos(halfRadius);
		float halfSin = sin(halfRadius);

		this->v = axis * halfSin;
		this->w = halfCos;

		normalize();
	}

	quat quat::operator-() const
	{
		quat rst;
		rst.v = -this->v;
		rst.w = -this->w;
		return rst;
	}

	quat quat::operator+(const quat& rhs) const
	{
		quat rst(*this);
		return rst += rhs;
	}

	quat quat::operator*(const quat& rhs) const
	{
		quat rst(
			this->w * rhs.w - dot(this->v, rhs.v),
			this->w * rhs.v + rhs.w * this->v + cross(this->v, rhs.v)
			);
		return rst;
	}

	quat quat::operator*(float scaler) const
	{
		quat rst(*this);
		return rst *= scaler;
	}

	quat& quat::operator+=(const quat& rhs)
	{
		this->v += rhs.v;
		this->w += rhs.w;
		return *this;
	}

	quat& quat::operator*=(const quat& rhs)
	{
		//since operator* will change this.v as long as this.w.
		return *this = *this * rhs;
	}

	quat& quat::operator*=(float scaler)
	{
		this->v *= scaler;
		this->w *= scaler;
		return *this;
	}

	quat& quat::normalize()
	{
		float length2 = length_sqr();
		if (!fequal(0.0f, length2) && !fequal(1.0f, length2))
		{
			float invLength = 1.0f / sqrtf(length2);
			this->v *= invLength;
			this->w *= invLength;
		}

		return *this;
	}

	quat quat::normalized() const
	{
		quat rst(*this);
		return rst.normalize();
	}

	quat& quat::conjugate()
	{
		this->v = -this->v;
		//this->w = -this->w;
		return *this;
	}

	quat quat::conjugated() const
	{
		quat rst(*this);
		return rst.conjugate();
	}

	quat& quat::inverse()
	{
		conjugate();
		if (!fequal(0, length_sqr()))
		{
			return normalize();
		}
		else
		{
			return *this;
		}
	}

	quat quat::inversed() const
	{
		quat rst(*this);
		return rst.inverse();
	}

	float quat::length() const
	{
		return sqrtf(length_sqr());
	}

	float quat::length_sqr() const
	{
		return w*w + v.length_sqr();
	}

	quat operator*(float scaler, const quat& q)
	{
		return q * scaler;
	}

	float dot(const quat& lhs, const quat& rhs)
	{
		return lhs.w*rhs.w + dot(lhs.v, rhs.v);
	}

	vec3 rotate(const quat& rotation, const vec3& point)
	{
		quat invRotation = rotation.inversed();
		quat tmpPoint(0, point);

		return (rotation * tmpPoint * invRotation).v;
	}

	quat slerp(const quat& s, const quat& d, float f)
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

			f0 = sin((1.0f - f) * w)*inv_sin_w;
			f1 = sin(f * w)*inv_sin_w;
		}

		return f0 * s + f1 * d;
	}

    vec3 q2e(const quat& q)
    {
        mat33 m = to_mat33(q);

        return vec3(
            atan2(m._12, m._22),
            asin(clamp<float>(-m._02, -1.0f, 1.0f)),
            atan2(m._01, m._00)
        );
    }
    
    quat e2q(const vec3& euler)
    {
        vec4 v0(cos(euler.z / 2), 0, 0, sin(euler.z / 2));
        vec4 v1(cos(euler.y / 2), 0, sin(euler.y / 2), 0);
        vec4 v2(cos(euler.x / 2), sin(euler.x / 2), 0, 0);
        vec4 v = v0 * v1 * v2;
        return quat(v.w, v.x, v.y, v.z);
    }
}