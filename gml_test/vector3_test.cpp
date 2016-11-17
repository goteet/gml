#include "stdafx.h"

namespace gml
{
	TEST_CLASS(Vector3Test)
	{
	public:
		TEST_METHOD(Vector3GenericTest)
		{
			GML_IEQUAL(sizeof(float) * 3, sizeof(vec3));
		}
		TEST_METHOD(Vec3InitializationTest)
		{
			// vec3()
			vec3 v1;
			GML_FEQUAL(0.0f, v1.x);
			GML_FEQUAL(0.0f, v1.y);
			GML_FEQUAL(0.0f, v1.z);

			// vec3(float, float, float)
			vec3 v2(3.0f, 4.0f, 5.0f);
			GML_FEQUAL(3.0f, v2.x);
			GML_FEQUAL(4.0f, v2.y);
			GML_FEQUAL(5.0f, v2.z);

			// vec3(vec3)
			auto v3(v2);
			GML_FEQUAL(3.0f, v3.x);
			GML_FEQUAL(4.0f, v3.y);
			GML_FEQUAL(5.0f, v3.z);

			// vec3 = vec3
			auto v4 = v2;
			GML_FEQUAL(3.0f, v4.x);
			GML_FEQUAL(4.0f, v4.y);
			GML_FEQUAL(5.0f, v4.z);
		}

		TEST_METHOD(Vec3ConstantTest)
		{
			// zero
			const auto zero = vec3::zero();
			GML_FEQUAL(0.0f, zero.x);
			GML_FEQUAL(0.0f, zero.y);
			GML_FEQUAL(0.0f, zero.z);

			// one
			const auto one = vec3::one();
			GML_FEQUAL(1.0f, one.x);
			GML_FEQUAL(1.0f, one.y);
			GML_FEQUAL(1.0f, one.z);

			// left
			const auto left = vec3::left();
			GML_FEQUAL(-1.0f, left.x);
			GML_FEQUAL(0.0f, left.y);
			GML_FEQUAL(0.0f, left.z);

			// right
			const auto right = vec3::right();
			GML_FEQUAL(1.0f, right.x);
			GML_FEQUAL(0.0f, right.y);
			GML_FEQUAL(0.0f, right.z);

			// up
			const auto up = vec3::up();
			GML_FEQUAL(0.0f, up.x);
			GML_FEQUAL(1.0f, up.y);
			GML_FEQUAL(0.0f, up.z);

			// down
			const auto down = vec3::down();
			GML_FEQUAL(0.0f, down.x);
			GML_FEQUAL(-1.0f, down.y);
			GML_FEQUAL(0.0f, down.z);

			// forward
			const auto forward = vec3::forward();
			GML_FEQUAL(0.0f, forward.x);
			GML_FEQUAL(0.0f, forward.y);
			GML_FEQUAL(1.0f, forward.z);

			// backward
			const auto backward = vec3::backward();
			GML_FEQUAL(0.0f, backward.x);
			GML_FEQUAL(0.0f, backward.y);
			GML_FEQUAL(-1.0f, backward.z);
		}

		TEST_METHOD(Vec3NegativeTest)
		{
			// operator-
			vec3 v1(3.0f, 4.0f, 5.0f);
			auto v2 = -v1;
			GML_FEQUAL(-3.0f, v2.x);
			GML_FEQUAL(-4.0f, v2.y);
			GML_FEQUAL(-5.0f, v2.z);

			auto v3 = -vec3::zero();
			GML_FEQUAL(0.0f, v3.x);
			GML_FEQUAL(0.0f, v3.y);
			GML_FEQUAL(0.0f, v3.z);
		}

		TEST_METHOD(Vec3CompareTest)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(1.0f, 2.0f, 3.0f);
			vec3 v3(2.0f, 1.0f, 2.0f);

			// operator==
			GML_IS_TRUE(v1 == v2);

			// operator!=
			GML_IS_FALSE(v1 == v3);
		}

		TEST_METHOD(Vec3AddTest)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(2.0f, 3.0f, 4.0f);
			float f = 2.0f;

			// operator+(float)
			auto a = v1 + f;
			GML_FEQUAL(3.0f, a.x);
			GML_FEQUAL(4.0f, a.y);
			GML_FEQUAL(5.0f, a.z);

