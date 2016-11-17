#include "stdafx.h"

TEST_CLASS(Matrix3x3Test)
{
public:
	TEST_METHOD(Matrix3x3GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 3 * 3, sizeof(mat33));
	}
};