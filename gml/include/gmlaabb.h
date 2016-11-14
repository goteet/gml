#pragma once

#include <gmlvector.h>
#include <gmlutility.h>
namespace gml
{
	class aabb2d
	{
	public:
		aabb2d() = default;

		inline aabb2d(const vec2& min_bound, const vec2& max_bound) { set(min_bound, max_bound); }

		inline bool operator==(const aabb2d& other) const
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

		inline void set(const vec2& min_bound, const vec2& max_bound)
		{
			m_min_bound = min_combine(min_bound, max_bound);
			m_max_bound = max_combine(min_bound, max_bound);
			m_center = (m_min_bound + m_max_bound) * 0.5f;
			m_extend = m_center - m_min_bound;
			m_is_empty = false;
		}

		inline const vec2& center() const { return m_center; }

		inline const vec2& min_bound() const { return m_min_bound; }

		inline const vec2& max_bound() const { return m_max_bound; }

		inline const vec2& extend() const { return m_extend; }

		inline bool is_empty() const { return m_is_empty; }

		inline bool contains(const aabb2d& other) const
		{
			if (!is_empty() && !other.is_empty())
			{
				return !(m_min_bound.x > other.m_min_bound.x || m_max_bound.x < other.m_max_bound.x ||
					m_min_bound.y > other.m_min_bound.y || m_max_bound.y < other.m_max_bound.y);
			}
			return false;
		}

		inline it_mode is_intersect(const aabb2d& other) const
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

				return it_hit;
			}
			else
			{
				return it_none;
			}
		}

		inline bool contains(const vec2& point) const
		{
			if (!is_empty())
			{
				return !(m_min_bound.x > point.x || m_max_bound.x < point.x ||
					m_min_bound.y > point.y || m_max_bound.y < point.y);
			}
			return false;
		}

		inline void expand(const vec2& point)
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

		inline void expand(const aabb2d& other)
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

		inline void clear()
		{
			m_min_bound = vec2::zero();
			m_max_bound = vec2::zero();
			m_center = vec2::zero();
			m_extend = vec2::zero();
			m_is_empty = true;
		}

	private:
		bool m_is_empty = true;
		vec2 m_min_bound = vec2::zero();
		vec2 m_max_bound = vec2::zero();
		vec2 m_center = vec2::zero();
		vec2 m_extend = vec2::zero();
	};

	class aabb
	{
	public:
		aabb() = default;

		aabb(const vec3& min_bound, const vec3& max_bound)
		{
			set(min_bound, max_bound);
		}

		bool operator==(const aabb& other) const
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

		void set(const vec3& min_bound, const vec3& max_bound)
		{
			m_min_bound = min_combine(min_bound, max_bound);
			m_max_bound = max_combine(min_bound, max_bound);
			m_center = (m_min_bound + m_max_bound) * 0.5f;
			m_extend = m_center - m_min_bound;
			m_is_empty = false;
		}

		inline const vec3& center() const { return m_center; }

		inline const vec3& min_bound() const { return m_min_bound; }

		inline const vec3& max_bound() const { return m_max_bound; }

		inline const vec3& extend() const { return m_extend; }

		inline bool is_empty() const { return m_is_empty; }

		bool contains(const aabb& other) const
		{
			if (!is_empty() && !other.is_empty())
			{

				return !(m_min_bound.x > other.m_min_bound.x || m_max_bound.x < other.m_max_bound.x ||
					m_min_bound.y > other.m_min_bound.y || m_max_bound.y < other.m_max_bound.y ||
					m_min_bound.z > other.m_min_bound.z || m_max_bound.z < other.m_max_bound.z);
			}
			return false;

		}

		it_mode is_intersect(const aabb& other) const
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
					m_min_bound.y > other.m_max_bound.y || m_max_bound.y < other.m_min_bound.y ||
					m_min_bound.z > other.m_max_bound.z || m_max_bound.z < other.m_min_bound.z)
				{
					return it_none;
				}

				bool minxless = m_min_bound.x < other.m_min_bound.x;
				bool maxxless = m_max_bound.x < other.m_max_bound.x;
				bool minyless = m_min_bound.y < other.m_min_bound.y;
				bool maxyless = m_max_bound.y < other.m_max_bound.y;
				bool minzless = m_min_bound.z < other.m_min_bound.z;
				bool maxzless = m_max_bound.z < other.m_max_bound.z;

				if (minxless && !maxxless && minyless && !maxyless && minzless && !maxzless)
				{
					return it_contain;
				}
				if (!minxless && maxxless && !minyless && maxyless && !minzless && maxzless)
				{
					return it_inside;
				}

				return it_hit;
			}
			else
			{
				return it_none;
			}
		}

		bool contains(const vec3& point) const
		{
			if (!is_empty())
			{
				return !(m_min_bound.x > point.x || m_max_bound.x < point.x ||
					m_min_bound.y > point.y || m_max_bound.y < point.y ||
					m_min_bound.z > point.z || m_max_bound.z < point.z);
			}
			return false;
		}

		void expand(const vec3& point)
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

		void expand(const aabb& other)
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

		void clear()
		{
			m_min_bound = vec3::zero();
			m_max_bound = vec3::zero();
			m_center = vec3::zero();
			m_extend = vec3::zero();
			m_is_empty = true;
		}

	private:
		bool m_is_empty = true;
		vec3 m_min_bound = vec3::zero();
		vec3 m_max_bound = vec3::zero();
		vec3 m_center = vec3::zero();
		vec3 m_extend = vec3::zero();
	};
}