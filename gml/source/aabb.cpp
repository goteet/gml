#include "../include/gmlaabb.h"

namespace gml
{
	aabb::aabb(const vec3& min_bound, const vec3& max_bound)
	{
		set(min_bound, max_bound);
	}

	bool aabb::operator==(const aabb& other) const
	{
		if (this == &other)
		{
			return true;
		}
		else if (is_empty() && other.is_empty())
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

	void aabb::set(const vec3& min_bound, const vec3& max_bound)
	{
		m_min_bound = min_combine(min_bound, max_bound);
		m_max_bound = max_combine(min_bound, max_bound);
		m_center = (m_min_bound + m_max_bound) * 0.5f;
		m_extend = m_center - m_min_bound;
		m_is_empty = false;
	}

	bool aabb::contains(const aabb& other) const
	{
		if (!is_empty() && !other.is_empty())
		{
			return contains(other.min_bound()) && contains(other.max_bound());
		}
		return false;
	}

	it_mode aabb::is_intersect(const aabb& other) const
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

			bool minBoundContains = contains(other.min_bound());
			bool maxBoundContains = contains(other.max_bound());

			if (minBoundContains && maxBoundContains)
			{
				return it_contain;
			}
			else if (minBoundContains || maxBoundContains)
			{
				return it_hit;
			}
			else
			{
				minBoundContains = other.contains(m_min_bound);
				maxBoundContains = other.contains(m_max_bound);

				if (minBoundContains && maxBoundContains)
				{
					return it_inside;
				}
				// Impossible minBoundContains and maxBoundContains.
				else
				{
					return it_none;
				}
			}
		}
		else
		{
			return it_none;
		}
	}

	bool aabb::contains(const vec3& point) const
	{
		if (!is_empty())
		{
			return !(m_min_bound.x > point.x || m_max_bound.x < point.x ||
				m_min_bound.y > point.y || m_max_bound.y < point.y ||
				m_min_bound.z > point.z || m_max_bound.z < point.z);
		}
		return false;
	}

	void aabb::expand(const vec3& point)
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

	void aabb::expand(const aabb& other)
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

	void aabb::clear()
	{
		m_min_bound = vec3::zero();
		m_max_bound = vec3::zero();
		m_center = vec3::zero();
		m_extend = vec3::zero();
		m_is_empty = true;
	}
}