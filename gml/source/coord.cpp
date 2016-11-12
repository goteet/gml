#include "../include/gmlrect.h"

namespace gml
{
	coord::coord(int x, int y)
	{
		set(x, y);
	}

	void coord::set(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void coord::move(int offsetx, int offsety)
	{
		set(x + offsetx, y + offsety);
	}

	bool coord::operator==(const coord& other) const
	{
		if (this == &other)
		{
			return true;
		}
		return (x == other.x) && (y == other.y);
	}
}