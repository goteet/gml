#include "stdafx.h"

TEST_CLASS(RadianTest)
{
public:
	TEST_METHOD(RadianInitializeTest)
	{
		radian r(0.5f);
		GML_FEQUAL(0.5f, r.value);

		radian fromDegree(degree(180));
		GML_FEQUAL(PI, fromDegree.value);
	}

	TEST_METHOD(RadianOperationTest)
	{
		auto a = (radian)degree(30) + radian(PI / 6);
		GML_FEQUAL(PI / 3, a.value);

		GML_IS_TRUE((radian)degree(30) == radian(PI / 6));
		GML_IS_TRUE((radian)degree(30) != radian(PI / 5));
		GML_IS_TRUE((radian)degree(30) > radian(PI / 7));
		GML_IS_TRUE((radian)degree(30) < radian(PI / 2));
		GML_FEQUAL(-PI, (-radian(PI)).value);
	}
};