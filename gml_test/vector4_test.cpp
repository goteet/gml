#include "stdafx.h"

TEST_CLASS(Vector4Test)
{
public:
	TEST_METHOD(Vector4GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 4, sizeof(vec4));
	}
};