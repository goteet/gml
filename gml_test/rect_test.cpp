#include "stdafx.h"


TEST_CLASS(RectTest)
{
private:
	rect mRect;

public:
	RectTest()
	{
		mRect.set_pos(10, 10);
		mRect.set_size(20, 20);
	}

	TEST_METHOD(RectEqualTest)
	{
		// operator==
		rect r1;
		r1.set_pos(10, 10);
		r1.set_size(20, 20);
		GML_IS_TRUE(mRect == r1);

		rect r2;
		r2.set_pos(11, 11);
		r2.set_pos(20, 20);
		GML_IS_FALSE(mRect == r2);

		rect r3;
		r3.set_pos(10, 10);
		r3.set_size(21, 21);
		GML_IS_FALSE(mRect == r3);
	}

	TEST_METHOD(RectAccessTest)
	{
		GML_IEQUAL(10, mRect.left());
		GML_IEQUAL(30, mRect.right());
		GML_IEQUAL(10, mRect.top());
		GML_IEQUAL(30, mRect.bottom());
		GML_IEQUAL(20, mRect.width());
		GML_IEQUAL(20, mRect.height());

		coord center = mRect.center();
		GML_IEQUAL(20, center.x);
		GML_IEQUAL(20, center.y);

		coord pos = mRect.position();
		GML_IEQUAL(10, pos.x);
		GML_IEQUAL(10, pos.y);

		coord size = mRect.size();
		GML_IEQUAL(20, size.x);
		GML_IEQUAL(20, size.y);
	}

	TEST_METHOD(RectContainsTest)
	{
		GML_IS_TRUE(mRect.contains(11, 11));
		GML_IS_FALSE(mRect.contains(9, 9));
		GML_IS_FALSE(mRect.contains(31, 9));
		GML_IS_FALSE(mRect.contains(31, 31));

		GML_IS_TRUE(mRect.contains(coord(11, 11)));
		GML_IS_FALSE(mRect.contains(coord(9, 9)));
		GML_IS_FALSE(mRect.contains(coord(31, 9)));
		GML_IS_FALSE(mRect.contains(coord(9, 31)));
	}

	TEST_METHOD(RectHitTestTest)
	{
		rect r;
		r.set_pos(1, 1);
		r.set_size(5, 5);

		GML_IS_TRUE(mRect.hit_test(r) == it_mode::none);

		r.enlarge(5, 5);
		GML_IS_TRUE(mRect.hit_test(r) == it_mode::hit);

		r.enlarge(20, 20);
		GML_IS_TRUE(mRect.hit_test(r) == it_mode::inside);

		r.move(10, 10);
		r.enlarge(-20, -20);
		GML_IS_TRUE(mRect.hit_test(r) == it_mode::contain);

		r.move(-1, -1);
		r.enlarge(10, 10);
		GML_IS_TRUE(mRect.hit_test(r) == it_mode::same);
	}

	TEST_METHOD(RectMoveTest)
	{
		rect r;
		r.set_pos(10, 10);
		r.set_size(20, 20);

		r.move(10, 10);
		GML_IEQUAL(20, r.left());
		GML_IEQUAL(40, r.right());
		GML_IEQUAL(20, r.top());
		GML_IEQUAL(40, r.bottom());
		GML_IEQUAL(20, r.width());
		GML_IEQUAL(20, r.height());
	}

	TEST_METHOD(RectEnlargeTest)
	{
		rect r;
		r.set_pos(10, 10);
		r.set_size(20, 20);

		r.enlarge(10, 10);
		GML_IEQUAL(10, r.left());
		GML_IEQUAL(40, r.right());
		GML_IEQUAL(10, r.top());
		GML_IEQUAL(40, r.bottom());
		GML_IEQUAL(30, r.width());
		GML_IEQUAL(30, r.height());
	}
};