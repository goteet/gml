#include "../include/gmlaabb.h"

namespace gml
{
	bool aabb::operator==(const aabb& other)
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

	bool aabb::is_contain(const aabb& other) const
	{
		if (!is_empty() && !other.is_empty())
		{

			return !(m_min_bound.x > other.m_min_bound.x || m_max_bound.x < other.m_max_bound.x ||
				m_min_bound.y > other.m_min_bound.y || m_max_bound.y < other.m_max_bound.y ||
				m_min_bound.z > other.m_min_bound.z || m_max_bound.z < other.m_max_bound.z);
		}
		return false;

	}

	bool aabb::is_contain(const gml::vec3& point) const
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
			m_is_empty = false;
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
		m_min_bound = vec3::zero;
		m_max_bound = vec3::zero;
		m_center = vec3::zero;
		m_extend = vec3::zero;
		m_is_empty = true;
	}
}