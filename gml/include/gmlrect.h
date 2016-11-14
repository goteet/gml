#pragma once
#include <gmlutility.h>

namespace gml
{
	class coord
	{
	public:
		int x = 0;
		int y = 0;

	public:
		constexpr coord() = default;

		constexpr coord(int _x, int _y) :x(_x), y(_y) { }

		friend constexpr bool operator==(const coord& lhs, const coord& rhs) { return (&lhs == &rhs) || ((lhs.x == rhs.x) && (lhs.y == rhs.y)); }

		friend constexpr bool operator!=(const coord& lhs, const coord& rhs) { return !(lhs == rhs); }

		inline void set(int _x, int _y) { x = _x; y = _y; }

		inline void move(int offsetx, int offsety) { set(x + offsetx, y + offsety); }
	};

	class rect
	{
	public:
		friend constexpr bool operator==(const rect& lhs, const rect& rhs) { return (&lhs == &rhs) || ((lhs.m_pos == rhs.m_pos) && (lhs.m_size == rhs.m_size)); }

		constexpr int left() const { return m_pos.x; }

		constexpr int right() const { return left() + width(); }

		constexpr int top() const { return m_pos.y; }

		constexpr int bottom() const { return  top() + height(); }

		constexpr int width() const { return m_size.x; }

		constexpr int height() const { return m_size.y; }

		constexpr coord center() const { return coord((left() + right()) / 2, (top() + bottom()) / 2); }

		constexpr coord position() const { return m_pos; }

		constexpr coord size() const { return m_size; }

		inline void set_width(int w) { m_size.x = w > 0 ? w : 0; }

		inline void set_height(int h) { m_size.y = h > 0 ? h : 0; }

		inline void set_pos(int x, int y) { m_pos.set(x, y); }

		inline void set_pos(const coord& pos) { m_pos = pos; }

		inline void set_size(int w, int h) { m_size.set(w, h); }

		inline void set_size(const coord& size) { m_size = size; }

		constexpr bool contains(int x, int y) const { return !(x < left() || x > right() || y < top() || y > bottom()); }

		constexpr bool contains(const coord& point) const { return contains(point.x, point.y); }

		inline it_mode hit_test(const rect& other) const
		{
			if (this == &other)
			{
				return it_same;
			}

			int intersection_count = get_intersection_count(other, *this);
			if (intersection_count == 4)
			{
				return it_inside;
			}
			// Impossible 3.
			else if (intersection_count == 2 || intersection_count == 1)
			{
				return it_hit;
			}
			else
			{
				intersection_count = get_intersection_count(*this, other);
				if (intersection_count == 4)
				{
					return it_contain;
				}
				// Impossible 3.
				else if (intersection_count == 2) // Impossible 1
				{
					return it_hit;
				}
				else
				{
					return it_none;
				}
			}
		}

		inline void move(int offsetx, int offsety) { m_pos.move(offsetx, offsety); }

		inline void enlarge(int offsetw, int offseth)
		{
			m_size.move(offsetw, offseth);
			if (m_size.x < 0) m_size.x = 0;
			if (m_size.y < 0) m_size.y = 0;
		}

	private:
		inline int get_intersection_count(const rect& container, const rect& to_check) const
		{
			int intersect_other = 0;

			if (container.contains(to_check.left(), to_check.top()))		intersect_other++;
			if (container.contains(to_check.left(), to_check.bottom()))		intersect_other++;
			if (container.contains(to_check.right(), to_check.top()))		intersect_other++;
			if (container.contains(to_check.right(), to_check.bottom()))	intersect_other++;
			return intersect_other;
		}

		coord m_pos;
		coord m_size;
	};
}
