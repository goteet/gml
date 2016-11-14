#pragma once

#include <gmlutility.h>
#include <cmath>
#include <cassert>

namespace gml
{
	class vec2;
	class vec3;
	class vec4;
}

namespace gml
{
	class vec2
	{
	public:
		inline static const vec2& vec2::zero() { static vec2 v(0.0f, 0.0f);		return v; }
		inline static const vec2& vec2::one() { static vec2 v(1.0f, 1.0f);		return v; }
		inline static const vec2& vec2::left() { static vec2 v(-1.0f, 0.0f);	return v; }
		inline static const vec2& vec2::right() { static vec2 v(1.0f, 0.0f);	return v; }
		inline static const vec2& vec2::up() { static vec2 v(0.0f, 1.0f);		return v; }
		inline static const vec2& vec2::down() { static vec2 v(0.0f, -1.0f);	return v; }

	public:
		float x = 0.0f;
		float y = 0.0f;

	public:
		constexpr vec2() = default;

		constexpr vec2(float _x, float _y) : x(_x), y(_y) { }

		constexpr explicit vec2(const vec3& v3);

		constexpr explicit vec2(const vec4& v4);

		constexpr vec2 operator+() const { return vec2(x, y); }

		constexpr vec2 operator-() const { return vec2(-x, -y); }

		friend inline bool vec2::operator==(const vec2& lhs, const vec2& rhs)
		{
			if (&lhs == &rhs) return true;
			else return fequal(lhs.x, rhs.x) && fequal(lhs.y, rhs.y);
		}

		friend inline bool operator!=(const vec2& lhs, const vec2& rhs) { return !(lhs == rhs); }

		friend constexpr vec2 operator+(const vec2& lhs, float rhs) { return vec2(lhs.x + rhs, lhs.y + rhs); }

		friend constexpr vec2 operator+(float lhs, const vec2& rhs) { return rhs + lhs; }

		friend constexpr vec2 operator-(const vec2& lhs, float rhs) { return vec2(lhs.x - rhs, lhs.y - rhs); }

		friend constexpr vec2 operator-(float lhs, const vec2& rhs) { return -(rhs - lhs); }

		friend constexpr vec2 operator*(const vec2& lhs, float rhs) { return vec2(lhs.x * rhs, lhs.y * rhs); }

		friend constexpr vec2 operator*(float lhs, const vec2& rhs) { return rhs * lhs; }

		friend constexpr vec2 operator+(const vec2& lhs, const vec2& rhs) { return vec2(lhs.x + rhs.x, lhs.y + rhs.y); }

		friend constexpr vec2 operator-(const vec2& lhs, const vec2& rhs) { return vec2(lhs.x - rhs.x, lhs.y - rhs.y); }

		friend constexpr vec2 operator*(const vec2& lhs, const vec2& rhs) { return vec2(lhs.x * rhs.x, lhs.y * rhs.y); }

		friend inline vec2& operator+=(vec2& lhs, float rhs) { return (lhs = lhs + rhs); }

		friend inline vec2& operator-=(vec2& lhs, float rhs) { return (lhs = lhs - rhs); }

		friend inline vec2& operator*=(vec2& lhs, float rhs) { return (lhs = lhs * rhs); }

		friend inline vec2& operator+=(vec2& lhs, const vec2& rhs) { return (lhs = lhs + rhs); }

		friend inline vec2& operator-=(vec2& lhs, const vec2& rhs) { return (lhs = lhs - rhs); }

		friend inline vec2& operator*=(vec2& lhs, const vec2& rhs) { return (lhs = lhs * rhs); }

		//hack
		inline float& operator[](int index) { return const_cast<float&>(const_cast<const vec2*>(this)->operator[](index)); }

		inline const float& operator[](int index) const
		{
			assert(index >= 0 && index < 2);
			return (index < 0 || index >= 2) ? x : *(&x + index);
		}

		inline explicit operator float*() { return const_cast<float*>(const_cast<const vec2*>(this)->operator const float*()); }

		inline explicit operator const float*() const { return &(x); }

		inline void set(float _x, float _y) { x = _x; y = _y; }

		void set(const vec3& v3);

		void set(const vec4& v4);

		inline void normalize()
		{
			float length2 = length_sqr();
			if (!fequal(length2, 0.0f))
			{
				if (!fequal(1.0f, length2))
				{
					auto invLength = 1.0f / sqrtf(length2);
					x *= invLength;
					y *= invLength;
				}
			}
			else
			{
				*this = zero();
			}
		}

		inline vec2 normalized() const
		{
			vec2 copy(*this);
			copy.normalize();
			return copy;
		}

