#include "../include/gmlcolor.h"
#include "../include/gmlutility.h"
#include <stdlib.h>
#include <cassert>

namespace gml
{
	const color4& color4::black()
	{
		static color4 c(0, 0, 0, 1);
		return c;
	}
	const color4& color4::gray()
	{
		static color4 c(0.5f, 0.5f, 0.5f, 1);
		return c;
	}
	const color4& color4::white()
	{
		static color4 c(1, 1, 1, 1);
		return c;
	}
	const color4& color4::red()
	{
		static color4 c(1, 0, 0, 1);
		return c;
	}
	const color4& color4::green()
	{
		static color4 c(0, 1, 0, 1);
		return c;
	}
	const color4& color4::blue()
	{
		static color4 c(0, 0, 1, 1);
		return c;
	}
	const color4& color4::yellow()
	{
		static color4 c(1, 1, 0, 1);
		return c;
	}
	const color4& color4::cyan()
	{
		static color4 c(0, 1, 1, 1);
		return c;
	}
	const color4& color4::purple()
	{
		static color4 c(1, 0, 1, 1);
		return c;
	}

	color4 color4::random()
	{
		return (color4(rand() * 1.0f, rand() * 1.0f, rand() * 1.0f, rand() * 1.0f) * (1.0f / RAND_MAX));
	}

	color4::color4(float r, float g, float b, float a)
	{
		set(r, g, b, a);
	}

	color4::color4(const color3& c, float a)
	{
		set(c.r, c.g, c.b, a);
	}

	color4::color4(unsigned int _rgba)
	{
		r = (_rgba & 0xFF) / 255.0f;
		g = ((_rgba >> 8) & 0xFF) / 255.0f;
		b = ((_rgba >> 16) & 0xFF) / 255.0f;
		a = ((_rgba >> 24) & 0xFF) / 255.0f;
	}

	bool color4::operator==(const color4& rhs) const
	{
		if (&rhs == this)
			return true;

		return fequal(r, rhs.r) &&
			fequal(g, rhs.g) &&
			fequal(b, rhs.b) &&
			fequal(a, rhs.a);
	}

	bool color4::operator!=(const color4& rhs) const
	{
		return !(*this == rhs);
	}

	color4 color4::operator+(float value) const
	{
		color4 copy(*this);
		copy += value;
		return copy;
	}

	color4 color4::operator*(float value) const
	{
		color4 copy(*this);
		copy *= value;
		return copy;
	}

	color4 color4::operator+(const color4& rhs) const
	{
		return color4(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
	}

	color4 color4::operator*(const color4& rhs) const
	{
		return color4(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
	}
	color4& color4::operator+=(float value)
	{
		set(r + value, g + value, b + value, a + value);
		return *this;
	}

	color4& color4::operator*=(float value)
	{
		set(r * value, g * value, b * value, a * value);
		return *this;
	}

	color4& color4::operator+=(const color4& rhs)
	{
		set(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
		return *this;
	}

	color4& color4::operator*=(const color4& rhs)
	{
		set(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
		return *this;
	}

	//hack
	float& color4::operator[](int index)
	{
		return const_cast<float&>(const_cast<const color4*>(this)->operator[](index));
	}

	const float& color4::operator[](int index) const
	{
		assert(index >= 0 && index < 4);
		return *(&r + index);
	}

	color4::operator float*()
	{
		return &(this->r);
	}

	void color4::set(float r, float g, float b, float a)
	{
		this->r = clamp01(r);
		this->g = clamp01(g);
		this->b = clamp01(b);
		this->a = clamp01(a);
	}

	void color4::replace(const color3& c3)
	{
		set(c3.r, c3.g, c3.b, a);
	}

	unsigned int color4::rgba()
	{
		int nr = static_cast<int>(r * 255);
		int ng = static_cast<int>(g * 255);
		int nb = static_cast<int>(b * 255);
		int na = static_cast<int>(a * 255);
		return (nb | (ng << 8) | (nr << 16) | (na << 24));
	}

	unsigned int color4::bgra()
	{
		int nr = static_cast<int>(r * 255);
		int ng = static_cast<int>(g * 255);
		int nb = static_cast<int>(b * 255);
		int na = static_cast<int>(a * 255);
		return (nr | (ng << 8) | (nb << 16) | (na << 24));
	}

	color4 operator+(float value, const color4& rhs)
	{
		return rhs + value;
	}

	color4 operator*(float value, const color4& rhs)
	{
		return rhs * value;
	}

	float dot(const color4& lhs, const color4& rhs)
	{
		return lhs.r * rhs.r + lhs.g * rhs.g + lhs.b * rhs.b + lhs.a * rhs.a;
	}
}