#pragma once

#include <gmlvector.h>

namespace gml
{
	class aabb
	{
	public:
		bool operator==(const aabb& other);

		inline const vec3& center() const { return m_center; }

		inline const vec3& min_bound() const { return m_min_bound; }

		inline const vec3& max_bound() const { return m_max_bound; }

		inline const vec3& extend() const { return m_extend; }

		inline bool is_empty() const { return m_is_empty; }

		bool is_contain(const aabb& other) const;

		bool is_contain(const vec3& point) const;

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