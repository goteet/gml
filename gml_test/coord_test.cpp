#include "stdafx.h"

TEST_CLASS(CoordinateTest)
{
public:
	TEST_METHOD(CoordinateComparisionTest)
	{
		coord a;
		coord b;
		GML_IS_TRUE(a == b);
		GML_IS_FALSE(a != b);

		a.set(3, 2);
		GML_IS_TRUE(a != b);
		GML_IS_FALSE(a == b);

		b.move(3, 2);
		GML_IS_TRUE(a == b);
		GML_IS_FALSE(a != b);
	}


	TEST_METHOD(CoordinateBehaviorTest)
	{
		coord a;
		GML_FEQUAL(0, a.x);
		GML_FEQUAL(0, a.y);

		a.set(1, 2);
		GML_FEQUAL(1, a.x);
		GML_FEQUAL(2, a.y);

		a.move(-1, -2);
		GML_FEQUAL(0, a.x);
		GML_FEQUAL(0, a.y);
	}
};