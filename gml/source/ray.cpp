#include "../include/gmlray.h"

namespace gml
{
	void ray::set_origin(float x, float y, float z)
	{
		m_origin.set(x, y, z);
	}

	void ray::set_origin(const vec3& origin)
	{
		m_origin = origin;
	}

	void ray::set_dir(float x, float y, float z)
	{
		m_dir.set(x, y, z);
	}


	void ray::set_dir(const vec3& dir)
	{
		m_dir = dir.normalized();
	}

	vec3 ray::get_pos_by_len(float length) const
	{
		return m_origin + m_dir * length;
	}
}