#include "stdafx.h"

TEST_CLASS(Vector4Test)
{
public:
	TEST_METHOD(Vector4GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 4, sizeof(vec4));
	}

	vec4 memberByList = { 1, 2, 3,4 };

	TEST_METHOD(Vector4InitializationTest)
	{
		GML_FEQUALM(1.0f, memberByList.x, "member init by init-list");
		GML_FEQUALM(2.0f, memberByList.y, "member init by init-list");
		GML_FEQUALM(3.0f, memberByList.z, "member init by init-list");
		GML_FEQUALM(4.0f, memberByList.w, "member init by init-list");

		vec4 local = { 1,2,3,4 };
		GML_FEQUALM(1.0f, local[0], "local init by init-list");
		GML_FEQUALM(2.0f, local[1], "local init by init-list");
		GML_FEQUALM(3.0f, local[2], "local init by init-list");
		GML_FEQUALM(4.0f, local[3], "local init by init-list");
	}

	TEST_METHOD(Vector4AccessTest)
	{
		vec4 v = { 1, 2, 3,4 };
		GML_FEQUAL(v.x, memberByList[0]);
		GML_FEQUAL(v.y, memberByList[1]);
		GML_FEQUAL(v.z, memberByList[2]);
		GML_FEQUAL(v.w, memberByList[3]);
	}
};