#pragma once

namespace gml
{
	typedef enum HIT_TYPE
	{
		outside		= 0,
		intersect	= 1,
		contain		= 2,
		inside		= 3,
	} HIT_TYPE;

	class coord
	{
	public:
		int x = 0;
		int y = 0;

	public:
		coord();

		coord(int x, int y);

		coord& set(int x, int y);

		coord& move(int offsetx, int offsety);
	};

	class rect
	{
	public:
		int left() const;

		int right() const;

		int top() const;

		int bottom() const;

		int width() const;

		int height() const;

		coord center() const;

		coord position() const;

		coord size() const;
		
		rect& set_width(int w);

		rect& set_height(int h);

		rect& set_left(int x);

		rect& set_right(int x);

		rect& set_top(int y);

		rect& set_bottom(int y);

		rect& set_pos(int x, int y);

		rect& set_pos(const coord& pos);

		rect& set_size(int w, int h);

		rect& set_size(const coord& size);

		bool hit_test(int x, int y) const;

		bool hit_test(const coord& point) const;

		int hit_test(const rect& other) const;

		rect& move(int offsetx, int offsety);
		
		rect& enlarge(int offsetw, int offseth);

	private:
		coord m_pos;
		coord m_size;
	};
}
