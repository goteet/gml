#pragma once
#include <gmlutility.h>
#include <stdlib.h>

namespace gml
{
	class color3;
	class color4;
}

namespace gml
{
	class color3
	{
	public:
		inline static const color3& black()
		{
			static color3 c(0, 0, 0);
			return c;
		}
		inline static const color3& gray()
		{
			static color3 c(0.5f, 0.5f, 0.5f);
			return c;
		}
		inline static const color3& white()
		{
			static color3 c(1, 1, 1);
			return c;
		}
		inline static const color3& red()
		{
			static color3 c(1, 0, 0);
			return c;
		}
		inline static const color3& green()
		{
			static color3 c(0, 1, 0);
			return c;
		}
		inline static const color3& blue()
		{
			static color3 c(0, 0, 1);
			return c;
		}
		inline static const color3& yellow()
		{
			static color3 c(1, 1, 0);
			return c;
		}
		inline static const color3& cyan()
		{
			static color3 c(0, 1, 1);
			return c;
		}
		inline static const color3& purple()
		{
			static color3 c(1, 0, 1);
			return c;
		}
		inline static color3 random()
		{
			return color3(
				(float)rand(),
				(float)rand(),
				(float)rand()) * (1.0f / RAND_MAX);
		}

	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;

	public:
		constexpr color3() = default;

		constexpr color3(float _r, float _g, float _b) : r(_r), g(_g), b(_b) { }

		constexpr explicit color3(const color4& c4);

		constexpr color3(unsigned int _rgb)
			: r((_rgb & 0xFF) / 255.0f)
			, g(((_rgb >> 8) & 0xFF) / 255.0f)
			, b(((_rgb >> 16) & 0xFF) / 255.0f) { }

		friend constexpr bool operator==(const color3& lhs, const color3& rhs)
		{
			return &rhs == &lhs ||
				(fequal(lhs.r, rhs.r) &&
					fequal(lhs.g, rhs.g) &&
					fequal(lhs.b, rhs.b));
		}

		friend constexpr bool operator!=(const color3& lhs, const color3& rhs)
		{
			return !(lhs == rhs);
		}

		friend constexpr color3 operator+(const color3& lhs, float rhs)
		{
			return color3(lhs.r + rhs, lhs.g + rhs, lhs.b + rhs);
		}

		friend constexpr color3 operator+(float lhs, const color3& rhs)
		{
			return rhs + lhs;
		}

		friend constexpr color3 operator*(const color3& lhs, float rhs)
		{
			return color3(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);
		}

		friend constexpr color3 operator*(float lhs, const color3& rhs)
		{
			return rhs * lhs;
		}

