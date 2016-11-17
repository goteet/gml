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
};