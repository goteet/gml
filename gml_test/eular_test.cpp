#include "stdafx.h"

TEST_CLASS(EulerTest)
{
public:
	TEST_METHOD(EulerInitializationTest)
	{
		euler a;
		GML_IS_TRUE(radian(0.0f) == a.yaw);
		GML_IS_TRUE(radian(0.0f) == a.roll);
		GML_IS_TRUE(radian(0.0f) == a.pitch);
	}

	TEST_METHOD(EulerComparisionTest)
	{
		euler a;
		euler b(vec3(PI / 3, PI / 3, PI / 3));

		GML_IS_FALSE(a == b);
		GML_IS_TRUE(a != b);

		a.roll = degree(60);
		a.pitch = degree(60);
		a.yaw = degree(60);

		GML_IS_TRUE(a == b);
		GML_IS_FALSE(a != b);

		auto v3 = a.to_radian3();
		GML_FEQUAL(PI / 3, v3.x);
		GML_FEQUAL(PI / 3, v3.y);
		GML_FEQUAL(PI / 3, v3.z);

	}
};