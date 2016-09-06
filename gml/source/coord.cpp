#include "../include/gmlrect.h"

namespace gml
{
	coord::coord() { }

	coord::coord(int x, int y)
	{
		set(x, y);
	}

	coord& coord::set(int x, int y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	coord& coord::move(int offsetx, int offsety)
	{
		set(x + offsetx, y + offsety);
		return *this;
	}
}