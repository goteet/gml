#include "stdafx.h"

TEST_CLASS(Matrix3x2Test)
{
public:
	TEST_METHOD(Matrix3x2GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 3 * 2, sizeof(mat32));
	}
};