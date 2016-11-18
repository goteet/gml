#include "stdafx.h"

TEST_CLASS(AABB2DTest)
{
public:
	TEST_METHOD(AABB2DMove)
	{
		aabb2d bounding(vec2(-2, -2), vec2(2, 2));
		GML_IS_TRUE(bounding.center() == vec2::zero());

		bounding.move({ 2, 2 });
		GML_IS_TRUE(bounding.center() == vec2(2, 2));
		GML_IS_TRUE(bounding.min_bound() == vec2(0, 0));
		GML_IS_TRUE(bounding.max_bound() == vec2(4, 4));

		bounding.move_to({ 0, 0 });
		GML_IS_TRUE(bounding.center() == vec2(0, 0));
		GML_IS_TRUE(bounding.min_bound() == vec2(-2, -2));
		GML_IS_TRUE(bounding.max_bound() == vec2(2, 2));
	}

	TEST_METHOD(AABB2DEmpty)
	{
		aabb2d bounding(vec2(-2, 0), vec2(2, 0));
		GML_IS_TRUE(bounding.is_empty());
	}

	TEST_METHOD(AABB2DComparisonTest)
	{
		aabb2d empty1;
		aabb2d empty2(vec2(10, 0), vec2(11, 0));

		GML_IS_FALSE(empty1 == empty2);
		GML_IS_TRUE(empty1 != empty2);
		GML_IS_FALSE(empty2.is_invalid());
		GML_IS_TRUE(empty2.is_empty());

		empty2.expand(vec2(11, 1));
		empty1.expand(vec2::zero());
		GML_IS_TRUE(empty1 != empty2);
		GML_IS_TRUE(empty1.is_empty());
		GML_IS_FALSE(empty1.is_invalid());
		GML_IS_FALSE(empty2.is_empty());

		empty1.clear();
		empty2.clear();
		GML_IS_TRUE(empty1 == empty2);
		GML_IS_TRUE(empty1.is_invalid());
		GML_IS_TRUE(empty1.is_invalid());
	}

	TEST_METHOD(AABB2DResizeTest)
	{
		aabb2d a;
		GML_IS_TRUE(a.center() == vec2::zero());
		GML_IS_TRUE(a.extend() == vec2::zero());
		GML_IS_TRUE(a.min_bound() == vec2::zero());
		GML_IS_TRUE(a.max_bound() == vec2::zero());

		a.expand(vec2::one());

		GML_IS_TRUE(a.center() == vec2::one());
		GML_IS_TRUE(a.extend() == vec2::zero());
		GML_IS_TRUE(a.min_bound() == vec2::one());
		GML_IS_TRUE(a.max_bound() == vec2::one());

		aabb2d b(vec2(10, 0), vec2(11, 0));
		GML_IS_TRUE(b.center() == vec2(10.5, 0));
		GML_IS_TRUE(b.extend() == vec2(0.5, 0));
		GML_IS_TRUE(b.min_bound() == vec2(10, 0));
		GML_IS_TRUE(b.max_bound() == vec2(11, 0));

		b.expand(vec2(11, 1));
		GML_IS_TRUE(b.center() == vec2(10.5, 0.5));
		GML_IS_TRUE(b.extend() == vec2(0.5, 0.5));
		GML_IS_TRUE(b.min_bound() == vec2(10, 0));
		GML_IS_TRUE(b.max_bound() == vec2(11, 1));

		b.move_to({ 0,0 });
		b.scaling(2);
		GML_IS_TRUE(b.center() == vec2::zero());
		GML_IS_TRUE(b.extend() == vec2(1, 1));
		GML_IS_TRUE(b.min_bound() == vec2(-1, -1));
		GML_IS_TRUE(b.max_bound() == vec2(1, 1));
	}

	TEST_METHOD(AABB2DIntersectTest)
	{
		const aabb2d empty;
		aabb2d b(vec2(10, 0), vec2(11, 0));

		GML_IS_FALSE(empty.contains(b));
		GML_IS_FALSE(empty.contains(vec2::zero()));
		GML_IS_TRUE(empty.is_intersect(b) == it_none);

		GML_IS_FALSE(b.contains(empty));
		GML_IS_FALSE(b.contains(vec2::zero()));
		GML_IS_TRUE(b.contains(vec2(10.5, 0)));
		GML_IS_TRUE(b.is_intersect(empty) == it_none);

		auto a = b;
		a.expand(vec2(11, 1));
		GML_IS_FALSE(empty.contains(a));
		GML_IS_TRUE(empty.is_intersect(a) == it_none);

		GML_IS_FALSE(a.contains(empty));
		GML_IS_FALSE(a.contains(vec2::zero()));
		GML_IS_TRUE(a.contains(vec2(11, 0.5)));
		GML_IS_TRUE(a.is_intersect(empty) == it_none);
		GML_IS_TRUE(a.is_intersect(b) == it_hit);
	}
};