#pragma once

#include <gmlvector.h>

namespace gml
{
	enum intersect_mode
	{
		it_none,
		it_contain,
		it_inside,
		it_intersect,	
		it_same,
	};

	class aabb2d
	{
	public:
		aabb2d();

		aabb2d(const vec2& min_bound, const vec2& max_bound);

		bool operator==(const aabb2d& other) const;

		aabb2d& set(const vec2& min_bound, const vec2& max_bound);

		inline const vec2& center() const { return m_center; }
					 
		inline const vec2& min_bound() const { return m_min_bound; }
					 
		inline const vec2& max_bound() const { return m_max_bound; }
					 
		inline const vec2& extend() const { return m_extend; }

		inline bool is_empty() const { return m_is_empty; }

		bool is_contain(const aabb2d& other) const;

		int is_intersect(const aabb2d& other) const;

		bool is_contain(const vec2& point) const;

		void expand(const vec2& point);

		void expand(const aabb2d& other);

		void clear();

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
		aabb();

		aabb(const vec3& min_bound, const vec3& max_bound);

		bool operator==(const aabb& other) const;

		aabb& set(const vec3& min_bound, const vec3& max_bound);

		inline const vec3& center() const { return m_center; }

		inline const vec3& min_bound() const { return m_min_bound; }

		inline const vec3& max_bound() const { return m_max_bound; }

		inline const vec3& extend() const { return m_extend; }

		inline bool is_empty() const { return m_is_empty; }

		bool is_contain(const aabb& other) const;

		int is_intersect(const aabb& other) const;

		bool is_contain(const vec3& point) const;

		void expand(const vec3& point);

		void expand(const aabb& other);

		void clear();

	private:
		bool m_is_empty = true;
		vec3 m_min_bound;
		vec3 m_max_bound;
		vec3 m_center;
		vec3 m_extend;
	};
}