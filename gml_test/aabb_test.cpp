#include "stdafx.h"

TEST_CLASS(AABBTest)
{
public:
	TEST_METHOD(AABBMove)
	{
		aabb bounding(vec3(-2, -2, 1), vec3(2, 2, -1));
		GML_IS_TRUE(bounding.center() == vec3::zero());

		bounding.move({ 2, 2, 1 });
		GML_IS_TRUE(bounding.center() == vec3(2, 2, 1));
		GML_IS_TRUE(bounding.min_bound() == vec3(0, 0, 0));
		GML_IS_TRUE(bounding.max_bound() == vec3(4, 4, 2));

		bounding.move_to({ 0, 0, 0 });
		GML_IS_TRUE(bounding.center() == vec3(0, 0, 0));
		GML_IS_TRUE(bounding.min_bound() == vec3(-2, -2, -1));
		GML_IS_TRUE(bounding.max_bound() == vec3(2, 2, 1));
	}

	TEST_METHOD(AABBEmpty)
	{
		aabb bounding(vec3(-2, 5, -1), vec3(2, -5, -1));
		GML_IS_TRUE(bounding.is_empty());
	}

	TEST_METHOD(AABBComparisonTest)
	{
		aabb empty1;
		aabb empty2(vec3(10, 0, -5), vec3(11, 0, 3));

		GML_IS_FALSE(empty1 == empty2);
		GML_IS_TRUE(empty1 != empty2);
		GML_IS_FALSE(empty2.is_invalid());
		GML_IS_TRUE(empty2.is_empty());

		empty2.expand(vec3(11, 1, 0));
		empty1.expand(vec3::zero());
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

	TEST_METHOD(AABBResizeTest)
	{
		aabb a;
		GML_IS_TRUE(a.center() == vec3::zero());
		GML_IS_TRUE(a.extend() == vec3::zero());
		GML_IS_TRUE(a.min_bound() == vec3::zero());
		GML_IS_TRUE(a.max_bound() == vec3::zero());

		a.expand(vec3::one());

		GML_IS_TRUE(a.center() == vec3::one());
		GML_IS_TRUE(a.extend() == vec3::zero());
		GML_IS_TRUE(a.min_bound() == vec3::one());
		GML_IS_TRUE(a.max_bound() == vec3::one());

		aabb b(vec3(10, 0, -6), vec3(11, 0, -5));
		GML_IS_TRUE(b.center() == vec3(10.5, 0, -5.5));
		GML_IS_TRUE(b.extend() == vec3(0.5, 0, 0.5));
		GML_IS_TRUE(b.min_bound() == vec3(10, 0, -6));
		GML_IS_TRUE(b.max_bound() == vec3(11, 0, -5));

		b.expand(vec3(11, 1, 1));
		GML_IS_TRUE(b.center() == vec3(10.5, 0.5, -2.5));
		GML_IS_TRUE(b.extend() == vec3(0.5, 0.5, 3.5));
		GML_IS_TRUE(b.min_bound() == vec3(10, 0, -6));
		GML_IS_TRUE(b.max_bound() == vec3(11, 1, 1));

		b.move_to({ 0,0,0 });
		b.scaling({ 2, 2, 1.0f / 3.5f });
		GML_IS_TRUE(b.center() == vec3::zero());
		GML_IS_TRUE(b.extend() == vec3::one());
		GML_IS_TRUE(b.min_bound() == -vec3::one());
		GML_IS_TRUE(b.max_bound() == vec3::one());
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