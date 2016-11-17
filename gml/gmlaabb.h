#pragma once
#include <gmlutility.h>
#include <gmlvector.h>

namespace gml
{
	class aabb2d
	{
	public:
		constexpr aabb2d();

		aabb2d(const vec2& min_bound, const vec2& max_bound);

		friend bool operator==(const aabb2d& lhs, const aabb2d& rhs);

		friend inline bool operator!=(const aabb2d& lhs, const aabb2d& rhs) { return !(lhs == rhs); }

		void set(const vec2& min_bound, const vec2& max_bound);

		constexpr const vec2& center() const { return m_center; }

		constexpr const vec2& min_bound() const { return m_min_bound; }

		constexpr const vec2& max_bound() const { return m_max_bound; }

		constexpr const vec2& extend() const { return m_extend; }

		constexpr bool is_empty() const { return m_is_empty; }

		it_mode is_intersect(const aabb2d& other) const;

		bool contains(const aabb2d& other) const;

		bool contains(const vec2& point) const;

		void expand(const vec2& point);

		void expand(const aabb2d& other);

		void move(const vec2& offset);

		void move_to(const vec2& point);

		void clear();

	private:
		bool m_is_empty;
		vec2 m_min_bound;
		vec2 m_max_bound;
		vec2 m_center;
		vec2 m_extend;
	};

	class aabb
	{
	public:
		constexpr aabb();

		aabb(const vec3& min_bound, const vec3& max_bound);

		constexpr const vec3& center() const { return m_center; }

		constexpr const vec3& min_bound() const { return m_min_bound; }

		constexpr const vec3& max_bound() const { return m_max_bound; }

		constexpr const vec3& extend() const { return m_extend; }

		constexpr bool is_empty() const { return m_is_empty; }

		friend bool operator==(const aabb& lhs, const aabb& rhs);

		friend inline bool operator!=(const aabb& lhs, const aabb& rhs) { return !(lhs == rhs); }

		void set(const vec3& min_bound, const vec3& max_bound);

		it_mode is_intersect(const aabb& other) const;

		bool contains(const aabb& other) const;

		bool contains(const vec3& point) const;

		void expand(const vec3& point);

		void expand(const aabb& other);

		void move(const vec3& point);

		void move_to(const vec3& point);

		void clear();

	private:
		bool m_is_empty;
		vec3 m_min_bound;
		vec3 m_max_bound;
		vec3 m_center;
		vec3 m_extend;
	};
}

namespace gml
{
	constexpr aabb2d::aabb2d()
		: m_is_empty(true)
		, m_min_bound(0, 0)
		, m_max_bound(0, 0)
		, m_center(0, 0)
		, m_extend(0, 0) { }

	inline aabb2d::aabb2d(const vec2& min_bound, const vec2& max_bound)
	{
		set(min_bound, max_bound);
	}