		friend constexpr color3 operator+(const color3& lhs, const color3& rhs)
		{
			return color3(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
		}

		friend constexpr color3 operator*(const color3& lhs, const color3& rhs)
		{
			return color3(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
		}

		friend inline color3& operator+=(color3& lhs, float rhs)
		{
			return (lhs = lhs + rhs);
		}

		friend inline color3& operator*=(color3& lhs, float rhs)
		{
			return (lhs = lhs * rhs);
		}

		friend inline color3& operator+=(color3& lhs, const color3& rhs)
		{
			return (lhs = lhs + rhs);
		}

		friend inline color3& operator*=(color3& lhs, const color3& rhs)
		{
			return (lhs = lhs * rhs);
		}

		//hack
		inline float& operator[](int index)
		{
			return const_cast<float&>(const_cast<const color3*>(this)->operator[](index));
		}

		constexpr const float& operator[](int index) const
		{
			return (index < 0 || index >= 3) ? r : *(&r + index);
		}

		inline explicit operator float*()
		{
			return const_cast<float*>(const_cast<const color3*>(this)->operator const float*());
		}

		constexpr explicit operator const float*() const
		{
			return &(r);
		}

		inline void set(float _r, float _g, float _b)
		{
			r = _r;
			g = _g;
			b = _b;
		}

		void set(const color4& c4);

		inline void color3::clamp()
		{
			r = clamp01(r);
			g = clamp01(g);
			b = clamp01(b);
		}

		inline color3 color3::clamped() const
		{
			color3 copy(*this);
			copy.clamp();
			return copy;
		}

		constexpr unsigned int rgba() const
		{
			return (0xFF000000 |
				gml::clamp(static_cast<int>(b * 255), 0, 255) |
				(gml::clamp(static_cast<int>(g * 255), 0, 255) << 8) |
				(gml::clamp(static_cast<int>(r * 255), 0, 255) << 16));
		}

		constexpr unsigned int bgra() const
		{
			return (0xFF000000 |
				gml::clamp(static_cast<int>(r * 255), 0, 255) |
				(gml::clamp(static_cast<int>(g * 255), 0, 255) << 8) |
				(gml::clamp(static_cast<int>(b * 255), 0, 255) << 16));
		}
	};

	constexpr float dot(const color3& lhs, const color3& rhs)
	{
		return lhs.r * rhs.r + lhs.g * rhs.g + lhs.b * rhs.b;
	}
}

namespace gml
{
	class color4
	{
	public:
		inline static const color4& black()
		{
			static color4 c(0, 0, 0, 1);
			return c;
		}
		inline static const color4& gray()
		{
			static color4 c(0.5f, 0.5f, 0.5f, 1);
			return c;
		}
		inline static const color4& white()
		{
			static color4 c(1, 1, 1, 1);
			return c;
		}
		inline static const color4& red()
		{
			static color4 c(1, 0, 0, 1);
			return c;
		}
		inline static const color4& green()
		{
			static color4 c(0, 1, 0, 1);
			return c;
		}
		inline static const color4& blue()
		{
			static color4 c(0, 0, 1, 1);
			return c;
		}
		inline static const color4& yellow()
		{
			static color4 c(1, 1, 0, 1);
			return c;
		}
		inline static const color4& cyan()
		{
			static color4 c(0, 1, 1, 1);
			return c;
		}
		inline static const color4& purple()
		{
			static color4 c(1, 0, 1, 1);
			return c;
		}
		inline static color4 random()
		{
			return color4(
				(float)rand(),
				(float)rand(),
				(float)rand(),
				(float)rand()) * (1.0f / RAND_MAX);
		}

	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

	public:
		constexpr color4() = default;

		constexpr color4(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) { }

		constexpr color4(const color3& c3, float _a) : r(c3.r), g(c3.g), b(c3.b), a(_a) { }

		constexpr color4(unsigned int _rgba)
			: r((_rgba & 0xFF) / 255.0f)
			, g(((_rgba >> 8) & 0xFF) / 255.0f)
			, b(((_rgba >> 16) & 0xFF) / 255.0f)
			, a(((_rgba >> 24) & 0xFF) / 255.0f) { }

		friend constexpr bool operator==(const color4& lhs, const color4& rhs)
		{
			return &rhs == &lhs ||
				(fequal(lhs.r, rhs.r) &&
					fequal(lhs.g, rhs.g) &&
					fequal(lhs.b, rhs.b) &&
					fequal(lhs.a, rhs.a));
		}


		friend constexpr bool operator!=(const color4& lhs, const color4& rhs)
		{
			return !(lhs == rhs);
		}

		friend constexpr color4 operator+(const color4& lhs, float rhs)
		{
			return color4(lhs.r + rhs, lhs.g + rhs, lhs.b + rhs, lhs.a + rhs);
		}

		friend constexpr color4 operator+(float lhs, const color4& rhs)
		{
			return rhs + lhs;
		}

		friend constexpr color4 operator*(const color4& lhs, float rhs)
		{
			return color4(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs, lhs.a * rhs);
		}

		friend constexpr color4 operator*(float lhs, const color4& rhs)
		{
			return rhs * lhs;
		}

		friend constexpr color4 operator+(const color4& lhs, const color4& rhs)
		{
			return color4(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a);
		}

		friend constexpr color4 operator*(const color4& lhs, const color4& rhs)
		{
			return color4(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a);
		}

