#include "stdafx.h"

TEST_CLASS(Matrix4x4Test)
{
public:
	TEST_METHOD(Matrix4x4GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 4 * 4, sizeof(mat44));
	}
};