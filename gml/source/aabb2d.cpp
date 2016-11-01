#include "../include/gmlaabb.h"

namespace gml
{
	aabb2d::aabb2d()
		: m_min_bound(vec3::zero())
		, m_max_bound(vec3::zero())
		, m_center(vec3::zero())
		, m_extend(vec3::zero())
	{

	}

	aabb2d::aabb2d(const vec2& min_bound, const vec2& max_bound)
	{
		set(min_bound, max_bound);
	}

	bool aabb2d::operator==(const aabb2d& other) const
	{
		if (is_empty() && other.is_empty())
		{
			return true;
		}
		else if (!is_empty() && !other.is_empty())
		{
			return (m_min_bound == other.m_min_bound && m_max_bound == other.m_max_bound);
		}
		else
		{
			return false;
		}
	}

	aabb2d& aabb2d::set(const vec2& min_bound, const vec2& max_bound)
	{
		m_min_bound = min_combine(min_bound, max_bound);
		m_max_bound = max_combine(min_bound, max_bound);
		m_center = (m_min_bound + m_max_bound) * 0.5f;
		m_extend = m_center - m_min_bound;
		m_is_empty = false;
		return *this;
	}

	bool aabb2d::is_contain(const aabb2d& other) const
	{
		if (!is_empty() && !other.is_empty())
		{
			return !(m_min_bound.x > other.m_min_bound.x || m_max_bound.x < other.m_max_bound.x ||
				m_min_bound.y > other.m_min_bound.y || m_max_bound.y < other.m_max_bound.y);
		}
		return false;
	}

	int aabb2d::is_intersect(const aabb2d& other) const
	{
		if (is_empty() && other.is_empty())
		{
			return it_same;
		}
		else if (!is_empty() && !other.is_empty())
		{
			if (m_min_bound == other.m_min_bound && m_max_bound == other.m_max_bound)
			{
				return it_same;
			}

			if (m_min_bound.x > other.m_max_bound.x || m_max_bound.x < other.m_min_bound.x ||
				m_min_bound.y > other.m_max_bound.y || m_max_bound.y < other.m_min_bound.y)
			{
				return it_none;
			}

			bool minxless = m_min_bound.x < other.m_min_bound.x;
			bool maxxless = m_max_bound.x < other.m_max_bound.x;
			bool minyless = m_min_bound.y < other.m_min_bound.y;
			bool maxyless = m_max_bound.y < other.m_max_bound.y;

			if (minxless && !maxxless && minyless && !maxyless)
			{
				return it_contain;
			}
			if (!minxless && maxxless && !minyless && maxyless)
			{
				return it_inside;
			}

			return it_intersect;
		}
		else
		{
			return it_none;
		}
	}

	bool aabb2d::is_contain(const vec2& point) const
	{
		if (!is_empty())
		{
			return !(m_min_bound.x > point.x || m_max_bound.x < point.x ||
				m_min_bound.y > point.y || m_max_bound.y < point.y);
		}
		return false;
	}

	void aabb2d::expand(const vec2& point)
	{
		if (is_empty())
		{
			m_min_bound = m_max_bound = point;
			m_is_empty = false;
		}
		else
		{
			m_min_bound = min_combine(m_min_bound, point);
			m_max_bound = max_combine(m_max_bound, point);
		}

		m_center = (m_min_bound + m_max_bound) * 0.5f;
		m_extend = m_center - m_min_bound;
	}

	void aabb2d::expand(const aabb2d& other)
	{
		if (other.is_empty())
		{
			return;
		}

		if (is_empty())
		{
			*this = other;
		}
		else
		{
			m_min_bound = min_combine(m_min_bound, other.m_min_bound);
			m_max_bound = max_combine(m_max_bound, other.m_max_bound);
			m_center = (m_min_bound + m_max_bound) * 0.5f;
			m_extend = m_center - m_min_bound;
		}
	}

	void aabb2d::clear()
	{
		m_min_bound = vec2::zero();
		m_max_bound = vec2::zero();
		m_center = vec2::zero();
		m_extend = vec2::zero();
		m_is_empty = true;
	}
}