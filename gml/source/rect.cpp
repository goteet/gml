#include "../include/gmlrect.h"

namespace gml
{
	int rect::left() const
	{
		return m_pos.x;
	}

	int rect::right() const
	{
		return left() + width();
	}

	int rect::top() const
	{
		return m_pos.y;
	}

	int rect::bottom() const
	{
		return top() + height();
	}

	int rect::width() const
	{
		return m_size.x;
	}

	int rect::height() const
	{
		return m_size.y;
	}

	coord rect::center() const
	{
		return coord((left() + right()) / 2, (top() + bottom()) / 2);
	}

	coord rect::position() const
	{
		return m_pos;
	}

	coord rect::size() const
	{
		return m_size;
	}

	rect& rect::set_width(int w)
	{
		m_size.x = w > 0 ? w : 0;
		return *this;
	}

	rect& rect::set_height(int h)
	{
		m_size.y = h > 0 ? h : 0;
		return *this;
	}

	rect& rect::set_left(int x)
	{
		m_pos.x = x;
		return *this;
	}


	rect& rect::set_right(int x)
	{
		m_size.x = x - left();
		if (m_size.x < 0) m_size.x = 0;
		return *this;
	}

	rect& rect::set_top(int y)
	{
		m_pos.y = y;
		return *this;
	}

	rect& rect::set_bottom(int y)
	{
		m_size.y = y - top();
		if (m_size.y < 0) m_size.y = 0;
		return *this;
	}

	rect& rect::set_pos(int x, int y)
	{
		set_left(x);
		set_top(y);
		return *this;
	}

	rect& rect::set_pos(const coord& pos)
	{
		return set_pos(pos.x, pos.y);
	}

	rect& rect::set_size(int w, int h)
	{
		set_width(w);
		set_height(h);
		return *this;
	}

	rect& rect::set_size(const coord& size)
	{
		return set_size(size.x, size.y);
	}

	bool rect::hit_test(int x, int y) const
	{
		return !(x < left() || x > right() || y < top() || y > bottom());
	}

	bool rect::hit_test(const coord& point) const
	{
		return hit_test(point.x, point.y);
	}

	int rect::hit_test(const rect& other) const
	{
		int intersect_other = 0;
		if (other.hit_test(left(),  top()))		intersect_other++;
		if (other.hit_test(left(),  bottom()))	intersect_other++;
		if (other.hit_test(right(), top()))		intersect_other++;
		if (other.hit_test(right(), bottom()))	intersect_other++;

		if (intersect_other == 0)
			return outside;
		else if (intersect_other == 4)
			return inside;

		intersect_other = 0;
		if (hit_test(other.left(),  other.top()))		intersect_other++;
		if (hit_test(other.left(),  other.bottom()))	intersect_other++;
		if (hit_test(other.right(), other.top()))		intersect_other++;
		if (hit_test(other.right(), other.bottom()))	intersect_other++;

		if (intersect_other == 4)
			return contain;
		else //
			return intersect;
	}

	rect& rect::move(int offsetx, int offsety)
	{
		m_pos.move(offsetx, offsety);
		return *this;
	}

	rect& rect::enlarge(int offsetw, int offseth)
	{
		m_size.move(offsetw, offseth);
		if (m_size.x < 0) m_size.x = 0;
		if (m_size.y < 0) m_size.y = 0;
		return *this;
	}
}