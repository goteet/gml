#include "stdafx.h"


TEST_CLASS(Vector2Test)
{
public:
	TEST_METHOD(Vector2GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 2, sizeof(vec2));
		vec2 v2(vec2::up());
		vec2 v3(vec4::one());
		vec2 v4(vec3::left());
	}

	vec2 memberByStaticFunc = vec2::one();
	vec2 memberByList = { 1, 2 };

	TEST_METHOD(Vector2InitializationTest)
	{
		GML_FEQUALM(1.0f, memberByStaticFunc[0], "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc[1], "member init by static function");

		GML_FEQUALM(1.0f, memberByList.x, "member init by init-list");
		GML_FEQUALM(2.0f, memberByList.y, "member init by init-list");

		vec2 local = { 1,2 };
		GML_FEQUALM(1.0f, local.x, "local init by init-list");
		GML_FEQUALM(2.0f, local.y, "local init by init-list");

		// vec2()
		vec2 v1;
		GML_FEQUAL(0.0f, v1.x);
		GML_FEQUAL(0.0f, v1.y);

		// vec2(float, float)
		vec2 v2(3.0f, 4.0f);
		GML_FEQUAL(3.0f, v2.x);
		GML_FEQUAL(4.0f, v2.y);

		// vec2(vec2)
		auto v3(v2);
		GML_FEQUAL(3.0f, v3.x);
		GML_FEQUAL(4.0f, v3.y);

		// vec2 = vec2
		auto v4 = v2;
		GML_FEQUAL(3.0f, v4.x);
		GML_FEQUAL(4.0f, v4.y);
	}

	TEST_METHOD(Vector2AccessTest)
	{
		vec2 v = { 1, 2 };
		GML_FEQUAL(v.x, memberByList[0]);
		GML_FEQUAL(v.y, memberByList[1]);
	}

	TEST_METHOD(Vector2ConstantsTest)
	{
		// zero
		const auto zero = vec2::zero();
		GML_FEQUAL(0.0f, zero.x);
		GML_FEQUAL(0.0f, zero.y);

		// one
		const auto one = vec2::one();
		GML_FEQUAL(1.0f, one.x);
		GML_FEQUAL(1.0f, one.y);

		// left
		const auto left = vec2::left();
		GML_FEQUAL(-1.0f, left.x);
		GML_FEQUAL(0.0f, left.y);

		// right
		const auto right = vec2::right();
		GML_FEQUAL(1.0f, right.x);
		GML_FEQUAL(0.0f, right.y);

		// up
		const auto up = vec2::up();
		GML_FEQUAL(0.0f, up.x);
		GML_FEQUAL(1.0f, up.y);

		// down
		const auto down = vec2::down();
		GML_FEQUAL(0.0f, down.x);
		GML_FEQUAL(-1.0f, down.y);
	}

	TEST_METHOD(Vector2NegativeTest)
	{
		// operator-
		vec2 v1(3.0f, 4.0f);
		auto v2 = -v1;
		GML_FEQUAL(-3.0f, v2.x);
		GML_FEQUAL(-4.0f, v2.y);

		auto v3 = -vec2::zero();
		GML_FEQUAL(0.0f, v3.x);
		GML_FEQUAL(0.0f, v3.y);
	}

	TEST_METHOD(Vector2CompareTest)
	{
		vec2 v1(1.0f, 2.0f);
		vec2 v2(1.0f, 2.0f);
		vec2 v3(2.0f, 1.0f);

		// operator==
		GML_IS_TRUE(v1 == v2);
		GML_IS_FALSE(v1 == v3);

		// operator!=
		GML_IS_FALSE(v1 != v2);
		GML_IS_TRUE(v1 != v3);
	}

	TEST_METHOD(Vector2AddTest)
	{
		vec2 v1(1.0f, 2.0f);
		vec2 v2(2.0f, 3.0f);
		float f = 2.0f;

		// operator+(float)
		auto a = v1 + f;
		GML_FEQUAL(3.0f, a.x);
		GML_FEQUAL(4.0f, a.y);

		// operator+(vec2)
		auto b = v1 + v2;
		GML_FEQUAL(3.0f, b.x);
		GML_FEQUAL(5.0f, b.y);

		// operator+=(float)
		auto c = v1;
		c += f;
		GML_FEQUAL(3.0f, c.x);
		GML_FEQUAL(4.0f, c.y);

		// operator+(vec2)
		auto d = v1;
		d += v2;
		GML_FEQUAL(3.0f, d.x);
		GML_FEQUAL(5.0f, d.y);
	}

	TEST_METHOD(Vector2MinusTest)
	{
		vec2 v1(1.0f, 2.0f);
		vec2 v2(2.0f, 3.0f);
		float f = 2.0f;

		// operator-(float)
		auto a = v1 - f;
		GML_FEQUAL(-1.0f, a.x);
		GML_FEQUAL(0.0f, a.y);

		// operator-(vec2)
		auto b = v1 - v2;
		GML_FEQUAL(-1.0f, b.x);
		GML_FEQUAL(-1.0f, b.y);

		// operator-=(float)
		auto c = v1;
		c -= f;
		GML_FEQUAL(-1.0f, c.x);
		GML_FEQUAL(0.0f, c.y);

		// operator-(vec2)
		auto d = v1;
		d -= v2;
		GML_FEQUAL(-1.0f, d.x);
		GML_FEQUAL(-1.0f, d.y);
	}

	TEST_METHOD(Vector2MultiplyTest)
	{
		vec2 v1(1.0f, 2.0f);
		vec2 v2(2.0f, 3.0f);
		float f = 2.0f;

		// operator*(float)
		auto a = v1 * f;
		GML_FEQUAL(2.0f, a.x);
		GML_FEQUAL(4.0f, a.y);

		// operator*(vec2)
		auto b = v1 * v2;
		GML_FEQUAL(2.0f, b.x);
		GML_FEQUAL(6.0f, b.y);

		// operator*=(float)
		auto c = v1;
		c *= f;
		GML_FEQUAL(2.0f, c.x);
		GML_FEQUAL(4.0f, c.y);

		// operator*(vec2)
		auto d = v1;
		d *= v2;
		GML_FEQUAL(2.0f, d.x);
		GML_FEQUAL(6.0f, d.y);
	}

	TEST_METHOD(Vector2IndexTest)
	{
		// operator[]
		vec2 v1;
		v1[0] = 1.0f;
		v1[1] = 2.0f;
		GML_FEQUAL(1.0f, v1.x);
		GML_FEQUAL(2.0f, v1.y);
	}

	TEST_METHOD(Vector2ToPointerTest)
	{
		// float*
		vec2 v1(1.0f, 2.0f);
		float *fv = (float *)v1;
		GML_FEQUAL(1.0f, fv[0]);
		GML_FEQUAL(2.0f, fv[1]);
	}

	TEST_METHOD(Vector2SetTest)
	{
		vec2 v1, v2, v3;
		vec3 vvv(1.0f, 2.0f, 3.0f);
		vec4 vvvv(1.0f, 2.0f, 3.0f, 4.0f);

		// set(float, float)
		v1.set(1.0f, 2.0f);
		GML_FEQUAL(1.0f, v1.x);
		GML_FEQUAL(2.0f, v1.y);

		// set(vec3)
		v2.set(vvv);
		GML_FEQUAL(1.0f, v2.x);
		GML_FEQUAL(2.0f, v2.y);

		// set(vec4)
		v3.set(vvvv);
		GML_FEQUAL(1.0f, v3.x);
		GML_FEQUAL(2.0f, v3.y);
	}

	// normalize
	// normalized
	TEST_METHOD(Vector2NormalizeTest)
	{
		vec2 v1(1.0f, 0.0f);
		auto a = v1.normalized();
		v1.normalize();
		GML_FEQUAL(1.0f, v1.x);
		GML_FEQUAL(0.0f, v1.y);
		GML_FEQUAL(1.0f, a.x);
		GML_FEQUAL(0.0f, a.y);

		vec2 v2(2.0f, 0.0f);
		auto b = v2.normalized();
		v2.normalize();
		GML_FEQUAL(1.0f, v2.x);
		GML_FEQUAL(0.0f, v2.y);
		GML_FEQUAL(1.0f, b.x);
		GML_FEQUAL(0.0f, b.y);

		vec2 v3(0.0f, 2.0f);
		auto c = v3.normalized();
		v3.normalize();
		GML_FEQUAL(0.0f, v3.x);
		GML_FEQUAL(1.0f, v3.y);
		GML_FEQUAL(0.0f, c.x);
		GML_FEQUAL(1.0f, c.y);

		vec2 v4(3.0f, 4.0f);
		auto d = v4.normalized();
		v4.normalize();
		GML_FEQUAL(0.6f, v4.x);
		GML_FEQUAL(0.8f, v4.y);
		GML_FEQUAL(0.6f, d.x);
		GML_FEQUAL(0.8f, d.y);
	}

	// inverse
	// inversed
	TEST_METHOD(Vector2InverseTest)
	{
		vec2 v1(1.0f, 0.0f);
		auto a = v1.inversed();
		v1.inverse();
		GML_FEQUAL(1.0f, v1.x);
		GML_FEQUAL(0.0f, v1.y);
		GML_FEQUAL(1.0f, a.x);
		GML_FEQUAL(0.0f, a.y);

		vec2 v2(2.0f, 0.0f);
		auto b = v2.inversed();
		v2.inverse();
		GML_FEQUAL(0.5f, v2.x);
		GML_FEQUAL(0.0f, v2.y);
		GML_FEQUAL(0.5f, b.x);
		GML_FEQUAL(0.0f, b.y);

		vec2 v3(0.0f, 2.0f);
		auto c = v3.inversed();
		v3.inverse();
		GML_FEQUAL(0.0f, v3.x);
		GML_FEQUAL(0.5f, v3.y);
		GML_FEQUAL(0.0f, c.x);
		GML_FEQUAL(0.5f, c.y);

		vec2 v4(3.0f, 4.0f);
		auto d = v4.inversed();
		v4.inverse();
		GML_FEQUAL(0.12f, v4.x);
		GML_FEQUAL(0.16f, v4.y);
		GML_FEQUAL(0.12f, d.x);
		GML_FEQUAL(0.16f, d.y);
	}

	TEST_METHOD(Vector2LengthTest)
	{
		vec2 v1(2.0f, 0.0f);
		vec2 v2(3.0f, 4.0f);

		// length
		GML_FEQUAL(2.0f, v1.length());
		GML_FEQUAL(5.0f, v2.length());

		// length_sqr
		GML_FEQUAL(4.0f, v1.length_sqr());
		GML_FEQUAL(25.0f, v2.length_sqr());
	}

	TEST_METHOD(Vector2DotTest)
	{
		// dot
		vec2 v1(1.0f, 2.0f);
		vec2 v2(3.0f, 0.0f);

		GML_FEQUAL(3.0f, dot(v1, v2));
	}

	TEST_METHOD(Vector2CrossTest)
	{
		// cross
		vec2 v1(1.0f, 2.0f);
		vec2 v2(3.0f, 0.0f);

		GML_FEQUAL(-6.0f, cross(v1, v2));
	}

	TEST_METHOD(Vector2CombineTest)
	{
		vec2 v1(1.0f, 2.0f);
		vec2 v2(3.0f, 0.0f);

		// min_combine
		auto minV = min_combine(v1, v2);
		GML_FEQUAL(1.0f, minV.x);
		GML_FEQUAL(0.0f, minV.y);

		// max_combine
		auto maxV = max_combine(v1, v2);
		GML_FEQUAL(3.0f, maxV.x);
		GML_FEQUAL(2.0f, maxV.y);
	}

	TEST_METHOD(Vector2Det22Test)
	{
		vec2 v1(1.0f, 2.0f);
		vec2 v2(3.0f, 0.0f);

		// det22
		GML_FEQUAL(-6.0f, det22(v1, v2));

		// det22_t
		GML_FEQUAL(-6.0f, det22_t(v1, v2));
	}

	TEST_METHOD(Vector2LerpTest)
	{
		const auto v1 = vec2::one();
		const vec2 v2(2.0f, 2.0f);

		auto lerpV = lerp(v1, v2, 0.5f);
		GML_FEQUAL(1.5f, lerpV.x);
		GML_FEQUAL(1.5f, lerpV.y);

		lerpV = lerp(v1, v2, 0.0f);
		GML_FEQUAL(1.0f, lerpV.x);
		GML_FEQUAL(1.0f, lerpV.y);

		lerpV = lerp(v1, v2, 1.0f);
		GML_FEQUAL(2.0f, lerpV.x);
		GML_FEQUAL(2.0f, lerpV.y);
	}
};