			// operator+(vec3)
			auto b = v1 + v2;
			GML_FEQUAL(3.0f, b.x);
			GML_FEQUAL(5.0f, b.y);
			GML_FEQUAL(7.0f, b.z);

			// operator+=(float)
			auto c = v1;
			c += f;
			GML_FEQUAL(3.0f, c.x);
			GML_FEQUAL(4.0f, c.y);
			GML_FEQUAL(5.0f, c.z);

			// operator+(vec3)
			auto d = v1;
			d += v2;
			GML_FEQUAL(3.0f, d.x);
			GML_FEQUAL(5.0f, d.y);
			GML_FEQUAL(7.0f, d.z);
		}

		TEST_METHOD(Vec3MinusTest)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(2.0f, 3.0f, 4.0f);
			float f = 2.0f;

			// operator-(float)
			auto a = v1 - f;
			GML_FEQUAL(-1.0f, a.x);
			GML_FEQUAL(0.0f, a.y);
			GML_FEQUAL(1.0f, a.z);

			// operator-(vec3)
			auto b = v1 - v2;
			GML_FEQUAL(-1.0f, b.x);
			GML_FEQUAL(-1.0f, b.y);
			GML_FEQUAL(-1.0f, b.z);

			// operator-=(float)
			auto c = v1;
			c -= f;
			GML_FEQUAL(-1.0f, c.x);
			GML_FEQUAL(0.0f, c.y);
			GML_FEQUAL(1.0f, c.z);

			// operator-(vec3)
			auto d = v1;
			d -= v2;
			GML_FEQUAL(-1.0f, d.x);
			GML_FEQUAL(-1.0f, d.y);
			GML_FEQUAL(-1.0f, d.z);
		}

		TEST_METHOD(Vec3MultiplyTest)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(2.0f, 3.0f, 4.0f);
			float f = 2.0f;

			// operator*(float)
			auto a = v1 * f;
			GML_FEQUAL(2.0f, a.x);
			GML_FEQUAL(4.0f, a.y);
			GML_FEQUAL(6.0f, a.z);

			// operator*(vec3)
			auto b = v1 * v2;
			GML_FEQUAL(2.0f, b.x);
			GML_FEQUAL(6.0f, b.y);
			GML_FEQUAL(12.0f, b.z);

			// operator*=(float)
			auto c = v1;
			c *= f;
			GML_FEQUAL(2.0f, c.x);
			GML_FEQUAL(4.0f, c.y);
			GML_FEQUAL(6.0f, c.z);

			// operator*(vec3)
			auto d = v1;
			d *= v2;
			GML_FEQUAL(2.0f, d.x);
			GML_FEQUAL(6.0f, d.y);
			GML_FEQUAL(12.0f, d.z);
		}

		TEST_METHOD(Vec3IndexTest)
		{
			// operator[]
			vec3 v1;
			v1[0] = 1.0f;
			v1[1] = 2.0f;
			v1[2] = 3.0f;
			GML_FEQUAL(1.0f, v1.x);
			GML_FEQUAL(v1[0], v1.x);
			GML_FEQUAL(2.0f, v1.y);
			GML_FEQUAL(v1[1], v1.y);
			GML_FEQUAL(3.0f, v1.z);
			GML_FEQUAL(v1[2], v1.z);
		}

		TEST_METHOD(Vec3ToPointerTest)
		{
			// float*
			vec3 v1(1.0f, 2.0f, 3.0f);
			float *fv = (float *)v1;
			GML_FEQUAL(1.0f, fv[0]);
			GML_FEQUAL(2.0f, fv[1]);
			GML_FEQUAL(3.0f, fv[2]);
		}

		TEST_METHOD(Vec3SetTest)
		{
			vec3 v1, v2, v3;
			vec2 vv(1.0f, 2.0f);
			vec4 vvvv(1.0f, 2.0f, 3.0f, 4.0f);

			// set(float, float, float)
			v1.set(1.0f, 2.0f, 3.0f);
			GML_FEQUAL(1.0f, v1.x);
			GML_FEQUAL(2.0f, v1.y);
			GML_FEQUAL(3.0f, v1.z);

			// set(vec2)
			v2.set(vv, 3.0f);
			GML_FEQUAL(1.0f, v2.x);
			GML_FEQUAL(2.0f, v2.y);
			GML_FEQUAL(3.0f, v2.z);

			// set(vec4)
			v3.set(vvvv);
			GML_FEQUAL(1.0f, v3.x);
			GML_FEQUAL(2.0f, v3.y);
			GML_FEQUAL(3.0f, v3.z);
		}

		TEST_METHOD(Vec3ReplaceTest)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec2 vv(0.0f, 0.0f);

			GML_FEQUAL(1.0f, v1.x);
			GML_FEQUAL(2.0f, v1.y);

			// replace
			v1.replace(vv);
			GML_FEQUAL(0.0f, v1.x);
			GML_FEQUAL(0.0f, v1.y);
		}

		// normalize
		// normalized
		TEST_METHOD(Vec3NormalizeTest)
		{
			vec3 v1(1.0f, 0.0f, 0.0f);
			auto a = v1.normalized();
			v1.normalize();
			GML_FEQUAL(1.0f, v1.x);
			GML_FEQUAL(0.0f, v1.y);
			GML_FEQUAL(0.0f, v1.z);
			GML_FEQUAL(1.0f, a.x);
			GML_FEQUAL(0.0f, a.y);
			GML_FEQUAL(0.0f, a.z);

			vec3 v2(2.0f, 0.0f, 0.0f);
			auto b = v2.normalized();
			v2.normalize();
			GML_FEQUAL(1.0f, v2.x);
			GML_FEQUAL(0.0f, v2.y);
			GML_FEQUAL(0.0f, v2.z);
			GML_FEQUAL(1.0f, b.x);
			GML_FEQUAL(0.0f, b.y);
			GML_FEQUAL(0.0f, b.z);

			vec3 v3(0.0f, 2.0f, 0.0f);
			auto c = v3.normalized();
			v3.normalize();
			GML_FEQUAL(0.0f, v3.x);
			GML_FEQUAL(1.0f, v3.y);
			GML_FEQUAL(0.0f, v3.z);
			GML_FEQUAL(0.0f, c.x);
			GML_FEQUAL(1.0f, c.y);
			GML_FEQUAL(0.0f, c.z);

			vec3 v4(0.0f, 0.0f, 2.0f);
			auto d = v4.normalized();
			v4.normalize();
			GML_FEQUAL(0.0f, v4.x);
			GML_FEQUAL(0.0f, v4.y);
			GML_FEQUAL(1.0f, v4.z);
			GML_FEQUAL(0.0f, d.x);
			GML_FEQUAL(0.0f, d.y);
			GML_FEQUAL(1.0f, d.z);

			vec3 v5(3.0f, 4.0f, 5.0f);
			auto e = v5.normalized();
			v5.normalize();
			GML_FEQUAL(0.424264f, v5.x);
			GML_FEQUAL(0.5656854f, v5.y);
			GML_FEQUAL(0.7071067f, v5.z);
			GML_FEQUAL(0.424264f, e.x);
			GML_FEQUAL(0.5656854f, e.y);
			GML_FEQUAL(0.7071067f, e.z);
		}

		// inverse
		// inversed
		TEST_METHOD(Vec3InverseTest)
		{
			vec3 v1(1.0f, 0.0f, 0.0f);
			auto a = v1.inversed();
			v1.inverse();
			GML_FEQUAL(1.0f, v1.x);
			GML_FEQUAL(0.0f, v1.y);
			GML_FEQUAL(0.0f, v1.z);
			GML_FEQUAL(1.0f, a.x);
			GML_FEQUAL(0.0f, a.y);
			GML_FEQUAL(0.0f, a.z);

			vec3 v2(2.0f, 0.0f, 0.0f);
			auto b = v2.inversed();
			v2.inverse();
			GML_FEQUAL(0.5f, v2.x);
			GML_FEQUAL(0.0f, v2.y);
			GML_FEQUAL(0.0f, v2.z);
			GML_FEQUAL(0.5f, b.x);
			GML_FEQUAL(0.0f, b.y);
			GML_FEQUAL(0.0f, b.z);

			vec3 v3(0.0f, 2.0f, 0.0f);
			auto c = v3.inversed();
			v3.inverse();
			GML_FEQUAL(0.0f, v3.x);
			GML_FEQUAL(0.5f, v3.y);
			GML_FEQUAL(0.0f, v3.z);
			GML_FEQUAL(0.0f, c.x);
			GML_FEQUAL(0.5f, c.y);
			GML_FEQUAL(0.0f, c.z);

			vec3 v4(0.0f, 0.0f, 2.0f);
			auto d = v4.inversed();
			v4.inverse();
			GML_FEQUAL(0.0f, v4.x);
			GML_FEQUAL(0.0f, v4.y);
			GML_FEQUAL(0.5f, v4.z);
			GML_FEQUAL(0.0f, d.x);
			GML_FEQUAL(0.0f, d.y);
			GML_FEQUAL(0.5f, d.z);

			vec3 v5(3.0f, 4.0f, 5.0f);
			auto e = v5.inversed();
			v5.inverse();
			GML_FEQUAL(0.06f, v5.x);
			GML_FEQUAL(0.08f, v5.y);
			GML_FEQUAL(0.1f, v5.z);
			GML_FEQUAL(0.06f, e.x);
			GML_FEQUAL(0.08f, e.y);
			GML_FEQUAL(0.1f, e.z);
		}

		TEST_METHOD(Vec3LengthTest)
		{
			vec3 v1(2.0f, 0.0f, 0.0f);
			vec3 v2(3.0f, 4.0f, 5.0f);

			// length
			GML_FEQUAL(2.0f, v1.length());
			GML_FEQUAL(7.0710678f, v2.length());

			// length_sqr
			GML_FEQUAL(4.0f, v1.length_sqr());
			GML_FEQUAL(50.0f, v2.length_sqr());
		}

		TEST_METHOD(Vec3DotTest)
		{
			// dot
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(3.0f, 0.0f, 2.0f);

			GML_FEQUAL(9.0f, dot(v1, v2));
		}

		TEST_METHOD(Vec3CrossTest)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(3.0f, 0.0f, 2.0f);

			// cross
			auto crossV = cross(v1, v2);

			GML_FEQUAL(4.0f, crossV.x);
			GML_FEQUAL(7.0f, crossV.y);
			GML_FEQUAL(-6.0f, crossV.z);
		}

		TEST_METHOD(Vec3CombineTest)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(3.0f, 0.0f, 2.0f);

			// min_combine
			auto minV = min_combine(v1, v2);
			GML_FEQUAL(1.0f, minV.x);
			GML_FEQUAL(0.0f, minV.y);
			GML_FEQUAL(2.0f, minV.z);

			// max_combine
			auto maxV = max_combine(v1, v2);
			GML_FEQUAL(3.0f, maxV.x);
			GML_FEQUAL(2.0f, maxV.y);
			GML_FEQUAL(3.0f, maxV.z);
		}

		TEST_METHOD(Vec3Det33Test)
		{
			vec3 v1(1.0f, 2.0f, 3.0f);
			vec3 v2(3.0f, 0.0f, 2.0f);
			vec3 v3(2.0f, 1.0f, 2.0f);

			// det22
			GML_FEQUAL(3.0f, det33(v1, v2, v3));

			// det22_t
			GML_FEQUAL(3.0f, det33_t(v1, v2, v3));
		}

		TEST_METHOD(Vec3LerpTest)
		{
			const auto v1 = vec3::one();
			const vec3 v2(2.0f, 2.0f, 2.0f);

			auto lerpV = lerp(v1, v2, 0.5f);
			GML_FEQUAL(1.5f, lerpV.x);
			GML_FEQUAL(1.5f, lerpV.y);
			GML_FEQUAL(1.5f, lerpV.z);

			lerpV = lerp(v1, v2, 0.0f);
			GML_FEQUAL(1.0f, lerpV.x);
			GML_FEQUAL(1.0f, lerpV.y);
			GML_FEQUAL(1.0f, lerpV.z);

			lerpV = lerp(v1, v2, 1.0f);
			GML_FEQUAL(2.0f, lerpV.x);
			GML_FEQUAL(2.0f, lerpV.y);
			GML_FEQUAL(2.0f, lerpV.z);
		}
	};
}