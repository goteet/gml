#include "stdafx.h"


TEST_CLASS(Color4Test)
{
public:
	TEST_METHOD(Color4GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 4, sizeof(color4));
	}

	TEST_METHOD(Color4InitializationTest)
	{
		// color4()
		color4 c1;
		GML_FEQUAL(0.0f, c1.r);
		GML_FEQUAL(0.0f, c1.g);
		GML_FEQUAL(0.0f, c1.b);
		GML_FEQUAL(1.0f, c1.a);

		// color4(float, float, float, float)
		color4 c2(0.1f, 0.2f, 1.3f, 0.5f);
		GML_FEQUAL(0.1f, c2.r);
		GML_FEQUAL(0.2f, c2.g);
		GML_FEQUAL(1.3f, c2.b);
		GML_FEQUAL(0.5f, c2.a);

		// color4(color4)
		color3 ccc = color3::red();
		color4 c3(ccc, 0.1f);
		GML_FEQUAL(1.0f, c3.r);
		GML_FEQUAL(0.0f, c3.g);
		GML_FEQUAL(0.0f, c3.b);
		GML_FEQUAL(0.1f, c3.a);

		// color4(unsigned int)
		color4 c4 = color4::from_rgba(0xFFFF00FFu);
		GML_FEQUAL(1.0f, c4.r);
		GML_FEQUAL(0.0f, c4.g);
		GML_FEQUAL(1.0f, c4.b);
		GML_FEQUAL(1.0f, c4.a);
	}

	TEST_METHOD(Color4ConstantsTest)
	{
		const auto black = color4::black();
		GML_FEQUAL(0.0f, black.r);
		GML_FEQUAL(0.0f, black.g);
		GML_FEQUAL(0.0f, black.b);
		GML_FEQUAL(1.0f, black.a);

		const auto gray = color4::gray();
		GML_FEQUAL(0.5f, gray.r);
		GML_FEQUAL(0.5f, gray.g);
		GML_FEQUAL(0.5f, gray.b);
		GML_FEQUAL(1.0f, gray.a);

		const auto white = color4::white();
		GML_FEQUAL(1.0f, white.r);
		GML_FEQUAL(1.0f, white.g);
		GML_FEQUAL(1.0f, white.b);
		GML_FEQUAL(1.0f, white.a);

		const auto red = color4::red();
		GML_FEQUAL(1.0f, red.r);
		GML_FEQUAL(0.0f, red.g);
		GML_FEQUAL(0.0f, red.b);
		GML_FEQUAL(1.0f, red.a);

		const auto green = color4::green();
		GML_FEQUAL(0.0f, green.r);
		GML_FEQUAL(1.0f, green.g);
		GML_FEQUAL(0.0f, green.b);
		GML_FEQUAL(1.0f, green.a);

		const auto blue = color4::blue();
		GML_FEQUAL(0.0f, blue.r);
		GML_FEQUAL(0.0f, blue.g);
		GML_FEQUAL(1.0f, blue.b);
		GML_FEQUAL(1.0f, blue.a);

		const auto yellow = color4::yellow();
		GML_FEQUAL(1.0f, yellow.r);
		GML_FEQUAL(1.0f, yellow.g);
		GML_FEQUAL(0.0f, yellow.b);
		GML_FEQUAL(1.0f, yellow.a);

		const auto cyan = color4::cyan();
		GML_FEQUAL(0.0f, cyan.r);
		GML_FEQUAL(1.0f, cyan.g);
		GML_FEQUAL(1.0f, cyan.b);
		GML_FEQUAL(1.0f, cyan.a);

		const auto purple = color4::purple();
		GML_FEQUAL(1.0f, purple.r);
		GML_FEQUAL(0.0f, purple.g);
		GML_FEQUAL(1.0f, purple.b);
		GML_FEQUAL(1.0f, purple.a);
	}

	TEST_METHOD(Color4RandomTest)
	{
		auto c1 = color4::random();
		auto c2 = color4::random();

		GML_IS_FALSE(c1 == c2);
	}

	TEST_METHOD(Color4CompareTest)
	{
		color4 c1(0.1f, 0.2f, 1.0f, 0.4f);
		color4 c2(0.1f, 0.2f, 1.0f, 0.4f);
		auto c3 = c1;
		color4 c4(0.1f, 0.1f, 0.1f, 0.1f);

		// operator==
		GML_IS_TRUE(c1 == c1);
		GML_IS_TRUE(c1 == c2);
		GML_IS_TRUE(c1 == c3);

		// opeartor!=
		GML_IS_TRUE(c1 != c4);
	}

	TEST_METHOD(Color4AddTest)
	{
		color4 c1(0.1f, 0.1f, 0.1f, 0.1f);
		color4 c2(0.2f, 0.2f, 1.2f, 0.2f);
		float f = 0.5f;

		// operator+(float)
		auto a = c1 + f;
		GML_FEQUAL(0.6f, a.r);
		GML_FEQUAL(0.6f, a.g);
		GML_FEQUAL(0.6f, a.b);
		GML_FEQUAL(0.6f, a.a);

		// operator+(color4)
		auto b = c1 + c2;
		GML_FEQUAL(0.3f, b.r);
		GML_FEQUAL(0.3f, b.g);
		GML_FEQUAL(1.3f, b.b);
		GML_FEQUAL(0.3f, b.a);

		// operator+=(float)
		auto c = c1;
		c += f;
		GML_FEQUAL(0.6f, c.r);
		GML_FEQUAL(0.6f, c.g);
		GML_FEQUAL(0.6f, c.b);
		GML_FEQUAL(0.6f, c.a);

		// operator+=(color4)
		auto d = c1;
		d += c2;
		GML_FEQUAL(0.3f, d.r);
		GML_FEQUAL(0.3f, d.g);
		GML_FEQUAL(1.3f, d.b);
		GML_FEQUAL(0.3f, d.a);
	}

	TEST_METHOD(Color4MultiplyTest)
	{
		color4 c1(0.1f, 0.1f, 0.1f, 0.1f);
		color4 c2(0.2f, 0.2f, 1.2f, 0.2f);
		float f = 0.5f;

		// operator*(float)
		auto a = c1 * f;
		GML_FEQUAL(0.05f, a.r);
		GML_FEQUAL(0.05f, a.g);
		GML_FEQUAL(0.05f, a.b);
		GML_FEQUAL(0.05f, a.a);

		// operator*(color4)
		auto b = c1 * c2;
		GML_FEQUAL(0.02f, b.r);
		GML_FEQUAL(0.02f, b.g);
		GML_FEQUAL(0.12f, b.b);
		GML_FEQUAL(0.02f, b.a);

		// operator*=(float)
		auto c = c1;
		c *= f;
		GML_FEQUAL(0.05f, c.r);
		GML_FEQUAL(0.05f, c.g);
		GML_FEQUAL(0.05f, c.b);
		GML_FEQUAL(0.05f, c.a);

		// operator*=(color4)
		auto d = c1;
		d *= c2;
		GML_FEQUAL(0.02f, d.r);
		GML_FEQUAL(0.02f, d.g);
		GML_FEQUAL(0.12f, d.b);
		GML_FEQUAL(0.02f, d.a);
	}

	TEST_METHOD(Color4IndexTest)
	{
		// operator[]
		color4 c;
		c[0] = 0.2f;
		c[1] = 0.3f;
		c[2] = 0.5f;
		c[3] = 0.1f;
		GML_FEQUAL(0.2f, c.r);
		GML_FEQUAL(c[0], c.r);
		GML_FEQUAL(0.3f, c.g);
		GML_FEQUAL(c[1], c.g);
		GML_FEQUAL(0.5f, c.b);
		GML_FEQUAL(c[2], c.b);
		GML_FEQUAL(0.1f, c.a);
		GML_FEQUAL(c[3], c.a);
	}

	TEST_METHOD(Color4ToPointerTest)
	{
		// float*
		color4 c(0.1f, 0.2f, 0.3f, 0.4f);
		float *fv = (float *)c;
		GML_FEQUAL(0.1f, fv[0]);
		GML_FEQUAL(0.2f, fv[1]);
		GML_FEQUAL(0.3f, fv[2]);
		GML_FEQUAL(0.4f, fv[3]);
	}

	TEST_METHOD(Color4SetTest)
	{
		color4 c1, c2;

		// set(float, float, float, float)
		c1.set(0.1f, 0.2f, 0.3f, 0.4f);
		GML_FEQUAL(0.1f, c1.r);
		GML_FEQUAL(0.2f, c1.g);
		GML_FEQUAL(0.3f, c1.b);
		GML_FEQUAL(0.4f, c1.a);
	}

	TEST_METHOD(Color4RgbaTest)
	{
		auto c1 = color4::red();
		auto c2 = color4::white();
		auto c3 = color4::black();

		GML_IEQUAL(0xFFFF0000u, c1.rgba());
		GML_IEQUAL(0xFFFFFFFFu, c2.rgba());
		GML_IEQUAL(0xFF000000u, c3.rgba());
	}

	TEST_METHOD(Color4BgraTest)
	{
		auto c1 = color4::red();
		auto c2 = color4::white();
		auto c3 = color4::black();

		GML_IEQUAL(0xFF0000FFu, c1.bgra());
		GML_IEQUAL(0xFFFFFFFFu, c2.rgba());
		GML_IEQUAL(0xFF000000u, c3.rgba());
	}
};