		inline void inverse()
		{
			float length2 = length_sqr();
			if (!fequal(length2, 0.0f))
			{
				x /= length2;
				y /= length2;
			}
			else
			{
				*this = zero();
			}
		}

		inline vec2 inversed() const
		{
			vec2 copy(*this);
			copy.inverse();
			return copy;
		}

		inline float length() const { return sqrtf(length_sqr()); }

		constexpr float length_sqr() const { return x*x + y*y; }
	};

	constexpr float dot(const vec2& lhs, const vec2& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

	constexpr float cross(const vec2& lhs, const vec2& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

	constexpr vec2 min_combine(const vec2& lhs, const vec2& rhs)
	{
		return vec2(
			lhs.x < rhs.x ? lhs.x : rhs.x,
			lhs.y < rhs.y ? lhs.y : rhs.y);
	}

	constexpr vec2 max_combine(const vec2& lhs, const vec2& rhs)
	{
		return vec2(
			lhs.x > rhs.x ? lhs.x : rhs.x,
			lhs.y > rhs.y ? lhs.y : rhs.y);
	}

	constexpr float det22(const gml::vec2& row1, const gml::vec2& row2)
	{
		return gml_impl::determinant(
			row1.x, row1.y,
			row2.x, row2.y);
	}

	constexpr float det22_t(const gml::vec2& row1, const gml::vec2& row2)
	{
		return gml_impl::determinant(
			row1.x, row2.x,
			row1.y, row2.y);
	}
}

namespace gml
{
	class vec3
	{
	public:
		inline static const vec3& vec3::zero() { static vec3 v(0.0f, 0.0f, 0.0f);		return v; }
		inline static const vec3& vec3::one() { static vec3 v(1.0f, 1.0f, 1.0f);		return v; }
		inline static const vec3& vec3::left() { static vec3 v(-1.0f, 0.0f, 0.0f);		return v; }
		inline static const vec3& vec3::right() { static vec3 v(1.0f, 0.0f, 0.0f);		return v; }
		inline static const vec3& vec3::up() { static vec3 v(0.0f, 1.0f, 0.0f);			return v; }
		inline static const vec3& vec3::down() { static vec3 v(0.0f, -1.0f, 0.0f);		return v; }
		inline static const vec3& vec3::forward() { static vec3 v(0.0f, 0.0f, 1.0f);	return v; }
		inline static const vec3& vec3::backward() { static vec3 v(0.0f, 0.0f, -1.0f);	return v; }

	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

	public:
		constexpr vec3() = default;

		constexpr vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

		constexpr vec3(const vec2& v2, float _z) : x(v2.x), y(v2.y), z(_z) { }

		constexpr explicit vec3(const vec4& v4);

		constexpr vec3 operator+() const { return vec3(x, y, z); }

		constexpr vec3 operator-() const { return vec3(-x, -y, -z); }

		friend inline bool vec3::operator==(const vec3& lhs, const vec3& rhs)
		{
			if (&rhs == &lhs)
			{
				return true;
			}
			else
			{
				return fequal(lhs.x, rhs.x) && fequal(lhs.y, rhs.y) && fequal(lhs.z, rhs.z);
			}
		}

		friend inline bool vec3::operator!=(const vec3& lhs, const vec3& rhs) { return !(lhs == rhs); }

		friend constexpr vec3 operator+(const vec3& lhs, float rhs) { return vec3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

		friend constexpr vec3 operator+(float lhs, const vec3& rhs) { return rhs + lhs; }

		friend constexpr vec3 operator-(const vec3& lhs, float rhs) { return vec3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

		friend constexpr vec3 operator-(float lhs, const vec3& rhs) { return -(rhs - lhs); }

		friend constexpr vec3 operator*(const vec3& lhs, float rhs) { return vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

		friend constexpr vec3 operator*(float lhs, const vec3& rhs) { return rhs * lhs; }

		friend constexpr vec3 operator+(const vec3& lhs, const vec3& rhs) { return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

		friend constexpr vec3 operator-(const vec3& lhs, const vec3& rhs) { return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

		friend constexpr vec3 operator*(const vec3& lhs, const vec3& rhs) { return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

		friend inline vec3& operator+=(vec3& lhs, float rhs) { return (lhs = lhs + rhs); }

		friend inline vec3& operator-=(vec3& lhs, float rhs) { return (lhs = lhs - rhs); }

		friend inline vec3& operator*=(vec3& lhs, float rhs) { return (lhs = lhs * rhs); }

		friend inline vec3& operator+=(vec3& lhs, const vec3& rhs) { return (lhs = lhs + rhs); }

		friend inline vec3& operator-=(vec3& lhs, const vec3& rhs) { return (lhs = lhs - rhs); }

		friend inline vec3& operator*=(vec3& lhs, const vec3& rhs) { return (lhs = lhs * rhs); }

		//hack
		inline float& operator[](int index) { return const_cast<float&>(const_cast<const vec3*>(this)->operator[](index)); }

		inline const float& operator[](int index) const
		{
			assert(index >= 0 && index < 3);
			return (index < 0 || index >= 3) ? x : *(&x + index);
		}

		inline explicit operator float*() { return const_cast<float*>(const_cast<const vec3*>(this)->operator const float*()); }

		inline explicit operator const float*() const { return &(x); }

		inline void set(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

		inline void set(const vec2& v2, float _z) { set(v2.x, v2.y, _z); }

		void set(const vec4& v4);

		inline void replace(const vec2& v2) { x = v2.x; y = v2.y; }

		inline void normalize()
		{
			float length2 = length_sqr();
			if (!fequal(length2, 0.0f))
			{
				if (!fequal(1.0f, length2))
				{
					float invLength = 1.0f / sqrtf(length2);
					x *= invLength;
					y *= invLength;
					z *= invLength;
				}
			}
			else
			{
				*this = zero();
			}
		}

		inline vec3 normalized() const
		{
			vec3 copy(*this);
			copy.normalize();
			return copy;
		}

		inline void inverse()
		{
			float length2 = length_sqr();
			if (!fequal(length2, 0.0f))
			{
				x /= length2;
				y /= length2;
				z /= length2;
			}
		}

		inline vec3 inversed() const
		{
			vec3 copy(*this);
			copy.inverse();
			return copy;
		}

		inline float length() const { return sqrtf(length_sqr()); }

		constexpr float length_sqr() const { return x*x + y*y + z*z; }
	};

	constexpr float dot(const vec3& lhs, const vec3& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }

	constexpr vec3 cross(const vec3& lhs, const vec3& rhs)
	{
		return vec3(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
			);
	}

	constexpr vec3 min_combine(const vec3& lhs, const vec3& rhs)
	{
		return vec3(
			lhs.x < rhs.x ? lhs.x : rhs.x,
			lhs.y < rhs.y ? lhs.y : rhs.y,
			lhs.z < rhs.z ? lhs.z : rhs.z
			);
	}

	constexpr vec3 max_combine(const vec3& lhs, const vec3& rhs)
	{
		return vec3(
			lhs.x > rhs.x ? lhs.x : rhs.x,
			lhs.y > rhs.y ? lhs.y : rhs.y,
			lhs.z > rhs.z ? lhs.z : rhs.z
			);
	}

	constexpr float det33(const gml::vec3& row1, const gml::vec3& row2, const gml::vec3& row3)
	{
		return gml_impl::determinant(
			row1.x, row1.y, row1.z,
			row2.x, row2.y, row2.z,
			row3.x, row3.y, row3.z);
	}

	constexpr float det33_t(const gml::vec3& row1, const gml::vec3& row2, const gml::vec3& row3)
	{
		return gml_impl::determinant(
			row1.x, row2.x, row3.x,
			row1.y, row2.y, row3.y,
			row1.z, row2.z, row3.z);
	}
}

namespace gml
{
	class vec4
	{
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

	public:
		constexpr vec4() = default;

		constexpr vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }

		constexpr vec4(const vec2& v2, float _z, float _w) : x(v2.x), y(v2.y), z(_z), w(_w) { }

		constexpr vec4(const vec3& v3, float _w) : x(v3.x), y(v3.y), z(v3.z), w(_w) { }

		friend inline bool operator==(const vec4& lhs, const vec4& rhs)
		{
			if (&rhs == &lhs)
			{
				return true;
			}
			else
			{
				return fequal(lhs.x, rhs.x) && fequal(lhs.y, rhs.y) && fequal(lhs.z, rhs.z) && fequal(lhs.w, rhs.w);
			}
		}

		friend inline bool operator!=(const vec4& lhs, const vec4& rhs) { return !(lhs == rhs); }

		//hack
		inline float& operator[](int index) { return const_cast<float&>(const_cast<const vec4*>(this)->operator[](index)); }

		inline const float& operator[](int index) const
		{
			assert(index >= 0 && index < 4);
			return (index < 0 || index >= 4) ? x : *(&x + index);
		}

		friend constexpr vec4 operator*(const vec4& lhs, const vec4& rhs) { return vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

		inline explicit operator float*() { return const_cast<float*>(const_cast<const vec4*>(this)->operator const float*()); }

		inline explicit operator const float*() const { return &(x); }

		inline void set(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }

		inline void set(const vec2& v2, float _z, float _w) { set(v2.x, v2.y, _z, _w); }

		inline void set(const vec3& v3, float _w) { set(v3.x, v3.y, v3.z, _w); }

		inline void replace(const vec2& v2) { x = v2.x; y = v2.y; }

		inline void replace(const vec3& v3) { x = v3.x; y = v3.y; z = v3.z; }

		inline float length() const { return sqrtf(length_sqr()); }

		constexpr float length_sqr() const { return x*x + y*y + z*z + w*w; }
	};

	constexpr float dot(const vec4& lhs, const vec4& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w; }

	constexpr float det44(const gml::vec4& row1, const gml::vec4& row2, const gml::vec4& row3, const gml::vec4& row4)
	{
		return gml_impl::determinant(
			row1.x, row1.y, row1.z, row1.w,
			row2.x, row2.y, row2.z, row2.w,
			row3.x, row3.y, row3.z, row3.w,
			row4.x, row4.y, row4.z, row4.w
			);
	}

	constexpr float det44_t(const gml::vec4& row1, const gml::vec4& row2, const gml::vec4& row3, const gml::vec4& row4)
	{
		return gml_impl::determinant(
			row1.x, row2.y, row3.z, row4.w,
			row1.x, row2.y, row3.z, row4.w,
			row1.x, row2.y, row3.z, row4.w,
			row1.x, row2.y, row3.z, row4.w
			);
	}
}

namespace gml
{
	constexpr vec2::vec2(const vec3& v3) : x(v3.x), y(v3.y) { }

	constexpr vec2::vec2(const vec4& v4) : x(v4.x), y(v4.y) { }

	inline void vec2::set(const vec3& v3) { set(v3.x, v3.y); }

	inline void vec2::set(const vec4& v4) { set(v4.x, v4.y); }

	constexpr vec3::vec3(const vec4& v4) : x(v4.x), y(v4.y), z(v4.z) { }

	inline void vec3::set(const vec4& v4) { set(v4.x, v4.y, v4.z); }
}

namespace gml
{
	struct _X { constexpr static const int SwizzleIndex = 0; };
	struct _Y { constexpr static const int SwizzleIndex = 1; };
	struct _Z { constexpr static const int SwizzleIndex = 2; };
	struct _W { constexpr static const int SwizzleIndex = 3; };

	template<typename SwizzleX, typename SwizzleY>
	constexpr inline vec2 swizzle(const vec2& v2)
	{
		return vec2(v2[SwizzleX::SwizzleIndex], v2[SwizzleY::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY>
	constexpr inline vec2 swizzle(const vec3& v3)
	{
		return vec2(v3[SwizzleX::SwizzleIndex], v3[SwizzleY::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY>
	constexpr inline vec2 swizzle(const vec4& v4)
	{
		return vec2(v4[SwizzleX::SwizzleIndex], v4[SwizzleY::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ>
	constexpr inline vec3 swizzle(const vec2& v2)
	{
		return vec3(v2[SwizzleX::SwizzleIndex], v2[SwizzleY::SwizzleIndex], v2[SwizzleZ::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ>
	constexpr inline vec3 swizzle(const vec3& v3)
	{
		return vec3(v3[SwizzleX::SwizzleIndex], v3[SwizzleY::SwizzleIndex], v3[SwizzleZ::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ>
	constexpr inline vec3 swizzle(const vec4& v4)
	{
		return vec3(v4[SwizzleX::SwizzleIndex], v4[SwizzleY::SwizzleIndex], v4[SwizzleZ::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ, typename SwizzleW>
	constexpr inline vec4 swizzle(const vec2& v2)
	{
		return vec4(v2[SwizzleX::SwizzleIndex], v2[SwizzleY::SwizzleIndex], v2[SwizzleZ::SwizzleIndex], v2[SwizzleW::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ, typename SwizzleW>
	constexpr inline vec4 swizzle(const vec3& v3)
	{
		return vec4(v3[SwizzleX::SwizzleIndex], v3[SwizzleY::SwizzleIndex], v3[SwizzleZ::SwizzleIndex], v3[SwizzleW::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ, typename SwizzleW>
	inline vec4 swizzle(const vec4& v4)
	{
		return vec4(v4[SwizzleX::SwizzleIndex], v4[SwizzleY::SwizzleIndex], v4[SwizzleZ::SwizzleIndex], v4[SwizzleW::SwizzleIndex]);
	}
}

