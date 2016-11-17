#include "stdafx.h"


TEST_CLASS(SwizzleTest)
{
public:
	TEST_METHOD(Vector2SwizzleTest)
	{
		vec2 v2(1, 2), sw2, sw3, sw4;
		vec3 v3(v2, 3);
		vec4 v4(v2, 3, 4);

		sw2 = swizzle<_Y, _X>(v2);
		GML_FEQUAL(sw2.x, v2.y);
		GML_FEQUAL(sw2.y, v2.x);

		sw3 = swizzle<_Y, _Z>(v3);
		GML_FEQUAL(sw3.x, v3.y);
		GML_FEQUAL(sw3.y, v3.z);

		sw4 = swizzle<_Z, _W>(v4);
		GML_FEQUAL(sw4.x, v4.z);
		GML_FEQUAL(sw4.y, v4.w);
	}

	TEST_METHOD(Vector3SwizzleTest)
	{
		vec2 v2(1, 2);
		vec3 v3(v2, 3), sw2, sw3, sw4;
		vec4 v4(v3, 4);

		sw2 = swizzle<_Y, _X, _Y>(v2);
		GML_FEQUAL(sw2.x, v2.y);
		GML_FEQUAL(sw2.y, v2.x);
		GML_FEQUAL(sw2.z, v2.y);

		sw3 = swizzle<_Y, _Z, _X>(v3);
		GML_FEQUAL(sw3.x, v3.y);
		GML_FEQUAL(sw3.y, v3.z);
		GML_FEQUAL(sw3.z, v3.x);

		sw4 = swizzle<_W, _X, _Z>(v4);
		GML_FEQUAL(sw4.x, v4.w);
		GML_FEQUAL(sw4.y, v4.x);
		GML_FEQUAL(sw4.z, v4.z);
	}

	TEST_METHOD(Vector4SwizzleTest)
	{
		vec2 v2(1, 2);
		vec3 v3(v2, 3);
		vec4 v4(v3, 4), sw2, sw3, sw4;

		sw2 = swizzle<_Y, _X, _Y, _X>(v2);
		GML_FEQUAL(sw2.x, v2.y);
		GML_FEQUAL(sw2.y, v2.x);
		GML_FEQUAL(sw2.z, v2.y);
		GML_FEQUAL(sw2.w, v2.x);

		sw3 = swizzle<_Y, _Z, _X, _Z>(v3);
		GML_FEQUAL(sw3.x, v3.y);
		GML_FEQUAL(sw3.y, v3.z);
		GML_FEQUAL(sw3.z, v3.x);
		GML_FEQUAL(sw3.w, v3.z);

		sw4 = swizzle<_W, _X, _Z, _Y>(v4);
		GML_FEQUAL(sw4.x, v4.w);
		GML_FEQUAL(sw4.y, v4.x);
		GML_FEQUAL(sw4.z, v4.z);
		GML_FEQUAL(sw4.w, v4.y);
	}

	TEST_METHOD(Color3SwizzleTest)
	{
		
	}

	TEST_METHOD(Color4SwizzleTest)
	{

	}
};