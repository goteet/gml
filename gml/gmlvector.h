#pragma once

#include <gmlutility.h>
#include <cassert>
#include <cmath>

namespace gml_impl
{
	template<int D> struct vec_s;
}

namespace gml
{

	template<int D> class vec_t : public gml_impl::vec_s<D>
	{
	public:
		constexpr static int DIMENSION = D;

		constexpr vec_t() = default;

		constexpr vec_t(const vec_t& other) = default;

		template<int DD = D, typename = typename std::enable_if<DD == 2>::type>
		constexpr vec_t(float _x, float _y) : vec_s(_x, _y) { }

		template<int DD = D, typename = typename std::enable_if<DD == 3>::type>
		constexpr vec_t(float _x, float _y, float _z) : vec_s(_x, _y, _z) { }

		template<int DD = D, typename = typename std::enable_if<DD == 4>::type>
		constexpr vec_t(float _x, float _y, float _z, float _w) : vec_s(_x, _y, _z, _w) { }

		template<int DD = D, typename = typename std::enable_if<(DD > 3)>::type >
		constexpr explicit vec_t(const vec_t<D - 2>& other, float _z, float _w) : vec_s<4>(other.x, other.y, _z, _w) {  }

		template<int DD = D, typename = typename std::enable_if<(DD > 2)>::type >
		constexpr explicit vec_t(const vec_t<D - 1>& other, float _tail) : vec_s(other, _tail) {  }

		template<int DD>
		constexpr explicit vec_t(const vec_t<DD>& other) : vec_s(other) { }

		friend bool operator==(const vec_t<D>& lhs, const vec_t<D>& rhs);

		friend inline bool operator!=(const vec_t<D>& lhs, const vec_t<D>& rhs) { return !(lhs == rhs); }

		constexpr const vec_t<D>& operator+() const { return *this; }

		vec_t<D> operator-() const;

		friend vec_t<D> operator+(const vec_t<D>& lhs, const vec_t<D>& rhs);

		friend vec_t<D> operator+(const vec_t<D>& lhs, float rhs);

		friend vec_t<D> operator+(float lhs, const vec_t<D>& rhs);

		friend vec_t<D> operator-(const vec_t<D>& lhs, const vec_t<D>& rhs);

		friend vec_t<D> operator-(const vec_t<D>& lhs, float rhs);

		friend vec_t<D> operator-(float lhs, const vec_t<D>& rhs);

		friend vec_t<D> operator*(const vec_t<D>& lhs, const vec_t<D>& rhs);

		friend vec_t<D> operator*(const vec_t<D>& lhs, float rhs);

		friend vec_t<D> operator*(float lhs, const vec_t<D>& rhs);

		friend vec_t<D>& operator+=(vec_t<D>& lhs, const vec_t<D>& rhs);

		friend vec_t<D>& operator+=(vec_t<D>& lhs, float rhs);

		friend vec_t<D>& operator-=(vec_t<D>& lhs, const vec_t<D>& rhs);

		friend vec_t<D>& operator-=(vec_t<D>& lhs, float rhs);

		friend vec_t<D>& operator*=(vec_t<D>& lhs, const vec_t<D>& rhs);

		friend vec_t<D>& operator*=(vec_t<D>& lhs, float rhs);

		float& operator[](int index);

		const float& operator[](int index) const;

		operator float*();

		constexpr explicit operator const float*() const { return &(x); }

		void vec_t<D>::normalize();

		vec_t<D> vec_t<D>::normalized() const;

		void vec_t<D>::inverse();

		vec_t<D> vec_t<D>::inversed() const;

		float vec_t<D>::length() const;

		float vec_t<D>::length_sqr() const;

		void replace(const vec_t<2>& v2);

		void replace(const vec_t<3>& v3);

	public:
		friend inline bool operator==(const vec_t<D>& lhs, const vec_t<D>& rhs)
		{
			for (int i = 0; i < D; i++)
			{
				if (!gml::fequal(lhs[i], rhs[i]))
					return false;
			}
			return true;
		}

		friend inline vec_t<D> operator+(const vec_t<D>& lhs, const vec_t<D>& rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs[i] + rhs[i];
			}
			return r;
		}

