#include "stdafx.h"

namespace gml
{
	TEST_CLASS(UtilityTest)
	{
		TEST_METHOD(testUtilityFequal)
		{
			GML_IS_TRUE(fequal(0.0f, -0.0f));
			GML_IS_TRUE(fequal(1.0f, 0.9999999f));
		 // GML_IS_TRUE(fequal(1.0f, 0.999999f));
			GML_IS_TRUE(fequal(0.0f - 1.0f, -1.0f));
			GML_IS_TRUE(fequal(1.3f, 1.0f + 0.3f));
		}

		TEST_METHOD(testUtilityLerp)
		{
			GML_FEQUAL(1.5f, lerp(1.0f, 2.0f, 0.5f));
			GML_FEQUAL(1.0f, lerp(1.0f, 2.0f, 0.0f));
			GML_FEQUAL(2.0f, lerp(1.0f, 2.0f, 1.0f));
		}

		TEST_METHOD(testUtilitySwap)
		{
			float a = 1.0f, b = 2.0f;
			GML_FEQUAL(1.0f, a);
			GML_FEQUAL(2.0f, b);
			
			swap(a, b);
			GML_FEQUAL(2.0f, a);
			GML_FEQUAL(1.0f, b);
		}

		TEST_METHOD(testUtilityClamp01)
		{
			GML_FEQUAL(0.0f, clamp01(-0.1f));
			GML_FEQUAL(0.0f, clamp01(0.0f));
			GML_FEQUAL(0.1f, clamp01(0.1f));
			GML_FEQUAL(1.0f, clamp01(1.0f));
			GML_FEQUAL(1.0f, clamp01(1.1f));
		}

		TEST_METHOD(testUtilityClamp)
		{
			GML_FEQUAL(0.0f, clamp(-0.1f, 0.0f, 10.0f));
			GML_FEQUAL(0.0f, clamp(-0.1f, 0.0f, 0.0f));
			GML_FEQUAL(0.1f, clamp(0.1f, 0.0f, 10.f));
			GML_FEQUAL(10.0f, clamp(10.0f, 0.0f, 10.0f));
			GML_FEQUAL(10.0f, clamp(100.0f, 0.0f, 10.0f));
		}
	};
}
