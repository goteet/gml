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

	color3::color3()
	{

	}

	color3::color3(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	color3::color3(const color4& c4)
	{
		this->r = c4.r;
		this->g = c4.g;
		this->b = c4.b;
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
		r += value;
		g += value;
		b += value;
		return *this;
	}

	color3& color3::operator*=(float value)
	{
		r *= value;
		g *= value;
		b *= value;
		return *this;
	}

	color3& color3::operator+=(const color3& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		return *this;
	}

	color3& color3::operator*=(const color3& rhs)
	{
		r *= rhs.r;
		g *= rhs.g;
		b *= rhs.b;
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

	color3& color3::set(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		return *this;
	}

	color3& color3::set(const color4& c4)
	{
		set(c4.r, c4.g, c4.b);
		return *this;
	}

	color3& color3::clamp()
	{
		if (r > 1.0f) r = 1.0f;
		else if (r < 0.0f) r = 0.0f;

		if (g > 1.0f) g = 1.0f;
		else if (g < 0.0f) g = 0.0f;

		if (b > 1.0f) b = 1.0f;
		else if (b < 0.0f) b = 0.0f;

		return *this;
	}

	color3 color3::clamped() const
	{
		color3 copy(*this);
		return copy.clamp();
	}

	unsigned int color3::to_rgb()
	{
		unsigned int nr = static_cast<unsigned int>(r * 255);
		unsigned int ng = static_cast<unsigned int>(g * 255);
		unsigned int nb = static_cast<unsigned int>(b * 255);

		if (nr > 255) nr = 255;
		if (ng > 255) ng = 255;
		if (nb > 255) nb = 255;

		return nr | (ng << 8) | (nb << 16);
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