	inline bool operator==(const aabb2d& lhs, const aabb2d& rhs)
	{
		if (&lhs != &rhs)
		{
			if (lhs.is_empty() && rhs.is_empty())
			{
				return true;
			}
			else if (!lhs.is_empty() && !rhs.is_empty())
			{
				return lhs.m_min_bound == rhs.m_min_bound && lhs.m_max_bound == rhs.m_max_bound;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	inline void aabb2d::set(const vec2& min_bound, const vec2& max_bound)
	{
		m_min_bound = min_combine(min_bound, max_bound);
		m_max_bound = max_combine(min_bound, max_bound);
		m_center = (m_min_bound + m_max_bound) * 0.5f;
		m_extend = m_center - m_min_bound;

		m_is_empty = (fequal(m_min_bound.x, m_max_bound.x) ||
			fequal(m_min_bound.y, m_max_bound.y));
	}

	inline it_mode aabb2d::is_intersect(const aabb2d& other) const
	{
		if (*this == other)
		{
			return it_same;
		}
		else if (!is_empty() && !other.is_empty())
		{
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

	inline bool aabb2d::contains(const aabb2d& other) const
	{
		if (is_empty() || other.is_empty())
		{
			return false;
		}
		else
		{
			return !(m_min_bound.x > other.m_min_bound.x ||
				m_max_bound.x < other.m_max_bound.x ||
				m_min_bound.y > other.m_min_bound.y ||
				m_max_bound.y < other.m_max_bound.y);
		}
	}

	inline bool aabb2d::contains(const vec2& point) const
	{
		if (is_empty())
		{
			return false;
		}
		else
		{
			return !(m_min_bound.x > point.x ||
				m_max_bound.x < point.x ||
				m_min_bound.y > point.y ||
				m_max_bound.y < point.y);
		}
	}

	inline void aabb2d::expand(const vec2& point)
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

	inline void aabb2d::expand(const aabb2d& other)
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

	inline void aabb2d::clear()
	{
		m_min_bound = vec2::zero();
		m_max_bound = vec2::zero();
		m_center = vec2::zero();
		m_extend = vec2::zero();
		m_is_empty = true;
	}

	inline void aabb2d::move(const vec2& offset)
	{
		m_min_bound += offset;
		m_max_bound += offset;
		m_center += offset;
	}

	inline void aabb2d::move_to(const vec2& point)
	{
		auto offset = point - m_center;
		m_min_bound += offset;
		m_max_bound += offset;
		m_center = point;
	}

	constexpr aabb::aabb() : m_is_empty(true)
		, m_min_bound(0, 0, 0)
		, m_max_bound(0, 0, 0)
		, m_center(0, 0, 0)
		, m_extend(0, 0, 0) { }

	inline aabb::aabb(const vec3& min_bound, const vec3& max_bound)
	{
		set(min_bound, max_bound);
	}

	inline bool operator==(const aabb& lhs, const aabb& rhs)
	{
		if (&lhs != &rhs)
		{
			if (lhs.is_empty() && rhs.is_empty())
			{
				return true;
			}
			else
			{
				if (!lhs.is_empty() && !rhs.is_empty())
				{
					return lhs.m_min_bound == rhs.m_min_bound && lhs.m_max_bound == rhs.m_max_bound;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return true;
		}
	}

	inline void aabb::set(const vec3& min_bound, const vec3& max_bound)
	{
		m_min_bound = min_combine(min_bound, max_bound);
		m_max_bound = max_combine(min_bound, max_bound);
		m_center = (m_min_bound + m_max_bound) * 0.5f;
		m_extend = m_center - m_min_bound;
		m_is_empty = (fequal(m_min_bound.x, m_max_bound.x) ||
			fequal(m_min_bound.y, m_max_bound.y) ||
			fequal(m_min_bound.z, m_max_bound.z));
	}

	inline it_mode aabb::is_intersect(const aabb& other) const
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

	inline bool aabb::contains(const aabb& other) const
	{
		if (!is_empty() && !other.is_empty())
		{
			return !(m_min_bound.x > other.m_min_bound.x || m_max_bound.x < other.m_max_bound.x ||
				m_min_bound.y > other.m_min_bound.y || m_max_bound.y < other.m_max_bound.y ||
				m_min_bound.z > other.m_min_bound.z || m_max_bound.z < other.m_max_bound.z);
		}
		else
		{
			return false;
		}
	}

	inline bool aabb::contains(const vec3& point) const
	{
		if (!is_empty())
		{
			return !(m_min_bound.x > point.x || m_max_bound.x < point.x ||
				m_min_bound.y > point.y || m_max_bound.y < point.y ||
				m_min_bound.z > point.z || m_max_bound.z < point.z);
		}
		else
		{
			return false;
		}
	}

	inline void aabb::expand(const vec3& point)
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

	inline void aabb::expand(const aabb& other)
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

	inline void aabb::move(const vec3& offset)
	{
		m_min_bound += offset;
		m_max_bound += offset;
		m_center += offset;
	}

	inline void aabb::move_to(const vec3& point)
	{
		auto offset = point - m_center;
		m_min_bound += offset;
		m_max_bound += offset;
		m_center = point;
	}

	inline void aabb::clear()
	{
		m_min_bound = vec3::zero();
		m_max_bound = vec3::zero();
		m_center = vec3::zero();
		m_extend = vec3::zero();
		m_is_empty = true;
	}
}