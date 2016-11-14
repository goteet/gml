#pragma once
#include <gmlvector.h>

namespace gml
{
	class ray
	{
	public:
		constexpr const vec3& origin() const
		{
			return m_origin;
		}

		constexpr const vec3& direction() const
		{
			return m_dir;
		}

		inline void set_origin(float x, float y, float z)
		{
			m_origin.set(x, y, z);
		}

		inline void set_origin(const vec3& origin)
		{
			m_origin = origin;
		}

		inline void set_dir(float x, float y, float z)
		{
			m_dir.set(x, y, z);
			m_dir.normalize();
		}

		inline void set_dir(const vec3& dir)
		{
			m_dir = dir.normalized();
		}

		constexpr vec3 get_offset(float length) const
		{
			return m_origin + m_dir * length;
		}

	private:
		vec3 m_origin;
		vec3 m_dir;
	};
}
