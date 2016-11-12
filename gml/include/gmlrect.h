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
		coord() = default;

		coord(int x, int y);

		bool operator==(const coord& other) const;

		void set(int x, int y);

		void move(int offsetx, int offsety);
	};

	class rect
	{
	public:
		bool operator==(const rect& other) const;

		int left() const;

		int right() const;

		int top() const;

		int bottom() const;

		int width() const;

		int height() const;

		coord center() const;

		coord position() const;

		coord size() const;
		
		void set_width(int w);

		void set_height(int h);
		
		void set_left(int x);
		
		void set_right(int x);
		
		void set_top(int y);
		
		void set_bottom(int y);
		
		void set_pos(int x, int y);
		
		void set_pos(const coord& pos);
		
		void set_size(int w, int h);
		
		void set_size(const coord& size);

		bool contains(int x, int y) const;

		bool contains(const coord& point) const;

		it_mode hit_test(const rect& other) const;

		void move(int offsetx, int offsety);
		
		void enlarge(int offsetw, int offseth);

	private:
		coord m_pos;
		coord m_size;
	};
}