		friend inline vec_t<D> operator+(const vec_t<D>& lhs, float rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs[i] + rhs;
			}
			return r;
		}

		friend inline vec_t<D> operator+(float lhs, const vec_t<D>& rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs + rhs[i];
			}
			return r;
		}

		friend inline vec_t<D> operator-(const vec_t<D>& lhs, const vec_t<D>& rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs[i] - rhs[i];
			}
			return r;
		}

		friend inline vec_t<D> operator-(const vec_t<D>& lhs, float rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs[i] - rhs;
			}
			return r;
		}

		friend inline vec_t<D> operator-(float lhs, const vec_t<D>& rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs - rhs[i];
			}
			return r;
		}

		friend inline vec_t<D> operator*(const vec_t<D>& lhs, const vec_t<D>& rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs[i] * rhs[i];
			}
			return r;
		}

		friend inline vec_t<D> operator*(const vec_t<D>& lhs, float rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs[i] * rhs;
			}
			return r;
		}

		friend inline vec_t<D> operator*(float lhs, const vec_t<D>& rhs)
		{
			vec_t<D> r;
			for (int i = 0; i < D; i++)
			{
				r[i] = lhs * rhs[i];
			}
			return r;
		}

		friend inline vec_t<D>& operator+=(vec_t<D>& lhs, const vec_t<D>& rhs)
		{
			for (int i = 0; i < D; i++)
			{
				lhs[i] += rhs[i];
			}
			return lhs;
		}

		friend inline vec_t<D>& operator+=(vec_t<D>& lhs, float rhs)
		{
			for (int i = 0; i < D; i++)
			{
				lhs[i] += rhs;
			}
			return lhs;
		}

		friend inline vec_t<D>& operator-=(vec_t<D>& lhs, const vec_t<D>& rhs)
		{
			for (int i = 0; i < D; i++)
			{
				lhs[i] -= rhs[i];
			}
			return lhs;
		}

		friend inline vec_t<D>& operator-=(vec_t<D>& lhs, float rhs)
		{
			for (int i = 0; i < D; i++)
			{
				lhs[i] -= rhs;
			}
			return lhs;
		}

		friend inline vec_t<D>& operator*=(vec_t<D>& lhs, const vec_t<D>& rhs)
		{
			for (int i = 0; i < D; i++)
			{
				lhs[i] *= rhs[i];
			}
			return lhs;
		}

		friend inline vec_t<D>& operator*=(vec_t<D>& lhs, float rhs)
		{
			for (int i = 0; i < D; i++)
			{
				lhs[i] *= rhs;
			}
			return lhs;
		}
	};

	typedef vec_t<2> vec2;
	typedef vec_t<3> vec3;
	typedef vec_t<4> vec4;

	template<int D> float dot(const vec_t<D>& lhs, const vec_t<D>& rhs);

	constexpr float cross(const vec_t<2>& lhs, const vec_t<2>& rhs);

	constexpr vec_t<3> cross(const vec_t<3>& lhs, const vec_t<3>& rhs);

	template<int D> vec_t<D> min_combine(const vec_t<D>& lhs, const vec_t<D>& rhs);

	template<int D> vec_t<D> max_combine(const vec_t<D>& lhs, const vec_t<D>& rhs);

	struct _0; struct _1;
	struct _X { constexpr static const int SwizzleIndex = 0; };
	struct _Y { constexpr static const int SwizzleIndex = 1; };
	struct _Z { constexpr static const int SwizzleIndex = 2; };
	struct _W { constexpr static const int SwizzleIndex = 3; };

	template<typename SwizzleX, typename SwizzleY>
	constexpr inline vec_t<2> swizzle(const vec_t<2>& v2)
	{
		return vec_t<2>(
			gml_impl::Component(v2, SwizzleX::SwizzleIndex),
			gml_impl::Component(v2, SwizzleY::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY>
	constexpr inline vec_t<2> swizzle(const vec_t<3>& v3)
	{
		return vec_t<2>(
			gml_impl::Component(v3, SwizzleX::SwizzleIndex),
			gml_impl::Component(v3, SwizzleY::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY>
	constexpr inline vec_t<2> swizzle(const vec_t<4>& v4)
	{
		return vec_t<2>(
			gml_impl::Component(v4, SwizzleX::SwizzleIndex),
			gml_impl::Component(v4, SwizzleY::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ>
	constexpr inline vec_t<3> swizzle(const vec_t<2>& v2)
	{
		return vec_t<3>(
			gml_impl::Component(v2, SwizzleX::SwizzleIndex),
			gml_impl::Component(v2, SwizzleY::SwizzleIndex),
			gml_impl::Component(v2, SwizzleZ::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ>
	constexpr inline vec_t<3> swizzle(const vec_t<3>& v3)
	{
		return vec_t<3>(
			gml_impl::Component(v3, SwizzleX::SwizzleIndex),
			gml_impl::Component(v3, SwizzleY::SwizzleIndex),
			gml_impl::Component(v3, SwizzleZ::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ>
	constexpr inline vec_t<3> swizzle(const vec_t<4>& v4)
	{
		return vec_t<3>(
			gml_impl::Component(v4, SwizzleX::SwizzleIndex),
			gml_impl::Component(v4, SwizzleY::SwizzleIndex),
			gml_impl::Component(v4, SwizzleZ::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ, typename SwizzleW>
	constexpr inline vec_t<4> swizzle(const vec_t<2>& v2)
	{
		return vec_t<4>(
			gml_impl::Component(v2, SwizzleX::SwizzleIndex),
			gml_impl::Component(v2, SwizzleY::SwizzleIndex),
			gml_impl::Component(v2, SwizzleZ::SwizzleIndex),
			gml_impl::Component(v2, SwizzleW::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ, typename SwizzleW>
	constexpr inline vec_t<4> swizzle(const vec_t<3>& v3)
	{
		return vec_t<4>(
			gml_impl::Component(v3, SwizzleX::SwizzleIndex),
			gml_impl::Component(v3, SwizzleY::SwizzleIndex),
			gml_impl::Component(v3, SwizzleZ::SwizzleIndex),
			gml_impl::Component(v3, SwizzleW::SwizzleIndex));
	}

	template<typename SwizzleX, typename SwizzleY, typename SwizzleZ, typename SwizzleW>
	inline vec_t<4> swizzle(const vec_t<4>& v4)
	{
		return vec_t<4>(
			gml_impl::Component(v4, SwizzleX::SwizzleIndex),
			gml_impl::Component(v4, SwizzleY::SwizzleIndex),
			gml_impl::Component(v4, SwizzleZ::SwizzleIndex),
			gml_impl::Component(v4, SwizzleW::SwizzleIndex));
	}
}

namespace gml_impl
{
	using gml::vec_t;

	template<> struct vec_s<2>
	{
		static const vec_t<2>& zero();
		static const vec_t<2>& one();
		static const vec_t<2>& left();
		static const vec_t<2>& right();
		static const vec_t<2>& up();
		static const vec_t<2>& down();

		float x = 0.0f;
		float y = 0.0f;

		constexpr vec_s() = default;
		constexpr vec_s(float _x, float _y) : x(_x), y(_y) { }
		constexpr explicit vec_s(const vec_s<3>& other);
		constexpr explicit vec_s(const vec_s<4>& other);

		inline void set(float _x, float _y)
		{
			x = _x; y = _y;
		}

		void set(const vec_t<2>& other);
		void set(const vec_t<3>& other);
		void set(const vec_t<4>& other);
	};

	template<> struct vec_s<3>
	{
		static const vec_t<3>& zero();
		static const vec_t<3>& one();
		static const vec_t<3>& left();
		static const vec_t<3>& right();
		static const vec_t<3>& up();
		static const vec_t<3>& down();
		static const vec_t<3>& forward();
		static const vec_t<3>& backward();

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		constexpr vec_s() = default;
		constexpr vec_s(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
		constexpr explicit vec_s(const vec_s<2>& other, float _z) : x(other.x), y(other.y), z(_z) { }
		constexpr explicit vec_s(const vec_s<4>& other);

		inline void set(float _x, float _y, float _z)
		{
			x = _x; y = _y; z = _z;
		}

		inline void set(const vec_s<2>& other, float _z)
		{
			set(other.x, other.y, _z);
		}

		inline void set(const vec_s<3>& other)
		{
			set(other.x, other.y, other.z);
		}

		void set(const vec_t<3>& other);
		void set(const vec_t<4>& other);
	};

	template<> struct vec_s<4>
	{
		static const vec_t<4>& zero();
		static const vec_t<4>& one();

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		constexpr vec_s() = default;
		constexpr vec_s(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }
		constexpr explicit vec_s(const vec_s<2>& other, float _z, float _w) : x(other.x), y(other.y), z(_z), w(_w) { }
		constexpr explicit vec_s(const vec_s<3>& other, float _w) : x(other.x), y(other.y), z(other.z), w(_w) { }

		inline void set(float _x, float _y, float _z, float _w)
		{
			x = _x; y = _y; z = _z; w = _w;
		}

		void set(const vec_t<4>& other);
	};

	inline void vec_s<2>::set(const vec_t<2>& other)
	{
		set(other.x, other.y);
	}

	constexpr vec_s<2>::vec_s(const vec_s<3>& other) : x(other.x), y(other.y) { }

	constexpr vec_s<2>::vec_s(const vec_s<4>& other) : x(other.x), y(other.y) { }

	inline void vec_s<2>::set(const vec_t<3>& other)
	{
		set(other.x, other.y);
	}

	inline void vec_s<2>::set(const vec_t<4>& other)
	{
		set(other.x, other.y);
	}

	constexpr vec_s<3>::vec_s(const vec_s<4>& other) : x(other.x), y(other.y), z(other.z) { }

	inline void vec_s<3>::set(const vec_t<3>& other)
	{
		set(other.x, other.y, other.z);
	}

	inline void vec_s<3>::set(const vec_t<4>& other)
	{
		set(other.x, other.y, other.z);
	}

	inline void vec_s<4>::set(const vec_t<4>& other)
	{
		set(other.x, other.y, other.z, other.w);
	}

	inline const vec_t<2>& vec_s<2>::zero()
	{
		static vec_t<2> v(0.0f, 0.0f);
		return v;
	}
	inline const vec_t<2>& vec_s<2>::one()
	{
		static vec_t<2> v(1.0f, 1.0f);
		return v;
	}
	inline const vec_t<2>& vec_s<2>::left()
	{
		static vec_t<2> v(-1.0f, 0.0f);
		return v;
	}
	inline const vec_t<2>& vec_s<2>::right()
	{
		static vec_t<2> v(1.0f, 0.0f);
		return v;
	}
	inline const vec_t<2>& vec_s<2>::up()
	{
		static vec_t<2> v(0.0f, 1.0f);
		return v;
	}
	inline const vec_t<2>& vec_s<2>::down()
	{
		static vec_t<2> v(0.0f, -1.0f);
		return v;
	}

	inline const vec_t<3>& vec_s<3>::zero()
	{
		static vec_t<3> v(0.0f, 0.0f, 0.0f);
		return v;
	}
	inline const vec_t<3>& vec_s<3>::one()
	{
		static vec_t<3> v(1.0f, 1.0f, 1.0f);
		return v;
	}
	inline const vec_t<3>& vec_s<3>::left()
	{
		static vec_t<3> v(-1.0f, 0.0f, 0.0f);
		return v;
	}
	inline const vec_t<3>& vec_s<3>::right()
	{
		static vec_t<3> v(1.0f, 0.0f, 0.0f);
		return v;
	}
	inline const vec_t<3>& vec_s<3>::up()
	{
		static vec_t<3> v(0.0f, 1.0f, 0.0f);
		return v;
	}
	inline const vec_t<3>& vec_s<3>::down()
	{
		static vec_t<3> v(0.0f, -1.0f, 0.0f);
		return v;
	}
	inline const vec_t<3>& vec_s<3>::forward()
	{
		static vec_t<3> v(0.0f, 0.0f, 1.0f);
		return v;
	}
	inline const vec_t<3>& vec_s<3>::backward()
	{
		static vec_t<3> v(0.0f, 0.0f, -1.0f);
		return v;
	}

	inline const vec_t<4>& vec_s<4>::zero()
	{
		static vec_t<4> v(0.0f, 0.0f, 0.0f, 0.0f);
		return v;
	}
	inline const vec_t<4>& vec_s<4>::one()
	{
		static vec_t<4> v(1.0f, 1.0f, 1.0f, 1.0f);
		return v;
	}
}

namespace gml
{
	template<int D>
	inline vec_t<D> vec_t<D>::operator-() const
	{
		vec_t<D> r;
		for (int i = 0; i < D; i++)
		{
			r[i] = -(*this)[i];
		}
		return r;
	}

	template<int D>
	inline float& vec_t<D>::operator[](int index) //hack
	{
		return const_cast<float&>(const_cast<const vec_t<D>*>(this)->operator[](index));
	}

	template<int D>
	inline const float& vec_t<D>::operator[](int index) const
	{
		assert(index >= 0 || index < DIMENSION);
		return *(&x + index);
	}

	template<int D>
	inline vec_t<D>::operator float*()
	{
		return const_cast<float*>(const_cast<const vec_t<D>*>(this)->operator const float*());
	}

	template<int D>
	inline void vec_t<D>::normalize()
	{
		float length2 = length_sqr();
		if (!fequal(length2, 0.0f))
		{
			if (!fequal(length2, 1.0f))
			{
				auto invLength = 1.0f / sqrtf(length2);
				(*this) *= invLength;
			}
		}
		else
		{
			*this = zero();
		}
	}

	template<int D>
	inline vec_t<D> vec_t<D>::normalized() const
	{
		vec_t<D> copy(*this);
		copy.normalize();
		return copy;
	}

	template<int D>
	inline void vec_t<D>::inverse()
	{
		float length2 = length_sqr();
		if (!fequal(length2, 0.0f))
		{
			(*this) *= 1.0f / length2;
		}
		else
		{
			*this = zero();
		}
	}

	template<int D>
	inline vec_t<D> vec_t<D>::inversed() const
	{
		vec_t<D> copy(*this);
		copy.inverse();
		return copy;
	}

	template<int D>
	inline float vec_t<D>::length() const
	{
		return sqrtf(length_sqr());
	}

	template<int D>
	inline float vec_t<D>::length_sqr() const
	{
		float r = 0.0f;
		for (int i = 0; i < D; i++)
		{
			r += (*this)[i] * (*this)[i];
		}
		return r;
	}

	template<int D>
	inline void vec_t<D>::replace(const vec_t<2>& v2)
	{
		static_assert(D == 2 || D == 3 || D == 4, "");
		x = v2.x;
		y = v2.y;
	}

	template<int D>
	inline void vec_t<D>::replace(const vec_t<3>& v3)
	{
		static_assert(D == 3 || D == 4, "");
		x = v3.x;
		y = v3.y;
		z = v3.z;
	}

	constexpr float cross(const vec_t<2>& lhs, const vec_t<2>& rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}

	constexpr vec_t<3> cross(const vec_t<3>& lhs, const vec_t<3>& rhs)
	{
		return vec_t<3>(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
			);
	}

	template<int D>
	float dot(const vec_t<D>& lhs, const vec_t<D>& rhs)
	{
		float r = 0.0f;
		for (int i = 0; i < D; i++)
		{
			r += lhs[i] * rhs[i];
		}
		return r;
	}

	template<int D>
	inline vec_t<D> min_combine(const vec_t<D>& lhs, const vec_t<D>& rhs)
	{
		vec_t<D> r;
		for (int i = 0; i < D; i++)
		{
			r[i] = (lhs[i] < rhs[i]) ? lhs[i] : rhs[i];
		}
		return r;
	}

	template<int D>
	inline vec_t<D> max_combine(const vec_t<D>& lhs, const vec_t<D>& rhs)
	{
		vec_t<D> r;
		for (int i = 0; i < D; i++)
		{
			r[i] = (lhs[i] > rhs[i]) ? lhs[i] : rhs[i];
		}
		return r;
	}
}

