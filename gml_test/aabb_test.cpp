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
};