		friend inline color4& operator+=(color4& lhs, float rhs)
		{
			return (lhs = lhs + rhs);
		}

		friend inline color4& operator*=(color4& lhs, float rhs)
		{
			return (lhs = lhs * rhs);
		}

		friend inline color4& operator+=(color4& lhs, const color4& rhs)
		{
			return (lhs = lhs + rhs);
		}

		friend inline color4& operator*=(color4& lhs, const color4& rhs)
		{
			return (lhs = lhs * rhs);
		}

		//hack
		inline float& operator[](int index)
		{
			return const_cast<float&>(const_cast<const color4*>(this)->operator[](index));
		}

		constexpr const float& operator[](int index) const
		{
			return (index < 0 || index >= 4) ? r : *(&r + index);
		}

		inline explicit operator float*()
		{
			return const_cast<float*>(const_cast<const color4*>(this)->operator const float*());
		}

		constexpr explicit operator const float*() const
		{
			return &(r);
		}

		inline void set(float _r, float _g, float _b, float _a)
		{
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}

		inline void replace(const color3& c3)
		{
			r = c3.r;
			g = c3.g;
			b = c3.b;
		}

		inline void clamp()
		{
			r = clamp01(r);
			g = clamp01(g);
			b = clamp01(b);
			a = clamp01(a);
		}

		inline color4 clamped() const
		{
			color4 copy(*this);
			copy.clamp();
			return copy;
		}

		constexpr unsigned int rgba() const
		{
			return (gml::clamp(static_cast<int>(b * 255), 0, 255) |
				(gml::clamp(static_cast<int>(g * 255), 0, 255) << 8) |
				(gml::clamp(static_cast<int>(r * 255), 0, 255) << 16) |
				(gml::clamp(static_cast<int>(a * 255), 0, 255) << 24));
		}

		constexpr unsigned int bgra() const
		{
			return (gml::clamp(static_cast<int>(r * 255), 0, 255) |
				(gml::clamp(static_cast<int>(g * 255), 0, 255) << 8) |
				(gml::clamp(static_cast<int>(b * 255), 0, 255) << 16) |
				(gml::clamp(static_cast<int>(a * 255), 0, 255) << 24));
		}
	};

	constexpr float dot(const color4& lhs, const color4& rhs)
	{
		return lhs.r * rhs.r + lhs.g * rhs.g + lhs.b * rhs.b + lhs.a * rhs.a;
	}
}

namespace gml
{
	constexpr color3::color3(const color4& c4) : r(c4.r), g(c4.g), b(c4.b) { }

	inline void color3::set(const color4& c4)
	{
		set(c4.r, c4.g, c4.b);
	}
}
namespace gml
{
	struct _R { constexpr static int SwizzleIndex = 0; };
	struct _G { constexpr static int SwizzleIndex = 1; };
	struct _B { constexpr static int SwizzleIndex = 2; };
	struct _A { constexpr static int SwizzleIndex = 3; };

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB>
	constexpr color3 swizzle(const color3& c3)
	{
		return color3(c3[SwizzleR::SwizzleIndex], c3[SwizzleG::SwizzleIndex], c3[SwizzleB::SwizzleIndex]);
	}

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB>
	constexpr color3 swizzle(const color4& c4)
	{
		return color3(c4[SwizzleR::SwizzleIndex], c4[SwizzleG::SwizzleIndex], c4[SwizzleB::SwizzleIndex]);
	}

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB, typename SwizzleA>
	constexpr color4 swizzle(const color3& c3)
	{
		return color4(c3[SwizzleR::SwizzleIndex], c3[SwizzleG::SwizzleIndex], c3[SwizzleB::SwizzleIndex], c3[SwizzleA::SwizzleIndex]);
	}

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB, typename SwizzleA>
	constexpr color4 swizzle(const color4& c4)
	{
		return color4(c4[SwizzleR::SwizzleIndex], c4[SwizzleG::SwizzleIndex], c4[SwizzleB::SwizzleIndex], c4[SwizzleA::SwizzleIndex]);
	}
}
