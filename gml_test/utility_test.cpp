#include "stdafx.h"


TEST_CLASS(UtilityTest)
{
	TEST_METHOD(UtilityFequalTest)
	{
		GML_IS_TRUE(fequal(0.0f, -0.0f));
		GML_IS_TRUE(fequal(1.0f, 0.9999999f));
		GML_IS_TRUE(fequal(0.0f - 1.0f, -1.0f));
		GML_IS_TRUE(fequal(1.3f, 1.0f + 0.3f));
	}

	TEST_METHOD(UtilityLerpTest)
	{
		GML_FEQUAL(1.5f, lerp(1.0f, 2.0f, 0.5f));
		GML_FEQUAL(1.0f, lerp(1.0f, 2.0f, 0.0f));
		GML_FEQUAL(2.0f, lerp(1.0f, 2.0f, 1.0f));
	}

	TEST_METHOD(UtilitySwapTest)
	{
		float a = 1.0f, b = 2.0f;
		GML_FEQUAL(1.0f, a);
		GML_FEQUAL(2.0f, b);

		swap(a, b);
		GML_FEQUAL(2.0f, a);
		GML_FEQUAL(1.0f, b);
	}

	TEST_METHOD(UtilityClamp01Test)
	{
		GML_FEQUAL(0.0f, clamp01(-0.1f));
		GML_FEQUAL(0.0f, clamp01(0.0f));
		GML_FEQUAL(0.1f, clamp01(0.1f));
		GML_FEQUAL(1.0f, clamp01(1.0f));
		GML_FEQUAL(1.0f, clamp01(1.1f));
	}

	TEST_METHOD(UtilityClampTest)
	{
		GML_FEQUAL(0.0f, clamp(-0.1f, 0.0f, 10.0f));
		GML_FEQUAL(0.0f, clamp(-0.1f, 0.0f, 0.0f));
		GML_FEQUAL(0.1f, clamp(0.1f, 0.0f, 10.f));
		GML_FEQUAL(10.0f, clamp(10.0f, 0.0f, 10.0f));
		GML_FEQUAL(10.0f, clamp(100.0f, 0.0f, 10.0f));
	}

	TEST_METHOD(UtilityExpTest)
	{
		int rsti1 = gml::exp(5, 5);
		float rstf1 = gml::exp(5.0f, 5);
		float rstf2 = 1.0f;
		int rsti2 = 1;
		for (int i = 0; i < 5; i++)
		{
			rstf2 *= 5.0f;
			rsti2 *= 5;
		}

		GML_IEQUAL(rsti2, rsti1);
		GML_IEQUAL(rstf2, rstf1);

	}
};
