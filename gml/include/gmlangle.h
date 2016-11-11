#pragma once

#include <gmlutility.h>

namespace gml
{
	struct degree;
	struct radian;

	struct degree
	{
	private:
		static constexpr float r2d_factor = static_cast<float>(180.0 / PI_d);

	public:
		float value = 0;

		constexpr degree() = default;

		explicit constexpr degree(float v) : value(v) { }

		constexpr degree(radian r);

		friend constexpr bool operator==(degree l, degree r)
		{
			return l.value == r.value;
		}
		friend constexpr bool operator!=(degree l, degree r)
		{
			return l.value != r.value;
		}
		friend constexpr bool operator<(degree l, degree r)
		{
			return l.value < r.value;
		}
		friend constexpr bool operator<=(degree l, degree r)
		{
			return l.value <= r.value;
		}
		friend constexpr bool operator>(degree l, degree r)
		{
			return l.value > r.value;
		}
		friend constexpr bool operator>=(degree l, degree r)
		{
			return l.value >= r.value;
		}
		friend constexpr degree operator+(degree l, degree r)
		{
			return degree(l.value + r.value);
		}
		friend constexpr degree operator-(degree l, degree r)
		{
			return degree(l.value - r.value);
		}
		friend constexpr degree operator*(degree l, float r)
		{
			return degree(l.value * r);
		}
		friend constexpr degree operator*(float l, degree r)
		{
			return degree(l * r.value);
		}
		constexpr degree operator+() const
		{
			return *this;
		}
		constexpr degree operator-() const
		{
			return degree(-value);
		}
		degree& operator+=(degree r)
		{
			value += r.value;
			return *this;
		}
		degree& operator-=(degree r)
		{
			value -= r.value;
			return *this;
		}
		degree& operator*=(float r)
		{
			value *= r;
			return *this;
		}
	};

	struct radian
	{
	private:
		static constexpr float d2r_factor = static_cast<float>(PI_d / 180.0);

	public:
		float value = 0;

		constexpr radian() = default;

		explicit constexpr radian(float v) : value(v) { }

		constexpr radian(degree d) : value(d.value * d2r_factor) { }

		friend constexpr bool operator==(radian l, radian r)
		{
			return l.value == r.value;
		}
		friend constexpr bool operator!=(radian l, radian r)
		{
			return l.value != r.value;
		}
		friend constexpr bool operator<(radian l, radian r)
		{
			return l.value < r.value;
		}
		friend constexpr bool operator<=(radian l, radian r)
		{
			return l.value <= r.value;
		}
		friend constexpr bool operator>(radian l, radian r)
		{
			return l.value > r.value;
		}
		friend constexpr bool operator>=(radian l, radian r)
		{
			return l.value >= r.value;
		}
		friend constexpr radian operator+(radian l, radian r)
		{
			return radian(l.value + r.value);
		}
		friend constexpr radian operator-(radian l, radian r)
		{
			return radian(l.value - r.value);
		}
		friend constexpr radian operator*(radian l, float r)
		{
			return radian(l.value * r);
		}
		friend constexpr radian operator*(float l, radian r)
		{
			return radian(l * r.value);
		}
		constexpr radian operator+() const
		{
			return *this;
		}
		constexpr radian operator-() const
		{
			return radian(-value);
		}
		radian& operator+=(radian r)
		{
			value += r.value;
			return *this;
		}
		radian& operator-=(radian r)
		{
			value -= r.value;
			return *this;
		}
		radian& operator*=(float r)
		{
			value *= r;
			return *this;
		}
	};

	float cos(const radian&);

	float sin(const radian&);

	// definition of radian is after degree.
	constexpr degree::degree(radian r) : value(r.value * r2d_factor) { }

}
