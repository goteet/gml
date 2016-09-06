#pragma once
#include <gmlvector.h>

namespace gml
{
	class ray
	{
	public:
		inline const vec3& origin() const { return m_origin; }

		inline const vec3& direction() const { return m_dir; }

		ray& set_origin(float x, float y, float z);

		ray& set_origin(const vec3& origin);

		ray& set_dir(float x, float y, float z);

		ray& set_dir(const vec3& dir);

		vec3 get_pos_by_len(float length) const;

	private:
		vec3 m_origin;
		vec3 m_dir;
	};
}
