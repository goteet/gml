#include "../include/gmlcolor.h"
#include "../include/gmlutility.h"
#include <stdlib.h>
#include <cassert>

namespace gml
{
	const color4 color4::black(0, 0, 0, 1);
	const color4 color4::gray(0.5f, 0.5f, 0.5f, 1);
	const color4 color4::white(1, 1, 1, 1);
	const color4 color4::red(1, 0, 0, 1);
	const color4 color4::green(0, 1, 0, 1);
	const color4 color4::blue(0, 0, 1, 1);
	const color4 color4::yellow(1, 1, 0,1);
	const color4 color4::cyan(0, 1, 1,1);
	const color4 color4::purple(1, 0, 1,1);

	color4 color4::random()
	{
		return (color4(rand() * 1.0f, rand() * 1.0f, rand() * 1.0f, rand() * 1.0f) * (1.0f / RAND_MAX));
	}

	color4::color4()
	{

	}

	color4::color4(float r, float g, float b, float a)
	{
		set(r, g, b, a);
	}
	
	color4::color4(const color3& c, float a)
	{
		this->r = c.r;
		this->g = c.g;
		this->b = c.b;
		this->a = a;
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
		r += value;
		g += value;
		b += value;
		a += value;
		return *this;
	}

	color4& color4::operator*=(float value)
	{
		r *= value;
		g *= value;
		b *= value;
		a *= value;
		return *this;
	}

	color4& color4::operator+=(const color4& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
		return *this;
	}

	color4& color4::operator*=(const color4& rhs)
	{
		r *= rhs.r;
		g *= rhs.g;
		b *= rhs.b;
		a *= rhs.a;
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

	color4& color4::set(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		return *this;
	}

	color4& color4::replace(const color3& c3)
	{
		this->r = c3.r;
		this->g = c3.g;
		this->b = c3.b;
		return *this;
	}

	color4& color4::clamp()
	{
		if (r > 1.0f) r = 1.0f;
		else if (r < 0.0f) r = 0.0f;

		if (g > 1.0f) g = 1.0f;
		else if (g < 0.0f) g = 0.0f;

		if (b > 1.0f) b = 1.0f;
		else if (b < 0.0f) b = 0.0f;

		if (a > 1.0f) a = 1.0f;
		else if (a < 0.0f) a = 0.0f;

		return *this;
	}

	color4 color4::clamped() const
	{
		color4 copy(*this);
		return copy.clamp();
	}

	unsigned int color4::to_rgba()
	{
		unsigned int nr = static_cast<unsigned int>(r * 255);
		unsigned int ng = static_cast<unsigned int>(g * 255);
		unsigned int nb = static_cast<unsigned int>(b * 255);
		unsigned int na = static_cast<unsigned int>(a * 255);

		if (nr > 255) nr = 255;
		if (ng > 255) ng = 255;
		if (nb > 255) nb = 255;
		if (na > 255) na = 255;

		return nr | (ng << 8) | (nb << 16) | (na << 24);
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