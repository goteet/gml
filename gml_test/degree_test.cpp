#include "stdafx.h"

TEST_CLASS(DegreeTest)
{
public:
	TEST_METHOD(DegreeInitializeTest)
	{
		degree d(30);
		GML_FEQUAL(30, d.value);

		degree fromRadian((radian)(PI));
		GML_FEQUAL(180.0f, fromRadian.value);
	}

	TEST_METHOD(DegreeOperationTest)
	{
		auto a = degree(30) + (degree)radian(PI / 6);
		GML_FEQUAL(60.0f, a.value);

		GML_IS_TRUE(degree(30) == (degree)radian(PI / 6));
		GML_IS_TRUE(degree(30) != (degree)radian(PI / 5));
		GML_IS_TRUE(degree(30) > (degree)radian(PI / 7));
		GML_IS_TRUE(degree(30) < (degree)radian(PI / 2));

		GML_FEQUAL(-30, (-degree(30)).value);
	}
};