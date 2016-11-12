#include "../include/gmlcolor.h"
#include "../include/gmlutility.h"
#include <stdlib.h>
#include <cassert>

namespace gml
{
	const color3& color3::black()
	{
		static color3 c(0, 0, 0);
		return c;
	}
	const color3& color3::gray()
	{
		static color3 c(0.5f, 0.5f, 0.5f);
		return c;
	}
	const color3& color3::white()
	{
		static color3 c(1, 1, 1);
		return c;
	}
	const color3& color3::red()
	{
		static color3 c(1, 0, 0);
		return c;
	}
	const color3& color3::green()
	{
		static color3 c(0, 1, 0);
		return c;
	}
	const color3& color3::blue()
	{
		static color3 c(0, 0, 1);
		return c;
	}
	const color3& color3::yellow()
	{
		static color3 c(1, 1, 0);
		return c;
	}
	const color3& color3::cyan()
	{
		static color3 c(0, 1, 1);
		return c;
	}
	const color3& color3::purple()
	{
		static color3 c(1, 0, 1);
		return c;
	}

	color3 color3::random()
	{
		return color3(rand() * 1.0f, rand() * 1.0f, rand() * 1.0f) * (1.0f / RAND_MAX);
	}

	color3::color3(float r, float g, float b)
	{
		set(r, g, b);
	}

	color3::color3(const color4& c4)
	{
		set(c4.r, c4.g, c4.b);
	}

	color3::color3(unsigned int _rgb)
	{
		r = (_rgb & 0xFF) / 255.0f;
		g = ((_rgb >> 8) & 0xFF) / 255.0f;
		b = ((_rgb >> 16) & 0xFF) / 255.0f;
	}

	bool color3::operator==(const color3& rhs) const
	{
		if (&rhs == this)
			return true;

		return fequal(r, rhs.r) &&
			fequal(g, rhs.g) &&
			fequal(b, rhs.b);
	}

	bool color3::operator!=(const color3& rhs) const
	{
		return !(*this == rhs);
	}

	color3 color3::operator+(float value) const
	{
		color3 copy(*this);
		copy += value;
		return copy;
	}

	color3 color3::operator*(float value) const
	{
		color3 copy(*this);
		copy *= value;
		return copy;
	}

	color3 color3::operator+(const color3& rhs) const
	{
		return color3(r + rhs.r, g + rhs.g, b + rhs.b);
	}

	color3 color3::operator*(const color3& rhs) const
	{
		return color3(r * rhs.r, g * rhs.g, b * rhs.b);
	}
	color3& color3::operator+=(float value)
	{
		set(r + value, g + value, b + value);
		return *this;
	}

	color3& color3::operator*=(float value)
	{
		set(r * value, g * value, b * value);
		return *this;
	}

	color3& color3::operator+=(const color3& rhs)
	{
		set(r + rhs.r, g + rhs.g, b + rhs.b);
		return *this;
	}

	color3& color3::operator*=(const color3& rhs)
	{
		set(r * rhs.r, g * rhs.g, b * rhs.b);
		return *this;
	}

	float& color3::operator[](int index)
	{
		return const_cast<float&>(const_cast<const color3*>(this)->operator[](index));
	}

	const float& color3::operator[](int index) const
	{
		assert(index >= 0 && index < 3);
		return *(&r + index);
	}

	color3::operator float*()
	{
		return &(this->r);
	}

	void color3::set(float r, float g, float b)
	{
		this->r = clamp01(r);
		this->g = clamp01(g);
		this->b = clamp01(b);
	}

	void color3::set(const color4& c4)
	{
		set(c4.r, c4.g, c4.b);
	}

	unsigned int color3::rgba()
	{
		int nr = static_cast<int>(r * 255);
		int ng = static_cast<int>(g * 255);
		int nb = static_cast<int>(b * 255);
		return (0xFF000000 | nb | (ng << 8) | (nr << 16));
	}

	unsigned int color3::bgra()
	{
		int nr = static_cast<int>(r * 255);
		int ng = static_cast<int>(g * 255);
		int nb = static_cast<int>(b * 255);
		return (0xFF000000 | nr | (ng << 8) | (nb << 16));
	}

	color3 operator+(float value, const color3& rhs)
	{
		return rhs + value;
	}

	color3 operator*(float value, const color3& rhs)
	{
		return rhs * value;
	}

	float dot(const color3& lhs, const color3& rhs)
	{
		return lhs.r * rhs.r + lhs.g * rhs.g + lhs.b * rhs.b;
	}
}