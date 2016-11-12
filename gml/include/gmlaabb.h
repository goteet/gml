#pragma once

#include <gmlvector.h>
#include <gmlutility.h>
namespace gml
{
	class aabb2d
	{
	public:
		aabb2d() = default;

		aabb2d(const vec2& min_bound, const vec2& max_bound);

		bool operator==(const aabb2d& other) const;

		void set(const vec2& min_bound, const vec2& max_bound);

		inline const vec2& center() const { return m_center; }
					 
		inline const vec2& min_bound() const { return m_min_bound; }
					 
		inline const vec2& max_bound() const { return m_max_bound; }
					 
		inline const vec2& extend() const { return m_extend; }

		inline bool is_empty() const { return m_is_empty; }

		bool contains(const aabb2d& other) const;

		it_mode is_intersect(const aabb2d& other) const;

		bool contains(const vec2& point) const;

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
		aabb() = default;

		aabb(const vec3& min_bound, const vec3& max_bound);

		bool operator==(const aabb& other) const;

		void set(const vec3& min_bound, const vec3& max_bound);

		inline const vec3& center() const { return m_center; }

		inline const vec3& min_bound() const { return m_min_bound; }

		inline const vec3& max_bound() const { return m_max_bound; }

		inline const vec3& extend() const { return m_extend; }

		inline bool is_empty() const { return m_is_empty; }

		bool contains(const aabb& other) const;

		it_mode is_intersect(const aabb& other) const;

		bool contains(const vec3& point) const;

		void expand(const vec3& point);

		void expand(const aabb& other);

		void clear();

	private:
		bool m_is_empty = true;
		vec3 m_min_bound = vec3::zero();
		vec3 m_max_bound = vec3::zero();
		vec3 m_center = vec3::zero();
		vec3 m_extend = vec3::zero();
	};
}